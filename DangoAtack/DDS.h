#pragma once
#include "Common.h"

namespace dds{

	typedef struct DDPixelFormat
	{
		GLuint size;
		GLuint flgas;
		GLuint fourCC;
		GLuint bpp;
		GLuint redMask;
		GLuint greenMask;
		GLuint blueMask;
		GLuint alphaMask;
	};

	typedef struct DDSCaps
	{
		GLuint caps;
		GLuint caps2;
		GLuint caps3;
		GLuint caps4;
	};

	typedef struct DDColorKey
	{
		GLuint lowVal;
		GLuint highVal;
	};

	typedef struct DDSurfaceDesc
	{
		GLuint size;
		GLuint flags;
		GLuint height;
		GLuint width;
		GLuint pitch;
		GLuint depth;
		GLuint mipMapLevels;
		GLuint alphaBitDepth;
		GLuint reserved;
		GLuint surface;

		DDColorKey ckDestOverlay;
		DDColorKey ckDestBlt;
		DDColorKey ckSrcOverlay;
		DDColorKey ckSrcBlt;

		DDPixelFormat format;
		DDSCaps caps;

		GLuint textureStage;
	};



	// ---------------------------------------------------------
	/// DDSテクスチャーを扱うクラス
	// ---------------------------------------------------------
	class DDS
	{
	public:
		GLuint ID;
		DDS();
		~DDS();
    
		GLuint Load(const char *fileName);

		// ゲッター
		GLuint getWidth() { return width; }
		GLuint getHeight() { return height; }


	protected:
		GLuint imageSize;
		GLubyte *imageData;
		GLenum format;
		GLuint internalFormat;
		GLuint width;
		GLuint height;
		GLuint bpp;

		GLuint numMipmaps;

		void decompressDDS();
		bool readDDS(const char *fileName);
	};
}

