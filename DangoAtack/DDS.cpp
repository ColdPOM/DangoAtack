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
	/// DDSファイルの読み込み
	/// [in] fileName 読み込むファイルのフルパス
	// ---------------------------------------------------------------------------------
	bool DDS::readDDS(const char *fileName)
	{
		char magic[4];
		int mipmapFactor;
		long curr, end;
		DDSurfaceDesc ddsd;

		//　ファイルを開く
		std::ifstream file(fileName,  std::ios::binary);
		if (file.fail())
		{
			std::cout << "Error : 指定されたファイルを開けませんでした\n";
			std::cout << "File : " << fileName << std::endl;
			return false;
		}

		//　マジックを読み取り
		file.read(magic, 4);

		//　マジックをチェック
		if ( strncmp(magic, "DDS ", 4 ) != 0 )
		{
			std::cout << "Error : DDSファイルではありません\n";
			file.close();
			return false;
		}

		//　ヘッダーを読み取り
		file.read((char*)&ddsd, sizeof ddsd);

		//　幅・高さを格納
		height = ddsd.height;
		width = ddsd.width;
		numMipmaps = ddsd.mipMapLevels;

		//　フォーマット判別
		switch ( ddsd.format.fourCC )
		{
		case '1TXD':
			//　DXT1
			format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			internalFormat = 3;
			mipmapFactor = 2;
			break;

		case '3TXD':
			//　DXT3
			format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
			internalFormat = 4;
			mipmapFactor = 4;
			break;

		case '5TXD':
			//　DXT5
			format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			internalFormat = 4;
			mipmapFactor = 4;
			break;

		default:
			std::cout << "Error : 未対応の形式です。DXT1, DXT3, DXT5のいずれかを使用してください\n";
			return false;
		}

		//　テクセルデータのサイズを算出
		curr = file.tellg();
		file.seekg(0, SEEK_END);
		end = file.tellg();
		file.seekg(curr, SEEK_SET);
		imageSize = end - curr;
		imageData = new GLubyte [imageSize];

		//　ピクセルデータの読み込み
		file.read((char*)imageData, sizeof(GLubyte) * imageSize);
	
		//　ファイルを閉じる
		file.close();

		return true;
	}




	// ------------------------------------------------------------------------------------------------------------
	/// DDSファイルの解凍
	// ------------------------------------------------------------------------------------------------------------
	void DDS::decompressDDS()
	{
		int blockSize;
		int offset = 0;
		GLsizei mWidth = width, mHeight = height, mSize = 0;

		//　DXT1
		if ( format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT )
			blockSize = 8;
		//　DXT3, DXT5
		else
			blockSize = 16;

		//　解凍
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
	/// テクスチャの生成
	/// DDSファイルを読み込みテクスチャを生成します
	/// [in] 読み込むファイルのフルパス
	/// [out] 生成されたテクスチャオブジェクトのID
	// --------------------------------------------------------------------------------------------
	GLuint DDS::Load(const char *filename)
	{
		//　ファイルの読み込み
		if ( !readDDS(filename) )
			return 0;

		//　テクスチャを生成
		glGenTextures(1, &ID);

		//　テクスチャをバインド
		glBindTexture(GL_TEXTURE_2D, ID);

		//　拡大・縮小する方法の指定
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		// テクスチャの繰り返し
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    
		//　テクスチャ環境の設定
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

		//　解凍作業
		decompressDDS();

		if ( imageData )
		{
			delete [] imageData;
			imageData = NULL;
		}

		// バインド解除
		glBindTexture(GL_TEXTURE_2D, 0);

		// 生成したテクスチャ番号を返す
		return ID;
	}

}