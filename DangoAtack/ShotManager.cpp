#include "ShotManager.h"


ShotManager::ShotManager(void)
{
}


ShotManager::~ShotManager(void)
{
	delete[] mShots;
}

// ----------------------------------------------------------
/// 初期化
/// [in] nom 生成させる弾の数
// ----------------------------------------------------------
void ShotManager::Init(const int nom){
	mShotCount = nom;
	mShots = new Shot[mShotCount]();

	for(int i = 0; i < mShotCount; i++){
		mShots[i].Init(this);
	}
}


// -----------------------------------------------------------
/// 更新
// -----------------------------------------------------------
void ShotManager::Update(){
	for(int i = 0; i < mShotCount; i++){
		mShots[i].Update();
	}
}


// -----------------------------------------------------------
/// 描画
// -----------------------------------------------------------
void ShotManager::Draw(){
	// 描画順に並べ替え（基準はカメラとの距離）
	std::sort(mActiveList.begin(), mActiveList.end(), 
		[](Shot*& left, Shot*& right) { return left->getDistance() > right->getDistance();});


	// アクティブになっているものだけ描画
	for(int i = 0; i < mActiveList.size(); i++){
		mActiveList[i]->Draw();
	}
}
