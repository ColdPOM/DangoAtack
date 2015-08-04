#pragma once
#include "Common.h"

// -----------------------------------------------------------------------------------
/// WAVEファイルの読み込みを行うクラス
// -----------------------------------------------------------------------------------

namespace wave{

	// RIFFヘッダ
	struct RiffHeader {
		ALuint riff; // RIFFの識別子"RIFF"
		ALint size;  // riffとsizeを除いたファイルサイズ
		ALuint type; // RIFFの種類"WAVE"
	};

	// フォーマットチャンク
	struct FormatChunk {
	  ALuint id;            // チャンク識別子("fmt")
	  ALint size;           // idとsizeを除いたチャンクサイズ
	  ALshort format;       // フォーマットID
	  ALushort channels;    // チャンネル数
	  ALuint samplerate;    // サンプリング周波数(Hz)
	  ALuint bytepersec;    // １秒間の録音に必要なバイト数 (バイト／秒)　
	  ALushort blockalign;  // データのブロックサイズ  (Byte/sample×チャンネル数)
	  ALushort bitswidth;   // サンプルあたりのビット数 (bit/sample)
	};

	// フォーマットチャンク拡張版
	struct FormatChunkEx {
	  FormatChunk* formatChunk;
	  ALushort extended_size;
	  ALubyte* extended;
	};

	// データチャンク
	struct DataChunk {
	  ALuint id;   // チャンク識別子("data")
	  ALint size;  // 波形データのバイト数

	  ALubyte* waveformData; // 波形データ
	};



	class WAVE
	{
	public:
		WAVE(void);
		~WAVE(void);

		void Load(const char* fileName, ALuint* buffer);                 // 読み込み
		void LoadHeaderAndFormat(std::ifstream* file);                   // 波形データ直前までを読み込む
		void LoadData(std::ifstream* file, ALuint* buffer, int size);    // 指定サイズ分データを読み込む

		// ゲッター
		inline RiffHeader getHeader() { return header; }   // ヘッダー情報の取得
		inline FormatChunk getFormat() { return format; }  // フォーマット情報の取得
		inline DataChunk getData() { return data; }        // データ情報の取得


	private:
		RiffHeader header;
		FormatChunk format;
		FormatChunkEx formatEx;
		DataChunk data;

		bool mLoadFlag; // ロード完了フラグ
	};

}

