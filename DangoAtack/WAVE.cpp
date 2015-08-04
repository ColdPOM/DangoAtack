#include "WAVE.h"

namespace wave{

	WAVE::WAVE(void): mLoadFlag(false)
	{
	}


	WAVE::~WAVE(void)
	{
		if(format.format != 1)delete[] formatEx.extended;
		if(mLoadFlag)delete[] data.waveformData;
	}



	// --------------------------------------------------------------------------------------
	/// WAVEファイルの読み込み
	/// [in] fileName 読み込むWAVEファイルの名前
	/// [in] buffer   波形データを格納するバッファ
	// --------------------------------------------------------------------------------------
	void WAVE::Load(const char* fileName, ALuint* buffer){
		// ファイルを開く
		std::ifstream file(fileName,  std::ios::binary);
		// オープン失敗
		if (file.fail()){
			std::cerr << "Error: Couldn't open WAVE file: " << fileName << "\n" << std::endl;
			return;
		}

		// ヘッダの読み込み
		file.read((char*)&header, sizeof(RiffHeader));

		// フォーマットチャンク読み込み
		file.read((char*)&format, sizeof(FormatChunk));
		
		// フォーマットチャンク拡張部 ※リニアPCMの場合は存在しない
		if(format.format != 1){
			formatEx.formatChunk = &format;
			file.read((char*)&formatEx.extended_size, sizeof(ALushort));
			formatEx.extended = new ALubyte[formatEx.extended_size];
			for(int i = 0; i < formatEx.extended_size; i++){
				file.read((char*)&formatEx.extended[i], sizeof(ALubyte));
			}
		}

		// データの読み込み
		file.read((char*)&data.id, sizeof(ALuint));
		file.read((char*)&data.size, sizeof(ALint));
		data.waveformData = new ALubyte[data.size];
		for(int i = 0; i < data.size; i++){
			file.read((char*)&data.waveformData[i], sizeof(ALubyte));
		}

		// 読み込んだデータをバッファに送る
		if(format.channels == 1){
			if(format.bitswidth == 8) {
				alBufferData(*buffer, AL_FORMAT_MONO8, data.waveformData, data.size, format.samplerate);
			}
			else if(format.bitswidth == 16){
				alBufferData(*buffer, AL_FORMAT_MONO16, data.waveformData, data.size, format.samplerate);
			}
		}
		else if(format.channels == 2){
			if(format.bitswidth == 8) {
				alBufferData(*buffer, AL_FORMAT_STEREO8, data.waveformData, data.size, format.samplerate);
			}
			else if(format.bitswidth == 16){
				alBufferData(*buffer, AL_FORMAT_STEREO16, data.waveformData, data.size, format.samplerate);
			}
		}

		mLoadFlag = true;

		// ファイルを閉じる
		file.close();
	}



	// -------------------------------------------------------------------------------
	/// 波形データ直前までを読み込む
	/// [in] 読み込むファイルのポインタ
	// -------------------------------------------------------------------------------
	void WAVE::LoadHeaderAndFormat(std::ifstream *file){
		// オープン失敗
		if (file->fail()){
			std::cerr << "Error: Couldn't open WAVE file BGM" << std::endl;
			return;
		}

		// ヘッダの読み込み
		file->read((char*)&header, sizeof(RiffHeader));

		// フォーマットチャンク読み込み
		file->read((char*)&format, sizeof(FormatChunk));
		
		// フォーマットチャンク拡張部 ※リニアPCMの場合は存在しない
		if(format.format != 1){
			formatEx.formatChunk = &format;
			file->read((char*)&formatEx.extended_size, sizeof(ALushort));
			formatEx.extended = new ALubyte[formatEx.extended_size];
			for(int i = 0; i < formatEx.extended_size; i++){
				file->read((char*)&formatEx.extended[i], sizeof(ALubyte));
			}
		}

		// データチャンクの波形データの直前まで読み込み
		file->read((char*)&data.id, sizeof(ALuint));
		file->read((char*)&data.size, sizeof(ALint));
	}


	// -----------------------------------------------------------------------------------
	/// 指定サイズ分波形データを読み込む
	/// 使用する前に必ずLoadHeaderAndFormat関数でヘッダとフォーマットチャンクを読み込んでください
	/// [in] file   読み込むファイルのポインタ
	/// [in] buffer 波形データを格納するバッファ
	/// [in] size   読み込むサイズ
	// -----------------------------------------------------------------------------------
	void WAVE::LoadData(std::ifstream* file, ALuint* buffer, int size){
		// 波形データの読み込み
		ALubyte* waveformData = new ALubyte[size];
		for(int i = 0; i < size; i++){
			file->read((char*)&waveformData[i], sizeof(ALubyte));
		}

		// 読み込んだデータをバッファに送る
		if(format.channels == 1){
			if(format.bitswidth == 8) {
				alBufferData(*buffer, AL_FORMAT_MONO8, waveformData, size, format.samplerate);
			}
			else if(format.bitswidth == 16){
				alBufferData(*buffer, AL_FORMAT_MONO16, waveformData, size, format.samplerate);
			}
		}
		else if(format.channels == 2){
			if(format.bitswidth == 8) {
				alBufferData(*buffer, AL_FORMAT_STEREO8, waveformData, size, format.samplerate);
			}
			else if(format.bitswidth == 16){
				alBufferData(*buffer, AL_FORMAT_STEREO16, waveformData, size, format.samplerate);
			}
		}

		delete[] waveformData;
	}
}