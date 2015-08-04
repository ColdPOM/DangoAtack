#pragma once
#include "Common.h"
#include "Shot.h"
#include <vector>

class Shot;

class ShotManager
{
public:
	ShotManager(void);
	~ShotManager(void);

	void Init(const int nom);    // 初期化
	void Update();				 // 更新
	void Draw();				 // 描画

	// ゲッター
	inline Shot* getShots() { return mShots ; }
	inline int getShotCount() { return mShotCount; }
	inline std::vector<Shot*> getActiveList() { return mActiveList; }

	// アクティブリストの操作
	inline void pushActiveObject(Shot* Shot) { mActiveList.push_back(Shot); }    // アクティブリストに追加 
	inline void eraseActiveObject(int i) {mActiveList.erase(mActiveList.begin() + i); }  // アクティブリストのi番目の要素を削除
	


private:
	Shot* mShots;                  // 弾オブジェクト配列
	int mShotCount;                // 弾の数
	std::vector<Shot*> mActiveList;    // アクティブリスト
};

