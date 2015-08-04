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
/// �X�g���[�~���O�Đ�
/// [in] filneName  �t�@�C���p�X
/// [in] self       ���N���X�̃|�C���^
// ------------------------------------------------------------------------
void Sound::Streaming(const char* fileName, Sound* self){
	//gMutex.lock();

	// �t�@�C�����J��
	std::ifstream file(fileName,  std::ios::binary);
	wave::WAVE wavFile;
	// �g�`�f�[�^���O�܂œǂݍ���
	wavFile.LoadHeaderAndFormat(&file);

	// �J�n���ԂƏI�����Ԃ�b����o�C�g�ɕϊ�
	int start = self->mStartPoint * wavFile.getFormat().bytepersec;
	int end;
	if(self->mEndPoint == -1) end = wavFile.getData().size;
	else end = self->mEndPoint * wavFile.getFormat().bytepersec;
	if(end > wavFile.getData().size) end = wavFile.getData().size;

	const int loadSize = (end - start) / self->mBufferSize; // ��x�ɓǂݍ��ރT�C�Y
	int loadCompSize = 0; // ���ݓǂݍ��񂾃T�C�Y�L�^�p

	// �o�b�t�@�̐���
	ALuint* mBuffers = new ALuint[self->mBufferSize];
	alGenBuffers(self->mBufferSize, mBuffers);

	// ��ڂ̃o�b�t�@�ɓǂݍ���ōĐ�
	file.seekg(start, std::ios_base::cur);
	wavFile.LoadData(&file, &mBuffers[0], loadSize);
	alSourceQueueBuffers(self->mSource, 1, &mBuffers[0]);
	alSourcePlay(self->mSource);
	loadCompSize += loadSize;

	// �Ō�̈�O�܂ł̃o�b�t�@�܂œǂݍ��݃L���[�C���O
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

	// �Ō�̈�̃o�b�t�@�ɓǂݍ��݃L���[�C���O
	wavFile.LoadData(&file, &mBuffers[self->mBufferSize - 1], end - start - loadCompSize);
	alSourceQueueBuffers(self->mSource, 1, &mBuffers[self->mBufferSize - 1]);

	// �t�@�C�������
	file.close();
	alDeleteBuffers(self->mBufferSize, mBuffers);
	delete[] mBuffers;

	//gMutex.unlock();
}


// ------------------------------------------------------------------------
/// BGM�̍Đ�
/// ���[�v�̗L����ݒ肵�Ȃ��ꍇ���[�v�͂���܂���
/// [in] fileName �t�@�C���p�X
/// [in] loop     ���[�v�̗L��
// ------------------------------------------------------------------------
void Sound::PlayBGM(const char* fileName, bool loop){
	if(mType == TYPE::SE) return;

	if(mType == TYPE::NOTYPE){
		mType = TYPE::BGM;

		mStartPoint = 0;
		mEndPoint = -1;

		// �\�[�X�̐���
		alGenSources(1, &mSource);
		alSourcei(mSource, AL_LOOPING, loop);

		// �ʃX���b�h�œǂݍ��݂Đ�
		std::thread th(Streaming, fileName, this);
		th.detach();
	}
}


// ------------------------------------------------------------------------
/// �͈͂��w�肵��BGM�̍Đ�
/// �I���ʒu��-1���w�肷��ƍŌ�܂ōĐ�����܂�
/// [in] fileName   �t�@�C���p�X
/// [in] startpoint �J�n�ʒu(�b)
/// [in] endpoint   �I���ʒu(�b)
/// [in] loop       ���[�v�̗L��
// ------------------------------------------------------------------------
void Sound::PlayBGM(const char* fileName, float startpoint, float endpoint, bool loop){
	if(mType == TYPE::SE) return;

	if(mType == TYPE::NOTYPE){
		mType = TYPE::BGM;

		mStartPoint = startpoint;
		mEndPoint = endpoint;

		// �\�[�X�̐���
		alGenSources(1, &mSource);
		alSourcei(mSource, AL_LOOPING, loop);

		// �ʃX���b�h�œǂݍ��݂Đ�
		std::thread th(Streaming, fileName, this);
		th.detach();
	}
}



// --------------------------------------------------------------------------
/// ���ڈȍ~��BGM�Đ�
/// ��~��ꎞ��~�̏�Ԃ��畜�A���Ă�BGM���Đ����܂�
// --------------------------------------------------------------------------
void Sound::PlayBGM(){
	if(mType == TYPE::BGM && (getState() == AL_STOPPED || getState() == AL_PAUSED)){
		alSourcePlay(mSource);
	}
}



// ------------------------------------------------------------------------
/// ���ʉ���ǂݍ���
/// ���[�h�͈��̂ݍs�����Ƃ��o���܂�
/// [in] �t�@�C���p�X
// ------------------------------------------------------------------------
void Sound::LoadSE(const char* fileName){
	if(mLoadFlag || mType != TYPE::NOTYPE) return;
	mType = TYPE::SE;

	// �o�b�t�@�̐���
	ALuint buffer;			   // SE�p�o�b�t�@
	alGenBuffers(1, &buffer);

	// WAVE�t�@�C���̓ǂݍ���
	wave::WAVE wavFile;
	wavFile.Load(fileName, &buffer);

	// �\�[�X�̐���
	alGenSources(1, &mSource);
	alSourcei(mSource, AL_BUFFER, buffer);

	mLoadFlag = true;
	alDeleteBuffers(1, &buffer);
}



// -------------------------------------------------------------------------
// ���ʉ���炷
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
// ���W���w�肵�Č��ʉ���炷
// [in] x,y,z �����̈ʒu
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
