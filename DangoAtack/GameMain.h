#pragma once
#include "Common.h"
#include "Scene.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Sprite2D.h"
#include "Sound.h"

// -------------------------------------------------------------------------------
///  メインゲーム
// -------------------------------------------------------------------------------


class GameMain : public Scene
{
public:
	GameMain(GLFWwindow *window);
	~GameMain(void);

	// マウスホイール操作の取得
	static void Wheel(GLFWwindow *window, double x,	double y);

	void Init();    // 初期化
	SCENE Update();  // 更新
	void Draw();    // 描画



private:
	bool mPause; // 一時停止フラグ
	static float mWheelCount;

	CollisionManager mCollisionManager;

	// テクスチャ
	Sprite2D mPauseTex;      // ポーズ時の表示
	Sprite2D mGameOverTex;   // ゲームオーバー時の表示
	Sprite2D mGameClearTex;  //ゲームクリアー時の表示

	// サウンド
	Sound BGM;

	// オブジェクト
	Player mPlayer;
	EnemyManager mEnemys;
	Stage mStage;


	// リソースのロード
	static void Load(GameMain* self);
};

