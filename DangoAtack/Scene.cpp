#include "Scene.h"

// ------------------------------------------------------
/// コンストラクタ
/// [in] window 使用するウィンドウのハンドル
// ------------------------------------------------------
Scene::Scene(GLFWwindow *window):
	mLoadComp(false),
	mFadeTime(0.0f),
	mFadeInStart(false),
	mFadeInComp(false),
	mFadeOutStart(false),
	mFadeOutComp(false)
{
	mMouse.Init(window);
	listnerPos[0] = 0.0f;
	listnerPos[1] = 0.0f;
	listnerPos[2] = 0.0f;
}

// ------------------------------------------------------
/// デストラクタ
// ------------------------------------------------------
Scene::~Scene(void)
{
}

// -----------------------------------------------------------------
/// 初期化
// -----------------------------------------------------------------
void Scene::Init(){
	mFadeTex.Load("texture/black.dds");
	mFadeTex.setPos(WIN_W/2.0f, WIN_H/2.0f);
	mFadeTex.setScale(WIN_W, WIN_H);
	mFadeTex.setAlpha(0.0f);
}

// -----------------------------------------------------------------
/// 更新
// -----------------------------------------------------------------
Scene::SCENE Scene::Update(){
	mMouse.Update(); // マウス状態の更新

	// フェードイン処理
	if(mFadeInStart && !mFadeInComp){
		mFadeTex.setAlpha(mFadeTex.getAlpha() - 1.0 / (mFadeTime*FPS));
		if(mFadeTex.getAlpha() <= 0.0){
			mFadeTex.setAlpha(0.0f);
			mFadeInComp = true;
		}
	}

	// フェードアウト処理
	else if(mFadeOutStart && !mFadeOutComp){
		mFadeTex.setAlpha(mFadeTex.getAlpha() + 1.0 / (mFadeTime*FPS));
		if(mFadeTex.getAlpha() >= 1.0){
			mFadeTex.setAlpha(1.0f);
			mFadeOutComp = true;
		}
	}

	return mScene;
}

// -----------------------------------------------------------------
/// 描画
/// 継承先のDraw関数の最後に必ず実行する必要がある
// -----------------------------------------------------------------
void Scene::Draw(){
	glDisable(GL_DEPTH_TEST);
	mFadeTex.Draw();
	glEnable(GL_DEPTH_TEST);
}


// -----------------------------------------------------------------
/// フェードイン開始
// -----------------------------------------------------------------
void Scene::FadeIn(float fadeTime){
	mFadeTex.setAlpha(1.0f);
	mFadeTime = fadeTime;
	mFadeInComp = false;
	mFadeInStart = true;
	mFadeOutStart = false;

}


// -----------------------------------------------------------------
/// フェードアウト開始
// -----------------------------------------------------------------
void Scene::FadeOut(float fadeTime){
	mFadeTex.setAlpha(0.0f);
	mFadeTime = fadeTime;
	mFadeOutComp = false;
	mFadeOutStart = true;
	mFadeInStart = false;
}
