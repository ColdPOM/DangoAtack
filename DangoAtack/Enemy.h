#pragma once
#include "Common.h"
#include "GameObject.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Shot.h"

class EnemyManager;

class Enemy : public GameObject
{
private:
	EnemyManager* mEnemyManager; // 自分を管理するマネージャー
	Player* mPlayer;     // プレイヤーの参照用
	int mState;			 // 敵の状態
	int mType;           // 敵の種類
	int mHitPoint;       // 敵のHP

	float mAtackTime; // 攻撃を出した時間の記録

	// カウンタとか
	int mAtackCount;   // 攻撃時間のカウント
	int mDeathCount;   // HPがゼロになってからの時間

	// フラグ
	bool mAtackComp; // 攻撃を出し切ったかどうか

	// ZAKO用
	float mScaleMeter; // 攻撃時などに使うスケール用
	bool mScaleMotion;   // モーション時拡大するか縮小するか
	float mMotionSpeed;  // モーション速度

	// FIRE用
	Shot* mShot;  // 発射する弾

	// STONE用
	int mWalkCount;        // ずり歩きのタイミングを計るためのカウント
	glm::vec3 mTargetPos;  // 攻撃時の目標地点
	bool mCameTargetPoint; // 目的地に着いたか
	bool mBarrier;         // 落下時は無敵

public:
	Enemy(void);
	~Enemy(void);

	enum TYPE { ZAKO, FIRE, STONE, BOSS };       // 敵の種類
	enum STATE { NEUTRAL, ATACK, DAMAGE }; // 敵の状態

	void Init(EnemyManager* EM, Player* player, int type);   // 初期化
	void Update();  // 更新

	// 状態の変更
	inline void ChangeState(STATE state) { mState = state; }  

	// 自身をエネミーマネージャーのアクティブリストから除外する
	void eraseMySelf();

	// アクション
	void Chase();  // プレイヤーを追跡
	void Atack();  // 攻撃する
	void Land();   // 着地処理
	void Damage(); // ダメージ処理
	void Turn(glm::vec3 target, float delta);  // 指定された方方を向く

	// ゲッター
	inline bool getIsBarrier() { return mBarrier; }
	inline int getType() { return mType; }
	inline int getState() { return mState; }
	inline int getHP() { return mHitPoint; }

	// セッター
	inline void setShot(Shot* shot) { mShot = shot; } // 使用する弾をセットする

	// 敵の配置
	void setEnemy(EnemyManager *EM, Player *player, int type, float x, float y, float z);

	// 敵をアクティブ化
	void Active();

};

