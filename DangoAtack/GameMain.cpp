#include "GameMain.h"
#include<map>

GameMain::GameMain(GLFWwindow *window):Scene(window)
{
	mScene = SCENE::GAMEMAIN_SCENE;

	// マウスホイール操作時のコールバックとしてwheel関数を登録
	glfwSetScrollCallback(window, Wheel); 
	Init();
}


GameMain::~GameMain(void)
{
}


// ---------------------------------------------------------------------
/// リソースのロード
/// [in] self 自クラスのポインタ
// ---------------------------------------------------------------------
void Load(GameMain* self){

}

float GameMain::mWheelCount = 1; // ホイールの回転数

// ----------------------------------------------------------------------
/// 初期化処理
// ----------------------------------------------------------------------
void GameMain::Init(){
	Scene::Init();
	mPauseTex.Load("texture/pause.dds");
	mGameOverTex.Load("texture/gameover.dds");
	mGameOverTex.setAlpha(0.0f);
	mGameClearTex.Load("texture/clear.dds");
	mGameClearTex.setAlpha(0.0f);
	mLoadComp = true;

	BGM.PlayBGM("sound/bgm2.wav", true);

	FadeIn(0.1f);

	mPause = false;
	mWheelCount = 1;
	mStage.Init();
	mPlayer.Init(&mMouse);
	mEnemys.Init(&mPlayer);

	mCollisionManager.setBossFlag(false);
	mStage.setBossFlag(false);

	camPos = mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f);
	lookAt = mPlayer.getPos() + mPlayer.getFront()*2.0f;

}


// -----------------------------------------------------------------------
/// マウスホイール操作の取得
/// マウスホイールの操作時コールバックとして呼ばれます
/// [in] *window 対象ウィンドウのハンドル
/// [in] x マウスホイールの横軸回転
/// [in] y マウスホイールの縦軸回転
// -----------------------------------------------------------------------
void GameMain::Wheel(GLFWwindow *window, double x,	double y){
	mWheelCount -= y;
	if(mWheelCount < 1) mWheelCount = 1;
	if(mWheelCount > 4) mWheelCount = 4;
};


// -----------------------------------------------------------------------
/// 更新処理
// -----------------------------------------------------------------------
Scene::SCENE GameMain::Update(){
	Scene::Update();
	// ポーズ
	if(mMouse.IsClickMiddleButton()){
		mPause = !mPause;
	}
	if(mPause) return mScene;

	// ステージのアップデート
	mStage.Update();

	// プレイヤーのアップデート
	mPlayer.Update();

	// 敵のアップデート
	mEnemys.Update();
	
	// 当たり判定
	if(!mEnemys.getActiveList()->empty())mCollisionManager.PlayerVSEnemy(mPlayer, mEnemys);   // プレイヤーと敵
	if(!mEnemys.getActiveList()->empty())mCollisionManager.EnemyVSEnemy(mEnemys);			    // 敵同士
	mCollisionManager.PlayerVSStage(mPlayer, mStage);									    // プレイヤーとステージ
	if(!mEnemys.getActiveList()->empty())mCollisionManager.EnemysVSStage(mEnemys, mStage);    // 敵とステージ
	mCollisionManager.PlayerVSShot(mPlayer, mEnemys.getShotManager());					    // 弾とプレイヤー

	// ボス戦突入
	if(mPlayer.getPos().z >= 760) {
		mCollisionManager.setBossFlag(true);
		mStage.setBossFlag(true);
		mPlayer.setBossFlag(true);
	}

	// カメラワーク
	// カメラ位置
	if(mPlayer.getState() != Player::STATE::ATACK) camPos += (mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f)*mWheelCount - camPos) / 3.0f;
	else camPos += (mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f)*mWheelCount - camPos) / 10.0f;
	

	// 注視点
	if(mPlayer.getState() != Player::STATE::ATACK && mPlayer.getState() != Player::STATE::AIM)lookAt += ((mPlayer.getPos() + mPlayer.getFront()*2.5f) - lookAt) / 5.0f;
	else if(mPlayer.getState() == Player::STATE::AIM) lookAt += ((mPlayer.getPos() + mPlayer.getFront()*5.0f) - lookAt) / 5.0f;
	else lookAt = mPlayer.getPos();

	mStage.setSkyPos(mPlayer.getPos());

	// BGMのソースの設定
	BGM.setPos(listnerPos[0], listnerPos[1], listnerPos[2]);

	// タイトルへ
	if((mEnemys.getGameClear() || mPlayer.getGameOver()) && mMouse.IsClickLeftButton() && !mFadeOutStart) FadeOut(2.0f);
	if(mFadeOutComp) ChangeScene(SCENE::TITLE_SCENE);

	if(!mEnemys.getGameClear() && mPlayer.getGameOver() &&  mGameOverTex.getAlpha() < 1.0f) mGameOverTex.setAlpha(mGameOverTex.getAlpha() + 0.01f);
	if(mEnemys.getGameClear() && mGameClearTex.getAlpha() < 1.0f) mGameClearTex.setAlpha(mGameClearTex.getAlpha() + 0.05f);

	return mScene;
}


// ----------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------
void GameMain::Draw(){
	mStage.Draw();
	mPlayer.Draw();
	mEnemys.Draw();

	if(mPause)mPauseTex.Draw();
	if(mPlayer.getGameOver())mGameOverTex.Draw();
	if(mEnemys.getGameClear())mGameClearTex.Draw();

	Scene::Draw();
}

