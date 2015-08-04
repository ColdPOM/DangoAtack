#include "DDS.h"

namespace dds{

	DDS::DDS(void)
	{
	}


	DDS::~DDS(void)
	{
		delete[] imageData;
	}

	// ---------------------------------------------------------------------------------
	/// DDS�t�@�C���̓ǂݍ���
	/// [in] fileName �ǂݍ��ރt�@�C���̃t���p�X
	// ---------------------------------------------------------------------------------
	bool DDS::readDDS(const char *fileName)
	{
		char magic[4];
		int mipmapFactor;
		long curr, end;
		DDSurfaceDesc ddsd;

		//�@�t�@�C�����J��
		std::ifstream file(fileName,  std::ios::binary);
		if (file.fail())
		{
			std::cout << "Error : �w�肳�ꂽ�t�@�C�����J���܂���ł���\n";
			std::cout << "File : " << fileName << std::endl;
			return false;
		}

		//�@�}�W�b�N��ǂݎ��
		file.read(magic, 4);

		//�@�}�W�b�N���`�F�b�N
		if ( strncmp(magic, "DDS ", 4 ) != 0 )
		{
			std::cout << "Error : DDS�t�@�C���ł͂���܂���\n";
			file.close();
			return false;
		}

		//�@�w�b�_�[��ǂݎ��
		file.read((char*)&ddsd, sizeof ddsd);

		//�@���E�������i�[
		height = ddsd.height;
		width = ddsd.width;
		numMipmaps = ddsd.mipMapLevels;

		//�@�t�H�[�}�b�g����
		switch ( ddsd.format.fourCC )
		{
		case '1TXD':
			//�@DXT1
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			internalFormat = 3;
			mipmapFactor = 2;
			break;

		case '3TXD':
			//�@DXT3
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			internalFormat = 4;
			mipmapFactor = 4;
			break;

		case '5TXD':
			//�@DXT5
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			internalFormat = 4;
			mipmapFactor = 4;
			break;

		default:
			std::cout << "Error : ���Ή��̌`���ł��BDXT1, DXT3, DXT5�̂����ꂩ���g�p���Ă�������\n";
			return false;
		}

		//�@�e�N�Z���f�[�^�̃T�C�Y���Z�o
		curr = file.tellg();
		file.seekg(0, SEEK_END);
		end = file.tellg();
		file.seekg(curr, SEEK_SET);
		imageSize = end - curr;
		imageData = new GLubyte [imageSize];

		//�@�s�N�Z���f�[�^�̓ǂݍ���
		file.read((char*)imageData, sizeof(GLubyte) * imageSize);
	
		//�@�t�@�C�������
		file.close();

		return true;
	}




	// ------------------------------------------------------------------------------------------------------------
	/// DDS�t�@�C���̉�
	// ------------------------------------------------------------------------------------------------------------
	void DDS::decompressDDS()
	{
		int blockSize;
		int offset = 0;
		GLsizei mWidth = width, mHeight = height, mSize = 0;

		//�@DXT1
		if ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
			blockSize = 8;
		//�@DXT3, DXT5
		else
			blockSize = 16;

		//�@��
		for ( int i=0; i<(int)numMipmaps; i++ )
		{
			mSize = ( (mWidth+3)/4 ) * ( (mHeight+3)/4 ) * blockSize;
			glCompressedTexImage2D(GL_TEXTURE_2D, i, format, mWidth, mHeight, 0, mSize, imageData + offset );
        
			if ( mWidth >> 1 )  mWidth = (mWidth >> 1);
			else    mWidth = 1;

			if ( mHeight >> 1 ) mHeight = (mHeight >> 1);
			else    mHeight = 1;

			offset += mSize;
		}
	}

	// --------------------------------------------------------------------------------------------
	/// �e�N�X�`���̐���
	/// DDS�t�@�C����ǂݍ��݃e�N�X�`���𐶐����܂�
	/// [in] �ǂݍ��ރt�@�C���̃t���p�X
	/// [out] �������ꂽ�e�N�X�`���I�u�W�F�N�g��ID
	// --------------------------------------------------------------------------------------------
	GLuint DDS::Load(const char *filename)
	{
		//�@�t�@�C���̓ǂݍ���
		if ( !readDDS(filename) )
			return 0;

		//�@�e�N�X�`���𐶐�
		glGenTextures(1, &ID);

		//�@�e�N�X�`�����o�C���h
		glBindTexture(GL_TEXTURE_2D, ID);

		//�@�g��E�k��������@�̎w��
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// �e�N�X�`���̌J��Ԃ�
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
		//�@�e�N�X�`�����̐ݒ�
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//�@�𓀍��
		decompressDDS();

		if ( imageData )
		{
			delete [] imageData;
			imageData = NULL;
		}

		// �o�C���h����
		glBindTexture(GL_TEXTURE_2D, 0);

		// ���������e�N�X�`���ԍ���Ԃ�
		return ID;
	}

}