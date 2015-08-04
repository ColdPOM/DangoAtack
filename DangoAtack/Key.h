#pragma once
#include "Common.h"


// ---------------------------------------------------------------------------
/// キー状態を取得するクラス
/// このクラスを利用することにより簡単にキー状態を取得することができます
// ---------------------------------------------------------------------------
class Key
{
private:
	GLFWwindow *window; // ウィンドウハンドル

	bool mPreA;
	bool mNowA;
	bool mPreS;
	bool mNowS;
	bool mPreD;
	bool mNowD;
	bool mPreW;
	bool mNowW;
	bool mPreSpace;
	bool mNowSpace;

public:
	Key(void);
	~Key(void);

	
	void Init(GLFWwindow *win);  // キークラスの初期化
	void Update();               // キー状態の更新


	// ----------------------------------------------------------------------------
	/// キー状態の取得
	/// それぞれのキー状態を取得できます
	/// IsDown:押している, IsPush:押された, IsRelease:離した, IsUp:離している
	// ----------------------------------------------------------------------------
	
	// 何も押されていない
	bool NoKey();

	// Aキー
	inline bool IsDownA() { return mNowA; }
    inline bool IsPushA() { return !mPreA && mNowA; }
    inline bool IsReleaseA() { return mPreA && !mNowA; }
    inline bool IsUpA() { return !mNowA; }

	// Sキー
	inline bool IsDownS() { return mNowS; }
    inline bool IsPushS() { return !mPreS && mNowS; }
    inline bool IsReleaseS() { return mPreS && !mNowS; }
    inline bool IsUpS() { return !mNowS; }

	// Dキー
	inline bool IsDownD() { return mNowD; }
    inline bool IsPushD() { return !mPreD && mNowD; }
    inline bool IsReleaseD() { return mPreD && !mNowD; }
    inline bool IsUpD() { return !mNowD; }

	// Wキー
	inline bool IsDownW() { return mNowW; }
    inline bool IsPushW() { return !mPreW && mNowW; }
    inline bool IsReleaseW() { return mPreW && !mNowW; }
    inline bool IsUpW() { return !mNowW; }

	// Spaceキー
	inline bool IsDownSpace() { return mNowSpace; }
    inline bool IsPushSpace() { return !mPreSpace && mNowSpace; }
    inline bool IsReleaseSpace() { return mPreSpace && !mNowSpace; }
    inline bool IsUpSpace() { return !mNowSpace; }
};

