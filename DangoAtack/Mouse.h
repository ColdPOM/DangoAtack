#pragma once
#include "Common.h"

class Mouse
{
private:
	GLFWwindow *window;

	double mPosX, mPosY; // マウスカーソル位置
	glm::vec2 mClickPos; // 最後にクリックされた座標

	bool mPreLeftButton;
	bool mNowLeftButton;
	bool mPreRightButton;
	bool mNowRightButton;
	bool mPreMiddleButton;
	bool mNowMiddleButton;

public:
	Mouse(void);
	~Mouse(void);

	void Init(GLFWwindow *win); // 初期化
	void Update();              // マウス状態の更新
	
	glm::vec2 getMousePos();												 // マウス座標の取得
	inline glm::vec2 getClickPos() { return mClickPos;}						 // 最後のクリック位置の取得
	inline glm::vec2 getPullVec() { return getMousePos() - getClickPos(); }  // 最後のクリック地点からマウス座標へのベクトル

	// ----------------------------------------------------------------------------
	/// マウスボタンの状態取得
	/// それぞれのボタン状態を取得できます
	/// IsDown:押している, IsClick:クリックされた, IsRelease:離した, IsUp:離している
	// ----------------------------------------------------------------------------

	// 左ボタン
	inline bool IsDownLeftButton() { return mNowLeftButton; }
    inline bool IsClickLeftButton() { return !mPreLeftButton && mNowLeftButton; }
    inline bool IsReleaseLeftButton() { return mPreLeftButton && !mNowLeftButton; }
    inline bool IsUpLeftButton() { return !mNowLeftButton; }

	// 右ボタン
	inline bool IsDownRightButton() { return mNowRightButton; }
    inline bool IsClickRightButton() { return !mPreRightButton && mNowRightButton; }
    inline bool IsReleaseRightButton() { return mPreRightButton && !mNowRightButton; }
    inline bool IsUpRightButton() { return !mNowRightButton; }

	// 中ボタン
	inline bool IsDownMiddleButton() { return mNowMiddleButton; }
    inline bool IsClickMiddleButton() { return !mPreMiddleButton && mNowMiddleButton; }
    inline bool IsReleaseMiddleButton() { return mPreMiddleButton && !mNowMiddleButton; }
    inline bool IsUpMiddleButton() { return !mNowMiddleButton; }
};

