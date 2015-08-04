#pragma once
#include "Enemy.h"
#include "Player.h"
#include "ShotManager.h"
#include <vector>

class Enemy;

class EnemyManager
{
private:
	bool GameClear; // ゲームクリアフラグ

	Player* mPlayer;                    // プレイヤーオブジェクトのポインタ
	Enemy* mEnemys;                     // 敵オブジェクト配列
	const int mEnemyCount;              // 出現できる敵の数
	std::vector<Enemy*> mActiveList;    // アクティブリスト

	ShotManager mShotManager; // 敵が放つ弾はショットマネージャーで管理

public:
	EnemyManager(void);
	~EnemyManager(void);

	void Init(Player *player);    // 初期化
	void Update();  // 更新
	void Draw();    // 描画

	enum TYPE { ZAKO, FIRE, STONE, BOSS };  // 敵の種類
	void SetEnemy(int nom, TYPE type, float x, float y, float z); // 敵を配置する
	void ActiveEnemy(int beginNom, int endNom); // 敵をアクティブ状態にする

	// ゲッター
	inline Enemy* getEnemys() { return mEnemys ; }
	inline int getEnemyCount() { return mEnemyCount; }
	inline std::vector<Enemy*>* getActiveList() { return &mActiveList; }
	inline ShotManager* getShotManager() { return &mShotManager; }
	inline bool getGameClear() { return GameClear; }

	// アクティブリストの操作
	inline void pushActiveObject(Enemy* enemy) { mActiveList.push_back(enemy); }       // 末尾に判定を行うEnemyへの参照を追加 
	inline void eraseActiveObject(int i) { mActiveList.erase(mActiveList.begin() + i); }  // アクティブリストのi番目の要素を削除
};

