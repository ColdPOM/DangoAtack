#pragma once
#include "WAVE.h"
#include <vector>
#include <thread>

// ---------------------------------------------------------------------
/// サウンドを扱うクラス
/// 対応ファイル形式: WAVE
// ---------------------------------------------------------------------

class Sound
{
public:
	Sound(void);
	~Sound(void);

	// 音量調整 (0.0 ～ 1.0）
	inline void setVolume(float value) { alSourcef(mSource, AL_GAIN, value); } 

	// BGMの操作
	void PlayBGM(const char* fileName, bool loop = false);  // BGMの再生
	void PlayBGM(const char* fileName, float startpoint, float endpoint = -1, bool loop = false);  // 範囲を指定してBGMの再生
	void PlayBGM();                                           // 二回目以降の再生
	inline void Stop() { alSourceStop(mSource); }             // 停止
	inline void Pause() { alSourcePause(mSource); }           // 一時停止

	// SEの操作
	void LoadSE(const char* fileName);  // SEのロード
	void PlaySE();  // SEの再生
	void PlaySE(float x, float y, float z);  // 座標を指定してSEの再生

	// セッター
	inline void setPos(float x, float y, float z) { mPos[0] = x, mPos[1] = y, mPos[2] = z; 
	alSourcefv(mSource, AL_POSITION, mPos);
	}

	// ゲッター
	inline bool LoadComp() { return mLoadFlag; } // ロード完了フラグの取得
	inline ALint getState() { alGetSourcei(mSource, AL_SOURCE_STATE, &mState); return mState; } // サウンドの状態取得


private:
	enum TYPE { NOTYPE, BGM, SE}; // サウンドのタイプ、初期状態はNOTYPE

	static void Streaming(const char* fileName, Sound* self); // ストリーミング再生

	TYPE mType;                // サウンドのタイプ
	ALint mState;              // サウンドの状態
	bool mLoadFlag;            // ロード完了フラグ
	float mStartPoint;         // 再生開始位置
	float mEndPoint;           // 再生終了位置
	const ALuint mBufferSize;  // ストリーミング再生時のバッファの数
	ALuint mSource;            // ソース
	float mPos[3];             // ソースの位置
};

