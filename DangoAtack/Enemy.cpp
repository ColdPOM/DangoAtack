#include "Enemy.h"
#include "DebugGL.h"


Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}


// -------------------------------------------------------------
/// 敵情報の初期化
/// 敵を生成する場合は必ず1度呼び出す必要があります
/// [in] EM 自身を管理するマネージャー
/// [in] player プレイヤーの参照用ポインタ
/// [in] type 敵の種類
// -------------------------------------------------------------
void Enemy::Init(EnemyManager* EM, Player* player, int type){
	GameObject::Init();
	mType = type;

	// タイプごとの設定
	switch (mType)
	{
	// 雑魚
	case TYPE::ZAKO : 
		if(!model.IsLoad()) model.Load("ene01.pmd", "model/enemy");
		mHitPoint = 2;
		mSpeed = 0.065f;
		mMotionSpeed = 0.005f;
		break;

	// 火をふく敵
	case TYPE::FIRE:
		if(!model.IsLoad()) model.Load("ene02.pmd", "model/enemy");
		mHitPoint = 3;
		mSpeed = 0.05f;
		break;

	// 岩っぽい敵
	case TYPE::STONE :
		if(!model.IsLoad()) model.Load("ene03.pmd", "model/enemy");
		mHitPoint = 3;
		mSpeed = 0.1f;
		break;

	case TYPE::BOSS:
		if(!model.IsLoad()) model.Load("boss.pmd", "model/enemy");
		mHitPoint = 10;
		mSpeed = 0.3f;
		break;

	default:
		std::cout << "使用できない敵のタイプを指定しています" << std::endl;
		break;
	}

	// 共通の設定
	mEnemyManager = EM;
	mPlayer = player;
	mShot = nullptr;
	mIs = false;
	mVisible = true;
	mAtackTime =  glfwGetTime();

	mAtackCount = 0;
	mAtackComp = false;
	mDeathCount = 0;

	mScaleMeter = 1.0f;
	mWalkCount = 0;
	mCameTargetPoint = false;
	mBarrier = false;

	mState = STATE::NEUTRAL;
}


// -----------------------------------------------------------------
/// 敵を配置
/// 初期化処理も同時に行う
/// [in] EM 自身を管理するマネージャー
/// [in] player プレイヤーの参照用ポインタ
/// [in] type 敵の種類
/// [in] x,y,z 配置する座標
// -----------------------------------------------------------------
void Enemy::setEnemy(EnemyManager *EM, Player *player, int type, float x, float y, float z){
	Init(EM, player, type);
	mPos = glm::vec3(x, y, z);
}



// --------------------------------------------------------------
/// 敵の更新
/// 敵の情報を更新
// --------------------------------------------------------------
void Enemy::Update(){
	if(!mIs) return;
	GameObject::Update();
	if(mStopFlag) return;

	// 重力
	if(!mLand) mMoveVec.y -= gravity;

	// 地面摩擦
	if(mLand){
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.05f;
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
	}


	// 敵の種類ごとの処理
	switch (mType){
	// ----------------------------------------雑魚-----------------------------------------------------
	case TYPE::ZAKO:
		// 攻撃
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x*1.5f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(mAtackCount >= 60){ // ニュートラル状態に戻る
				ChangeState(STATE::NEUTRAL);
				mScaleMeter = 1.0f;
				mAtackCount = 0;
			}
			else if(mAtackComp && mScaleMeter > 1.0f){ // 攻撃を終え縮む
				mScaleMeter -= 0.1f;
			}
			else if(!mAtackComp && mAtackCount >= 30 && mScaleMeter < 2.5f){ // 膨らむ
				mScaleMeter += 0.5f;
				if(mScaleMeter >= 2.5f) mAtackComp = true; // 攻撃完了
			}
			else if (!mAtackComp)mScaleMeter -= 0.012f; // 予備動作

			setScale(mScaleMeter);
		}

		// プレイヤーの追跡
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// アニメーション
		if(mState == STATE::NEUTRAL){
			if(glm::length(mPlayer->getPos() - mPos) >= 20)mMotionSpeed = 0.005f;

			if(mScaleMotion) mScale.y -= mMotionSpeed;
			else mScale.y += mMotionSpeed;
			if(mScaleMotion && mScale.y <= 0.8) {
				mScaleMotion = false;
				mScale.y = 0.8f + mMotionSpeed;
			}
			if(!mScaleMotion && mScale.y >= 1) {
				mScaleMotion = true;
				mScale.y = 1 - mMotionSpeed;
			}
		}
		break;



		// ----------------------------------------火をふく敵--------------------------------------------------
	case TYPE::FIRE:
		// 攻撃
		if(mState == STATE::NEUTRAL && !mShot->getIs() && glm::length(mPlayer->getPos() - mPos) < 15 && glfwGetTime() - mAtackTime >= 7.0f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
			mAtackTime = glfwGetTime();
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(!mAtackComp && mAtackCount >= 30 && mScaleMeter > 1.0f){ // 火を吹く
				mScaleMeter -= 0.1f;
				if(mScaleMeter <= 1.0f) {
					mShot->pushActiveList();
					mShot->Trigger(mPos + mFront*(getSize().x/2), mPlayer);
					mAtackComp = true;
					mScaleMeter = 1.0f;
					mAtackCount = 0;
					ChangeState(STATE::NEUTRAL);
				}
			}
			else if (!mAtackComp)mScaleMeter += 0.012f; // 予備動作

			setScale(mScaleMeter);
			Turn(mPlayer->getPos(), 10); // プレイヤーの方を向く
		}

		// プレイヤーの追跡
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// アニメーション
		if(mState == STATE::NEUTRAL){

			if(mScaleMotion) mScale.y -= mMotionSpeed;
			else mScale.y += mMotionSpeed;
			if(mScaleMotion && mScale.y <= 0.8) {
				mScaleMotion = false;
				mScale.y = 0.8f + mMotionSpeed;
			}
			if(!mScaleMotion && mScale.y >= 1) {
				mScaleMotion = true;
				mScale.y = 1 - mMotionSpeed;
			}
		}
		break;



		// ----------------------------------------石の敵----------------------------------------------------
	case TYPE::STONE:
		// 攻撃
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x*2){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mWalkCount = 0;
			mTargetPos = mPlayer->getPos() + glm::vec3(0.0f, 10.0f, 0.0f);
			mCameTargetPoint = false;
		}
		if(mState == STATE::ATACK) {
			// 目標地点へのベクトル
			glm::vec3 vec = mTargetPos - mPos;
			if(!mCameTargetPoint && glm::length(vec) > 0.1f){ // 目標の上空に向かう
				mMoveVec.y += gravity; // 重力をかき消す
				mPos += glm::normalize(vec)*0.5f;
				Turn(mTargetPos, 5);

				if(glm::length(vec) <= 1.0f){ // 目標地点に到着
					mCameTargetPoint = true;
					mMoveVec += glm::vec3(0.0f, -1.0f, 0.0f);
					mBarrier = true;
				}
			}
			else if(mLand){ // 着地
				mAtackCount++;
				mBarrier = false;
				if(mAtackCount >= 120){ // ニュートラル状態に戻る
					ChangeState(STATE::NEUTRAL);
					mAtackCount = 0;
				}
			}
		}

		// プレイヤーの追跡 (ずりずりと引きずるように進む)
		else if(mState == STATE::NEUTRAL){
			mWalkCount++;
			if(mWalkCount < 30)	Chase();
			else if(mWalkCount >= 60) mWalkCount = 0;
		}

		break;

		// ----------------------------------------ボス----------------------------------------------------
		case TYPE::BOSS:
		// 攻撃
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x * 0.9f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(mAtackCount >= 40){ // ニュートラル状態に戻る
				ChangeState(STATE::NEUTRAL);
				mScaleMeter = 1.0f;
				mAtackCount = 0;
			}
			else if(mAtackComp && mScaleMeter > 1.0f){ // 攻撃を終え縮む
				mScaleMeter -= 0.1f;
			}
			else if(!mAtackComp && mAtackCount >= 15 && mScaleMeter < 2.5f){ // 膨らむ
				mScaleMeter += 0.5f;
				if(mScaleMeter >= 2.5f) mAtackComp = true; // 攻撃完了
			}
			else if (!mAtackComp)mScaleMeter -= 0.012f; // 予備動作

			setScale(mScaleMeter);
		}

		// プレイヤーの追跡
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// アニメーション
		if(mState == STATE::NEUTRAL){
			if(glm::length(mPlayer->getPos() - mPos) >= 20)mMotionSpeed = 0.005f;

			if(mScaleMotion) mScale.y -= mMotionSpeed;
			else mScale.y += mMotionSpeed;
			if(mScaleMotion && mScale.y <= 0.8) {
				mScaleMotion = false;
				mScale.y = 0.8f + mMotionSpeed;
			}
			if(!mScaleMotion && mScale.y >= 1) {
				mScaleMotion = true;
				mScale.y = 1 - mMotionSpeed;
			}
		}
		break;
	}






	// 移動
	mPos += mMoveVec;

	// HPゼロ
	if(mHitPoint <= 0) mDeathCount++;

	// HPゼロになってから一定時間で消滅
	if(mDeathCount >= FPS * 3){
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// 落ちた
	if(mPos.y <= -50) {
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// プレイヤーと距離が離れすぎると消滅
	if(mIs && mPlayer->getPos().z - mPos.z  >= 200){
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// モデルに座標等を適用
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

}

// ----------------------------------------------------------------
/// 着地
// ----------------------------------------------------------------
void Enemy::Land(){
	if(!mLand) {
		if(mState == STATE::DAMAGE) ChangeState(STATE::NEUTRAL);
		mLand = true;
		mRotate.x = 0;
		mMoveVec.y = 0;
	}
}


// --------------------------------------------------------------
/// プレイヤーの追跡
// --------------------------------------------------------------
void Enemy::Chase(){
	glm::vec3 vec = mPlayer->getPos() - mPos;

	// キャラクターの移動
	glm::vec3 v = glm::normalize(glm::vec3(vec.x, 0, vec.z)) * mSpeed;
	mMoveVec.x = v.x;
	mMoveVec.z = v.z;

	Turn(mPlayer->getPos(), 10);
}


// --------------------------------------------------------------
/// ダメージ処理
/// プレイヤーのアタックを受けた時に使用します
/// [in] AtackVec プレイヤーのアタック時の移動ベクトル
// --------------------------------------------------------------
void Enemy::Damage(){
	ChangeState(STATE::DAMAGE);
	mLand = false;
	mPos += glm::vec3(0.0f, 0.1f, 0.0f); // ちょっと浮かせる
	mRotate.x = 20;
	model.setRotate(mRotate);
	setScale(1.0f);
	if(glm::length(mPlayer->getMoveVec()) >= 0.6f)mHitPoint--;

	float vecLengthY = glm::length(mPlayer->getMoveVec()); // 縦方向の吹っ飛び度合い
	float vecLengthXZ = 0.2f; // 横方向の吹っ飛び度合い
	if(mHitPoint <= 0) {
		vecLengthY = 5.0f;
		vecLengthXZ = 3.0f;
	}

	mMoveVec = mPlayer->getMoveVec()*vecLengthXZ + glm::vec3(0.0f, 0.1f*vecLengthY*3, 0.0f); // 吹っ飛び度合い
	InvaildCol(1.0f); // 無敵化
}


// ----------------------------------------------------------------------------
/// 指定された方を向く(Y軸回転のみ）
/// [in] delta 振り向きにかかる間隔。大きいほどゆっくり振り向く
// ----------------------------------------------------------------------------
void Enemy::Turn(glm::vec3 target, float delta){
	glm::vec3 vec = target - mPos;

	float r;
	// 敵の正面ベクトルとプレイヤー方向ベクトル間の角度
	float dot = glm::dot(glm::vec2(mFront.x, mFront.z), glm::normalize(glm::vec2(vec.x, vec.z)));
	if(glm::abs(dot - 1) > 0.0001f){
		r = glm::acos(dot) * 180.0f / glm::pi<float>();
		// 角度を敵正面から半時計周りがプラス、時計回りがマイナスの角度にする
		glm::vec3 a = glm::rotateY(mFront, glm::pi<float>()/2.0f);
		glm::vec2 b = glm::vec2(a.x, a.z);
		if(glm::dot(b, glm::normalize(glm::vec2(vec.x, vec.z))) < 0) r = -r;
	}
	else r = 0;

	// 回転させる
	mRotate.y += r/delta;
	mFront = glm::rotateY(mFront, r/delta * glm::pi<float>() / 180.0f);
}


// ------------------------------------------------------------------
/// エネミーマネージャーのアクティブリストから自身を除外する
// ------------------------------------------------------------------
void Enemy::eraseMySelf(){
	for(int i = 0; i < mEnemyManager->getActiveList()->size(); i++){
		if(mEnemyManager->getActiveList()->at(i) == this){
			mEnemyManager->eraseActiveObject(i);
			break;
		}
	}
}

// -------------------------------------------------------------------
/// 敵をアクティブにする
// -------------------------------------------------------------------
void Enemy::Active(){
	mIs = true;
	mEnemyManager->pushActiveObject(this);
}