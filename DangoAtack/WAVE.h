#pragma once
#include "Common.h"

// -----------------------------------------------------------------------------------
/// WAVE�t�@�C���̓ǂݍ��݂��s���N���X
// -----------------------------------------------------------------------------------

namespace wave{

	// RIFF�w�b�_
	struct RiffHeader {
		ALuint riff; // RIFF�̎��ʎq"RIFF"
		ALint size;  // riff��size���������t�@�C���T�C�Y
		ALuint type; // RIFF�̎��"WAVE"
	};

	// �t�H�[�}�b�g�`�����N
	struct FormatChunk {
	  ALuint id;            // �`�����N���ʎq("fmt")
	  ALint size;           // id��size���������`�����N�T�C�Y
	  ALshort format;       // �t�H�[�}�b�gID
	  ALushort channels;    // �`�����l����
	  ALuint samplerate;    // �T���v�����O���g��(Hz)
	  ALuint bytepersec;    // �P�b�Ԃ̘^���ɕK�v�ȃo�C�g�� (�o�C�g�^�b)�@
	  ALushort blockalign;  // �f�[�^�̃u���b�N�T�C�Y  (Byte/sample�~�`�����l����)
	  ALushort bitswidth;   // �T���v��������̃r�b�g�� (bit/sample)
	};

	// �t�H�[�}�b�g�`�����N�g����
	struct FormatChunkEx {
	  FormatChunk* formatChunk;
	  ALushort extended_size;
	  ALubyte* extended;
	};

	// �f�[�^�`�����N
	struct DataChunk {
	  ALuint id;   // �`�����N���ʎq("data")
	  ALint size;  // �g�`�f�[�^�̃o�C�g��

	  ALubyte* waveformData; // �g�`�f�[�^
	};



	class WAVE
	{
	public:
		WAVE(void);
		~WAVE(void);

		void Load(const char* fileName, ALuint* buffer);                 // �ǂݍ���
		void LoadHeaderAndFormat(std::ifstream* file);                   // �g�`�f�[�^���O�܂ł�ǂݍ���
		void LoadData(std::ifstream* file, ALuint* buffer, int size);    // �w��T�C�Y���f�[�^��ǂݍ���

		// �Q�b�^�[
		inline RiffHeader getHeader() { return header; }   // �w�b�_�[���̎擾
		inline FormatChunk getFormat() { return format; }  // �t�H�[�}�b�g���̎擾
		inline DataChunk getData() { return data; }        // �f�[�^���̎擾


	private:
		RiffHeader header;
		FormatChunk format;
		FormatChunkEx formatEx;
		DataChunk data;

		bool mLoadFlag; // ���[�h�����t���O
	};

}

