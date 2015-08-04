#include "Shot.h"


Shot::Shot(void) : mLifeTime(5.0f * FPS)
{
}


Shot::~Shot(void)
{
}


// -------------------------------------------------------------
/// 弾の初期化
/// [in] SM 自身を管理しているマネージャーのアドレス
// -------------------------------------------------------------
void Shot::Init(ShotManager* SM){
	mBillboad.Load("fire.dds", "texture/");

	mShotManager = SM;
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale *= 0.3f;

	mIs = false;
	mSpeed = 0.09f;

	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = 1.0f;

	mIs = false;
	mFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mVisible = false;
	mDistance = glm::length(camPos - mPos);
}


// ---------------------------------------------------------------
/// 弾の更新
// ---------------------------------------------------------------
void Shot::Update(){
	if(!mIs) return;

	// 一定時間で消滅
	mLifeCount++;
	if(mLifeCount >= mLifeTime){
		Fin();
		return;
	}

	// ターゲットを追跡する
	glm::vec3 vec = glm::normalize(mTarget->getPos() - mPos) * mSpeed;
	mMoveVec.x = vec.x;
	mMoveVec.z = vec.z;

	// 移動
	mPos += mMoveVec;

	// モデルに座標等を適用
	mBillboad.setPos(mPos);
	mBillboad.setScale(mScale);

	mDistance = glm::length(camPos - mPos);
}

// --------------------------------------------------------------
/// 弾の描画
// --------------------------------------------------------------
void Shot::Draw(){
	mBillboad.DrawBill();
}


// ---------------------------------------------------------------
/// 弾の発射
/// [in] pos 発射位置
/// [in] target 目標とするオブジェクトのハンドル
// ---------------------------------------------------------------
void Shot::Trigger(const glm::vec3 &pos, GameObject* target){
	mIs = true;
	mVisible = true;
	mPos = pos + glm::vec3(0.0f, mBillboad.getSize().y/2, 0.0f);
	mTarget = target;
	mLifeCount = 0;
}


// -------------------------------------------------------------------
/// ショットマネージャーのアクティブリストに追加する
// -------------------------------------------------------------------
void Shot::pushActiveList(){
	mShotManager->pushActiveObject(this);
}

// ------------------------------------------------------------------
/// ショットマネージャーのアクティブリストから自身を除外する
// ------------------------------------------------------------------
void Shot::eraseMySelf(){
	for(int i = 0; i < mShotManager->getActiveList().size(); i++){
		if(mShotManager->getActiveList()[i] == this){
			mShotManager->eraseActiveObject(i);
			break;
		}
	}
}


// ----------------------------------------------------------------------
/// 弾の消滅
// ----------------------------------------------------------------------
void Shot::Fin(){
	mIs = false;
	mVisible = false;

	// マネージャーのアクティブリストから自身を外す
	eraseMySelf();	
}
