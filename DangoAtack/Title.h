#pragma once
#include "Common.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "Sound.h"

class Title : public Scene
{
public:
	Title(GLFWwindow *window);
	~Title(void);

	void Init();    // 初期化
	SCENE Update();	// 更新
	void Draw();    // 描画


private:
	Sprite2D mBackTex;  // 背景テクスチャ
	Sprite2D mStartTex; // クリックスタート文字

	Sound mBGM;     // BGM
	Sound mStartSE; // 画面クリック時の音

	float mFadeSpeed; // 点滅の速さ
	bool mFadeFlag;   // クリックスタートの点滅に使う
	bool mStart;      // スタートが押された
};

