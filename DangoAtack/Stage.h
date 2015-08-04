#pragma once
#include "Model.h"

class Stage
{
private:
	bool BossBattle; // ボス戦フラグ

	Model mGround; // 床
	Model mLand;   // ボス戦場
	Model mSky;    // 空
	Model mTree;  // 木
	glm::vec3* mTreePos; // 木の座標リスト
	const int mTreeCount; // 木の数

public:
	Stage(void);
	~Stage(void);

	void Init();   // 初期化
	void Update(); // 更新
	void Draw();   // 描画

	// ゲッター
	inline Model* getGround() { return &mGround; } // 床モデルの取得
	inline Model* getLand() { return &mLand; } // ボス戦場モデルの取得
	inline float getTreeHeight() { return mTree.getSize().y; } //木の高さを取得
	inline int getTreeCount() { return mTreeCount; } // 木の数を取得
	inline glm::vec3* getTreePos() { return mTreePos; } // 木の座標リストの取得

	// 空オブジェクトの座標指定
	inline void setSkyPos(glm::vec3 pos) { return mSky.setPos(pos); }

	// ボスバトルフラグの設定
	inline void setBossFlag(bool flag) { BossBattle = flag; } 
};

