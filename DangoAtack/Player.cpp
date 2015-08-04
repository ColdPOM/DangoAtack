#include "Player.h"


Player::Player(void)
{
}

Player::~Player(void)
{
}


// -------------------------------------------------------------
/// プレイヤー情報の初期化
/// プレイヤーを生成する場合は必ず1度呼び出す必要があります
// -------------------------------------------------------------
void Player::Init(Mouse *mouse){
	GameObject::Init();
	if(!model.IsLoad()) model.Load("dango.pmd", "model/dango");
	mHeartTex.Load("texture/heart.dds");

	mJumpSE.LoadSE("sound/jump.wav");
	mJumpSE.setVolume(0.5f);
	mAtackSE.LoadSE("sound/atack.wav");

	BossBattle = false;
	GameOver = false;

	mMouse = mouse;

	mHitPoint = 5;

	mPos = glm::vec3(0.0f, 5.0f, 0.0f);
	mRestartPos = mPos;
	mRotate.x = 20.0f;

	mIs = true;
	mVisible = true;
	mSpeed = 0.2f;
	mFlash = false;
	mFlashCount = 0;
	mLandCount = 0;

	mMotionSpeed = 0.012f;

	mState = STATE::JUMP;
	mFace = FACE::NOMAL;
}


// -------------------------------------------------------------
/// プレイヤーの更新
/// プレイヤー情報の更新を行います
// -------------------------------------------------------------
void Player::Update(){
	GameObject::Update();
	if(mStopFlag) return;

	if(mHitPoint <= 0){
		if(getScale().x > 0.05f) {
			mScale *= 0.985f;
			mRotate += glm::vec3(0.0f, 10.0f, 0.0f);
		}
		else {
			mScale = glm::vec3(0.01f, 0.01f, 0.01f);
			GameOver = true; // ゲームオーバー
		}

		return;
	}

	// ---操作---
	// 移動
	if(mMouse->IsDownRightButton())Move(mMouse->getMousePos());
	// 動作準備
	if (mMouse->IsClickLeftButton()) Click();
	// ジャンプ
	if (mMouse->IsReleaseLeftButton()) Jump();
	// 攻撃
	if (mMouse->IsDownLeftButton()) Aim(mMouse->getPullVec());
	if (mMouse->IsReleaseLeftButton()) Atack(mMouse->getPullVec());



	// 重力
	if(!mLand) mMoveVec.y -= gravity;

	if(mLand){
		mLandCount++;
		// 復活ポイントの更新
		if(mLandCount >= 60){
			mRestartPos = mPos;
			mLandCount = 0;
		}

		// 地面摩擦
		if(!(mMouse->IsDownRightButton() && mState == STATE::NEUTRAL)){
			if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
			if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		}
	}


	// 各状態ごとの処理
	switch (mState)
	{
	// 通常時
	case STATE::NEUTRAL:
		// プレイヤーのアニメーション
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

		break;

	// しゃがみ時
	case STATE::SIT:
		if(!mLand)break;
		mKeepTime++;
		// ブレーキ
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		break;

	// ジュンプ時
	case STATE::JUMP:

		break;

	// 狙い
	case STATE::AIM:
		// ブレーキ
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		break;

	// 攻撃時
	case STATE::ATACK:
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f;
		if(glm::length(mMoveVec) <= 0.1f){
			ChangeState(STATE::NEUTRAL);
			mRotate.x = 0;
		}
		break;

	default:
		printf("プレイヤーのmStateに使用できない値を指定しています\n");
		break;
	}
	
	
	// 移動
	mPos += mMoveVec;


	// 落ちた
	if(mPos.y <= -50) {
		mPos = mRestartPos;
		if(BossBattle) mPos = glm::vec3(10.0f, 0.1f, 800.0f);
		mMoveVec *= 0;
		mVisible = true;
		mFlash = 0;
		mFlashCount = 0;
		mHitPoint--;
		InvaildCol(3); // 無敵化
	}


	// 点滅
	if(mFlash){
		mFlashCount++;
		if(mFlashCount >= 5){
			mVisible = !mVisible;
			mFlashCount = 0;
		}
	}
	if(mIsCol) mFlash = false;


	// モデルに座標等を適用
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

}

// ----------------------------------------------------------------
/// プレイヤーの描画
// ----------------------------------------------------------------
void Player::Draw(){
	GameObject::Draw();

	// HPの表示
	if(mHitPoint <= 0) return;
	for(int i = 0; i < mHitPoint; i++){
		mHeartTex.Draw(10 + (mHeartTex.getWidth() + 5)*i, 10);
	}

}


// ----------------------------------------------------------------
/// プレイヤーの移動
/// キー入力に応じてプレイヤーを移動させます
/// プレイヤーのUpdate()呼び出しの前に一度だけ呼び出してください
/// [in] right, left, front, back　それぞれのキー入力判定値
// ----------------------------------------------------------------
void Player::Move(const glm::vec2 &mousePos){
	
	// 通常時意外または空中では移動できない
	if(mState != STATE::NEUTRAL || !mLand) return;

	glm::vec2 vec = mousePos - glm::vec2(WIN_W/2, WIN_H/2);

	// キャラクターの移動
	glm::vec3 v = glm::normalize(glm::vec3(-vec.x, 0, -vec.y)) * 0.06f;
	mMoveVec.x += v.x;
	mMoveVec.z += v.z;
	if(glm::length(mMoveVec) > mSpeed + 0.05f) {
		v = glm::normalize(mMoveVec) * 0.08f;
		mMoveVec.x -= v.x;
		mMoveVec.z -= v.z;
	}
	else if(glm::length(mMoveVec) > mSpeed){
		v = glm::normalize(mMoveVec) * mSpeed;
		mMoveVec.x = v.x;
		mMoveVec.z = v.z;
	}

	// キャラクターの向きを変える
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(vec))) * 180 / glm::pi<float>();
	if(vec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() / 180);
}


// -----------------------------------------------------------------
/// 画面がクリックされたときの処理
// -----------------------------------------------------------------
void Player::Click(){
	if(!mLand || (mState != STATE::NEUTRAL && mState != STATE::ATACK)) return;

	ChangeState(STATE::SIT);
	
	// 次の動作の準備
	mKeepVec = mMoveVec;
	mKeepTime = 0;
	mAimCenter = mPos;
	mScale.y = 0.7f;
	mScale.z = 1.0f;
	mRotate.x = 0;

}


// -----------------------------------------------------------------
/// プレイヤーのジャンプ
// -----------------------------------------------------------------
void Player::Jump(){
	if(mLand && mState == STATE::SIT){
		mJumpSE.PlaySE();

		mLand = false;
		mScale = glm::vec3(1.0f, 1.0f, 1.0f);
		mRotate.x = 20;
		mVisible = true;

		// 短いクリックの時は移動を考慮
		if(mKeepTime < 15) {
			mMoveVec = mKeepVec;
			mKeepVec = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		// スピードが速すぎるときは少し速度を落とす。通常ジャンプ時は少し飛距離を上げる
		if(glm::length(mMoveVec) > 0.3f)mMoveVec *= 0.7f;
		else mMoveVec *= 1.3f;
		mMoveVec.y = 0.25f;

		ChangeState(STATE::JUMP);
	}
}

// -----------------------------------------------------------------
/// 着地
// -----------------------------------------------------------------
void Player::Land(){
	if(!mLand) {
		ChangeState(STATE::NEUTRAL);
		mLand = true;
		mRotate.x = 0;
		mMoveVec.y = 0;

		// 点滅させる
		if(!mIsCol) mFlash = true;
	}
}

// -----------------------------------------------------------------
/// 攻撃の狙い定め
/// プレイヤーを引っ張り狙いを定めます
/// [in] pullVec マウスのクリック地点からの引っ張り距離
// -----------------------------------------------------------------
void Player::Aim(const glm::vec2 & pullVec){
	if(mState != STATE::AIM && mState != STATE::SIT) return;

	// 引っ張りが弱い場合はしゃがみ状態に戻す
	if(glm::length(pullVec) <= 10){
		ChangeState(STATE::SIT);
		mScale.z = 1;
		return;
	}

	ChangeState(STATE::AIM);

	// キャラクターの向きを変える
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(pullVec))) * 180.0f / glm::pi<float>();
	if(pullVec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() / 180.0f);

	// キャラクターを引き伸ばす
	mScale.z = 1 + glm::length(pullVec) * 0.02f; // 0.02fは補正地
	// 3以上の長さには引っ張れない
	if(mScale.z > 3) mScale.z = 3;

	// 引き伸ばし中心点をずらす
	mPos = mAimCenter + glm::normalize(glm::vec3(-pullVec.x, 0.0f, -pullVec.y)) * model.getSize().z / 2.0f;
}


// ------------------------------------------------------------------
/// 攻撃
/// 引っ張り力に応じて引っ張った向きへ飛んでいきます
// ------------------------------------------------------------------
void Player::Atack(glm::vec2 pullVec){
	if(mState != STATE::AIM)return;

	ChangeState(STATE::ATACK);
	mAtackSE.PlaySE();

	// キャラクターの向き設定
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(pullVec))) * 180.0f / glm::pi<float>();
	if(pullVec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() /180.0f);

	// 発射
	if(glm::length(pullVec) >= 112) pullVec = glm::normalize(pullVec) * 112.0f;
	mMoveVec = (glm::vec3(-pullVec.x, 0.0f, -pullVec.y)*0.015f);
	mScale.z = 1;
	mRotate.x = -10;
}

// ------------------------------------------------------------
/// ダメージ処理
/// [in] vec 吹っ飛ぶ方向
void Player::Damage(const glm::vec3 &vec){
	mLand = false;
	mPos += glm::vec3(0.0f, 0.1f, 0.0f); // ちょっと浮かせる
	mRotate.x = 20;
	model.setRotate(mRotate);
	setScale(1.0f);
	mMoveVec.x = vec.x*0.2f;
	mMoveVec.z = vec.z*0.2f;
	mMoveVec.y = 0.2f;
	mVisible = true;
	mFlashCount = 0;
	mHitPoint--;

	InvaildCol(3); // 無敵化
}