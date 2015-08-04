#include "GameObject.h"


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

// --------------------------------------------------------
/// ゲームオブジェクトの初期化
// --------------------------------------------------------
void GameObject::Init(){
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mRotate = glm::vec3(0.0f, 0.0f, 0.0f);

	mIs = false;
	mFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mVisible = false;
	mLand = false;

	mStopCount = -1;
	mInvaildCount = -1;

	mStopFlag = false;
	mIsCol = true;
}


// -------------------------------------------------------------------
/// ゲームオブジェクトの更新
/// 動きのあるオブジェクトは継承先のUpdate関数の先頭でこの関数を呼ぶ
// -------------------------------------------------------------------
void GameObject::Update(){
	if(!mIs) return;

	// ヒットストップ時間カウント
	if(mStopCount >= 0) mStopCount--;
	else mStopFlag = false;

	// 無敵時間カウント
	if(mInvaildCount >= 0) mInvaildCount--;
	else {
		mIsCol = true;
		mVisible = true;
	}
}


// --------------------------------------------------------------------
/// モデルの描画
// --------------------------------------------------------------------
void GameObject::Draw(){
	if(!mVisible || !mIs) return;

	// モデルに座標等を適用
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

	model.Draw();
}

