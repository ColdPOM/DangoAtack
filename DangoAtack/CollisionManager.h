#pragma once
#include "Collision.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Stage.h"
#include "Sound.h"

class CollisionManager
{
private:
	bool BossBattle; // ボス戦フラグ

	Sound mHitSE;

public:
	CollisionManager(void);
	~CollisionManager(void);

	void PlayerVSEnemy(Player &player, EnemyManager &EM); // プレイヤーと敵
	void EnemyVSEnemy(EnemyManager &EM);				  // 敵同士の当たり判定
	void PlayerVSStage(Player &player, Stage &stage);	  // プレイヤーとステージ
	void EnemysVSStage(EnemyManager &EM, Stage &stage);   // 敵とステージ
	void PlayerVSShot(Player &player, ShotManager* SM);   // 弾とプレイヤー

	// ボスバトルフラグの設定
	inline void setBossFlag(bool flag) { BossBattle = flag; }
};

