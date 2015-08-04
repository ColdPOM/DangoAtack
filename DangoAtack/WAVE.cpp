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
	/// WAVE�t�@�C���̓ǂݍ���
	/// [in] fileName �ǂݍ���WAVE�t�@�C���̖��O
	/// [in] buffer   �g�`�f�[�^���i�[����o�b�t�@
	// --------------------------------------------------------------------------------------
	void WAVE::Load(const char* fileName, ALuint* buffer){
		// �t�@�C�����J��
		std::ifstream file(fileName,  std::ios::binary);
		// �I�[�v�����s
		if (file.fail()){
			std::cerr << "Error: Couldn't open WAVE file: " << fileName << "\n" << std::endl;
			return;
		}

		// �w�b�_�̓ǂݍ���
		file.read((char*)&header, sizeof(RiffHeader));

		// �t�H�[�}�b�g�`�����N�ǂݍ���
		file.read((char*)&format, sizeof(FormatChunk));
		
		// �t�H�[�}�b�g�`�����N�g���� �����j�APCM�̏ꍇ�͑��݂��Ȃ�
		if(format.format != 1){
			formatEx.formatChunk = &format;
			file.read((char*)&formatEx.extended_size, sizeof(ALushort));
			formatEx.extended = new ALubyte[formatEx.extended_size];
			for(int i = 0; i < formatEx.extended_size; i++){
				file.read((char*)&formatEx.extended[i], sizeof(ALubyte));
			}
		}

		// �f�[�^�̓ǂݍ���
		file.read((char*)&data.id, sizeof(ALuint));
		file.read((char*)&data.size, sizeof(ALint));
		data.waveformData = new ALubyte[data.size];
		for(int i = 0; i < data.size; i++){
			file.read((char*)&data.waveformData[i], sizeof(ALubyte));
		}

		// �ǂݍ��񂾃f�[�^���o�b�t�@�ɑ���
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

		// �t�@�C�������
		file.close();
	}



	// -------------------------------------------------------------------------------
	/// �g�`�f�[�^���O�܂ł�ǂݍ���
	/// [in] �ǂݍ��ރt�@�C���̃|�C���^
	// -------------------------------------------------------------------------------
	void WAVE::LoadHeaderAndFormat(std::ifstream *file){
		// �I�[�v�����s
		if (file->fail()){
			std::cerr << "Error: Couldn't open WAVE file BGM" << std::endl;
			return;
		}

		// �w�b�_�̓ǂݍ���
		file->read((char*)&header, sizeof(RiffHeader));

		// �t�H�[�}�b�g�`�����N�ǂݍ���
		file->read((char*)&format, sizeof(FormatChunk));
		
		// �t�H�[�}�b�g�`�����N�g���� �����j�APCM�̏ꍇ�͑��݂��Ȃ�
		if(format.format != 1){
			formatEx.formatChunk = &format;
			file->read((char*)&formatEx.extended_size, sizeof(ALushort));
			formatEx.extended = new ALubyte[formatEx.extended_size];
			for(int i = 0; i < formatEx.extended_size; i++){
				file->read((char*)&formatEx.extended[i], sizeof(ALubyte));
			}
		}

		// �f�[�^�`�����N�̔g�`�f�[�^�̒��O�܂œǂݍ���
		file->read((char*)&data.id, sizeof(ALuint));
		file->read((char*)&data.size, sizeof(ALint));
	}


	// -----------------------------------------------------------------------------------
	/// �w��T�C�Y���g�`�f�[�^��ǂݍ���
	/// �g�p����O�ɕK��LoadHeaderAndFormat�֐��Ńw�b�_�ƃt�H�[�}�b�g�`�����N��ǂݍ���ł�������
	/// [in] file   �ǂݍ��ރt�@�C���̃|�C���^
	/// [in] buffer �g�`�f�[�^���i�[����o�b�t�@
	/// [in] size   �ǂݍ��ރT�C�Y
	// -----------------------------------------------------------------------------------
	void WAVE::LoadData(std::ifstream* file, ALuint* buffer, int size){
		// �g�`�f�[�^�̓ǂݍ���
		ALubyte* waveformData = new ALubyte[size];
		for(int i = 0; i < size; i++){
			file->read((char*)&waveformData[i], sizeof(ALubyte));
		}

		// �ǂݍ��񂾃f�[�^���o�b�t�@�ɑ���
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