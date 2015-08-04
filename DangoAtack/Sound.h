#pragma once
#include "WAVE.h"
#include <vector>
#include <thread>

// ---------------------------------------------------------------------
/// �T�E���h�������N���X
/// �Ή��t�@�C���`��: WAVE
// ---------------------------------------------------------------------

class Sound
{
public:
	Sound(void);
	~Sound(void);

	// ���ʒ��� (0.0 �` 1.0�j
	inline void setVolume(float value) { alSourcef(mSource, AL_GAIN, value); } 

	// BGM�̑���
	void PlayBGM(const char* fileName, bool loop = false);  // BGM�̍Đ�
	void PlayBGM(const char* fileName, float startpoint, float endpoint = -1, bool loop = false);  // �͈͂��w�肵��BGM�̍Đ�
	void PlayBGM();                                           // ���ڈȍ~�̍Đ�
	inline void Stop() { alSourceStop(mSource); }             // ��~
	inline void Pause() { alSourcePause(mSource); }           // �ꎞ��~

	// SE�̑���
	void LoadSE(const char* fileName);  // SE�̃��[�h
	void PlaySE();  // SE�̍Đ�
	void PlaySE(float x, float y, float z);  // ���W���w�肵��SE�̍Đ�

	// �Z�b�^�[
	inline void setPos(float x, float y, float z) { mPos[0] = x, mPos[1] = y, mPos[2] = z; 
	alSourcefv(mSource, AL_POSITION, mPos);
	}

	// �Q�b�^�[
	inline bool LoadComp() { return mLoadFlag; } // ���[�h�����t���O�̎擾
	inline ALint getState() { alGetSourcei(mSource, AL_SOURCE_STATE, &mState); return mState; } // �T�E���h�̏�Ԏ擾


private:
	enum TYPE { NOTYPE, BGM, SE}; // �T�E���h�̃^�C�v�A������Ԃ�NOTYPE

	static void Streaming(const char* fileName, Sound* self); // �X�g���[�~���O�Đ�

	TYPE mType;                // �T�E���h�̃^�C�v
	ALint mState;              // �T�E���h�̏��
	bool mLoadFlag;            // ���[�h�����t���O
	float mStartPoint;         // �Đ��J�n�ʒu
	float mEndPoint;           // �Đ��I���ʒu
	const ALuint mBufferSize;  // �X�g���[�~���O�Đ����̃o�b�t�@�̐�
	ALuint mSource;            // �\�[�X
	float mPos[3];             // �\�[�X�̈ʒu
};

