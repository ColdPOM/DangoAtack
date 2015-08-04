#include "Sound.h"


Sound::Sound(void):
	mType(NOTYPE),
	mLoadFlag(false),
	mBufferSize(10)
{
	mPos[0] = 0.0f;
	mPos[1] = 0.0f;
	mPos[2] = 0.0f;
}


Sound::~Sound(void)
{
	Stop();
	alSourcei(mSource, AL_BUFFER, 0);
	alDeleteSources(1, &mSource);
}

// ------------------------------------------------------------------------
/// ストリーミング再生
/// [in] filneName  ファイルパス
/// [in] self       自クラスのポインタ
// ------------------------------------------------------------------------
void Sound::Streaming(const char* fileName, Sound* self){
	//gMutex.lock();

	// ファイルを開く
	std::ifstream file(fileName,  std::ios::binary);
	wave::WAVE wavFile;
	// 波形データ直前まで読み込み
	wavFile.LoadHeaderAndFormat(&file);

	// 開始時間と終了時間を秒からバイトに変換
	int start = self->mStartPoint * wavFile.getFormat().bytepersec;
	int end;
	if(self->mEndPoint == -1) end = wavFile.getData().size;
	else end = self->mEndPoint * wavFile.getFormat().bytepersec;
	if(end > wavFile.getData().size) end = wavFile.getData().size;

	const int loadSize = (end - start) / self->mBufferSize; // 一度に読み込むサイズ
	int loadCompSize = 0; // 現在読み込んだサイズ記録用

	// バッファの生成
	ALuint* mBuffers = new ALuint[self->mBufferSize];
	alGenBuffers(self->mBufferSize, mBuffers);

	// 一つ目のバッファに読み込んで再生
	file.seekg(start, std::ios_base::cur);
	wavFile.LoadData(&file, &mBuffers[0], loadSize);
	alSourceQueueBuffers(self->mSource, 1, &mBuffers[0]);
	alSourcePlay(self->mSource);
	loadCompSize += loadSize;

	// 最後の一つ前までのバッファまで読み込みキューイング
	for(int i = 1; i < self->mBufferSize - 1; i++){
		if(self->getState() == AL_STOPPED) {
			file.close();
			alDeleteBuffers(self->mBufferSize, mBuffers);
			delete[] mBuffers;
			//gMutex.unlock();
			return;
		}

		wavFile.LoadData(&file, &mBuffers[i], loadSize);
		alSourceQueueBuffers(self->mSource, 1, &mBuffers[i]);
		loadCompSize += loadSize;
	}

	// 最後の一つのバッファに読み込みキューイング
	wavFile.LoadData(&file, &mBuffers[self->mBufferSize - 1], end - start - loadCompSize);
	alSourceQueueBuffers(self->mSource, 1, &mBuffers[self->mBufferSize - 1]);

	// ファイルを閉じる
	file.close();
	alDeleteBuffers(self->mBufferSize, mBuffers);
	delete[] mBuffers;

	//gMutex.unlock();
}


// ------------------------------------------------------------------------
/// BGMの再生
/// ループの有無を設定しない場合ループはされません
/// [in] fileName ファイルパス
/// [in] loop     ループの有無
// ------------------------------------------------------------------------
void Sound::PlayBGM(const char* fileName, bool loop){
	if(mType == TYPE::SE) return;

	if(mType == TYPE::NOTYPE){
		mType = TYPE::BGM;

		mStartPoint = 0;
		mEndPoint = -1;

		// ソースの生成
		alGenSources(1, &mSource);
		alSourcei(mSource, AL_LOOPING, loop);

		// 別スレッドで読み込みつつ再生
		std::thread th(Streaming, fileName, this);
		th.detach();
	}
}


// ------------------------------------------------------------------------
/// 範囲を指定してBGMの再生
/// 終了位置に-1を指定すると最後まで再生されます
/// [in] fileName   ファイルパス
/// [in] startpoint 開始位置(秒)
/// [in] endpoint   終了位置(秒)
/// [in] loop       ループの有無
// ------------------------------------------------------------------------
void Sound::PlayBGM(const char* fileName, float startpoint, float endpoint, bool loop){
	if(mType == TYPE::SE) return;

	if(mType == TYPE::NOTYPE){
		mType = TYPE::BGM;

		mStartPoint = startpoint;
		mEndPoint = endpoint;

		// ソースの生成
		alGenSources(1, &mSource);
		alSourcei(mSource, AL_LOOPING, loop);

		// 別スレッドで読み込みつつ再生
		std::thread th(Streaming, fileName, this);
		th.detach();
	}
}



// --------------------------------------------------------------------------
/// 二回目以降のBGM再生
/// 停止や一時停止の状態から復帰し再びBGMを再生します
// --------------------------------------------------------------------------
void Sound::PlayBGM(){
	if(mType == TYPE::BGM && (getState() == AL_STOPPED || getState() == AL_PAUSED)){
		alSourcePlay(mSource);
	}
}



// ------------------------------------------------------------------------
/// 効果音を読み込む
/// ロードは一回のみ行うことが出来ます
/// [in] ファイルパス
// ------------------------------------------------------------------------
void Sound::LoadSE(const char* fileName){
	if(mLoadFlag || mType != TYPE::NOTYPE) return;
	mType = TYPE::SE;

	// バッファの生成
	ALuint buffer;			   // SE用バッファ
	alGenBuffers(1, &buffer);

	// WAVEファイルの読み込み
	wave::WAVE wavFile;
	wavFile.Load(fileName, &buffer);

	// ソースの生成
	alGenSources(1, &mSource);
	alSourcei(mSource, AL_BUFFER, buffer);

	mLoadFlag = true;
	alDeleteBuffers(1, &buffer);
}



// -------------------------------------------------------------------------
// 効果音を鳴らす
// -------------------------------------------------------------------------
void Sound::PlaySE(){
	if(mLoadFlag && mType == TYPE::SE){
		mPos[0] = listnerPos[0];
		mPos[1] = listnerPos[1];
		mPos[2] = listnerPos[2];
		alSourcefv(mSource, AL_POSITION, mPos);
		alSourcePlay(mSource);
	}
	else if(!mLoadFlag){
		std::cout << "Error: This Sound is not loaded" << std::endl;
	}
	else if(mType != TYPE::SE){
		std::cout << "Error: This Sound is not SE" << std::endl;
	}
}


// -------------------------------------------------------------------------
// 座標を指定して効果音を鳴らす
// [in] x,y,z 音源の位置
// -------------------------------------------------------------------------
void Sound::PlaySE(float x, float y, float z){
	if(mLoadFlag && mType == TYPE::SE){
		mPos[0] = x;
		mPos[1] = y;
		mPos[2] = z;
		alSourcefv(mSource, AL_POSITION, mPos);
		alSourcePlay(mSource);
	}
	else if(!mLoadFlag){
		std::cout << "Error: This Sound is not loaded" << std::endl;
	}
	else if(mType != TYPE::SE){
		std::cout << "Error: This Sound is not SE" << std::endl;
	}
}
