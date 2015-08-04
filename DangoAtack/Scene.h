#pragma once
#include "Common.h"
#include "Mouse.h"
#include "Sprite2D.h"
#include <thread>

// ------------------------------------------------------
/// シーンクラス
/// 継承して使う
// ------------------------------------------------------

class Scene
{
public: 
	
	enum SCENE { TITLE_SCENE, GAMEMAIN_SCENE}; // シーンの種類

	Scene(GLFWwindow *window);
	virtual ~Scene(void);

	virtual void Init();    // 初期化
	virtual SCENE Update();	// 更新
	virtual void Draw();    // 描画

	void FadeIn(float fadeTime);  // フェードイン
	void FadeOut(float fadeTime); // フェードアウト

	// シーンの切り替え
	/// [in] scene 切り替え先シーン
	inline void ChangeScene(SCENE scene) { mScene = scene; } 

	// 以降先シーンを返す
	// シーン切り替えの時のみ使用
	inline SCENE getScene() { return mScene; }

	inline bool LoadComp() { return mLoadComp; } // ロードが完了したかを返す


	
protected:
	Mouse mMouse; // マウスオブジェクト

	SCENE mScene; // シーン切り替え用。アップデート関数の戻り値

	bool mLoadComp;    // シーンのロード完了フラグ

	float mFadeTime;    // フェードに掛かる時間
	bool mFadeInStart;  // フェードイン開始フラグ
	bool mFadeInComp;   // フェードイン完了フラグ
	bool mFadeOutStart; // フェードアウト完了フラグ
	bool mFadeOutComp;  // フェードアウト完了フラグ


private:
	Sprite2D mFadeTex; // フェード用テクスチャ
};

