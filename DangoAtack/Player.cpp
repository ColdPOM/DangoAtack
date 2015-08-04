#include "Player.h"


Player::Player(void)
{
}

Player::~Player(void)
{
}


// -------------------------------------------------------------
/// �v���C���[���̏�����
/// �v���C���[�𐶐�����ꍇ�͕K��1�x�Ăяo���K�v������܂�
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
/// �v���C���[�̍X�V
/// �v���C���[���̍X�V���s���܂�
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
			GameOver = true; // �Q�[���I�[�o�[
		}

		return;
	}

	// ---����---
	// �ړ�
	if(mMouse->IsDownRightButton())Move(mMouse->getMousePos());
	// ���쏀��
	if (mMouse->IsClickLeftButton()) Click();
	// �W�����v
	if (mMouse->IsReleaseLeftButton()) Jump();
	// �U��
	if (mMouse->IsDownLeftButton()) Aim(mMouse->getPullVec());
	if (mMouse->IsReleaseLeftButton()) Atack(mMouse->getPullVec());



	// �d��
	if(!mLand) mMoveVec.y -= gravity;

	if(mLand){
		mLandCount++;
		// �����|�C���g�̍X�V
		if(mLandCount >= 60){
			mRestartPos = mPos;
			mLandCount = 0;
		}

		// �n�ʖ��C
		if(!(mMouse->IsDownRightButton() && mState == STATE::NEUTRAL)){
			if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
			if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		}
	}


	// �e��Ԃ��Ƃ̏���
	switch (mState)
	{
	// �ʏ펞
	case STATE::NEUTRAL:
		// �v���C���[�̃A�j���[�V����
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

	// ���Ⴊ�ݎ�
	case STATE::SIT:
		if(!mLand)break;
		mKeepTime++;
		// �u���[�L
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		break;

	// �W�����v��
	case STATE::JUMP:

		break;

	// �_��
	case STATE::AIM:
		// �u���[�L
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f; 
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
		break;

	// �U����
	case STATE::ATACK:
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.03f;
		if(glm::length(mMoveVec) <= 0.1f){
			ChangeState(STATE::NEUTRAL);
			mRotate.x = 0;
		}
		break;

	default:
		printf("�v���C���[��mState�Ɏg�p�ł��Ȃ��l���w�肵�Ă��܂�\n");
		break;
	}
	
	
	// �ړ�
	mPos += mMoveVec;


	// ������
	if(mPos.y <= -50) {
		mPos = mRestartPos;
		if(BossBattle) mPos = glm::vec3(10.0f, 0.1f, 800.0f);
		mMoveVec *= 0;
		mVisible = true;
		mFlash = 0;
		mFlashCount = 0;
		mHitPoint--;
		InvaildCol(3); // ���G��
	}


	// �_��
	if(mFlash){
		mFlashCount++;
		if(mFlashCount >= 5){
			mVisible = !mVisible;
			mFlashCount = 0;
		}
	}
	if(mIsCol) mFlash = false;


	// ���f���ɍ��W����K�p
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

}

// ----------------------------------------------------------------
/// �v���C���[�̕`��
// ----------------------------------------------------------------
void Player::Draw(){
	GameObject::Draw();

	// HP�̕\��
	if(mHitPoint <= 0) return;
	for(int i = 0; i < mHitPoint; i++){
		mHeartTex.Draw(10 + (mHeartTex.getWidth() + 5)*i, 10);
	}

}


// ----------------------------------------------------------------
/// �v���C���[�̈ړ�
/// �L�[���͂ɉ����ăv���C���[���ړ������܂�
/// �v���C���[��Update()�Ăяo���̑O�Ɉ�x�����Ăяo���Ă�������
/// [in] right, left, front, back�@���ꂼ��̃L�[���͔���l
// ----------------------------------------------------------------
void Player::Move(const glm::vec2 &mousePos){
	
	// �ʏ펞�ӊO�܂��͋󒆂ł͈ړ��ł��Ȃ�
	if(mState != STATE::NEUTRAL || !mLand) return;

	glm::vec2 vec = mousePos - glm::vec2(WIN_W/2, WIN_H/2);

	// �L�����N�^�[�̈ړ�
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

	// �L�����N�^�[�̌�����ς���
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(vec))) * 180 / glm::pi<float>();
	if(vec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() / 180);
}


// -----------------------------------------------------------------
/// ��ʂ��N���b�N���ꂽ�Ƃ��̏���
// -----------------------------------------------------------------
void Player::Click(){
	if(!mLand || (mState != STATE::NEUTRAL && mState != STATE::ATACK)) return;

	ChangeState(STATE::SIT);
	
	// ���̓���̏���
	mKeepVec = mMoveVec;
	mKeepTime = 0;
	mAimCenter = mPos;
	mScale.y = 0.7f;
	mScale.z = 1.0f;
	mRotate.x = 0;

}


// -----------------------------------------------------------------
/// �v���C���[�̃W�����v
// -----------------------------------------------------------------
void Player::Jump(){
	if(mLand && mState == STATE::SIT){
		mJumpSE.PlaySE();

		mLand = false;
		mScale = glm::vec3(1.0f, 1.0f, 1.0f);
		mRotate.x = 20;
		mVisible = true;

		// �Z���N���b�N�̎��͈ړ����l��
		if(mKeepTime < 15) {
			mMoveVec = mKeepVec;
			mKeepVec = glm::vec3(0.0f, 0.0f, 0.0f);
		}

		// �X�s�[�h����������Ƃ��͏������x�𗎂Ƃ��B�ʏ�W�����v���͏����򋗗����グ��
		if(glm::length(mMoveVec) > 0.3f)mMoveVec *= 0.7f;
		else mMoveVec *= 1.3f;
		mMoveVec.y = 0.25f;

		ChangeState(STATE::JUMP);
	}
}

// -----------------------------------------------------------------
/// ���n
// -----------------------------------------------------------------
void Player::Land(){
	if(!mLand) {
		ChangeState(STATE::NEUTRAL);
		mLand = true;
		mRotate.x = 0;
		mMoveVec.y = 0;

		// �_�ł�����
		if(!mIsCol) mFlash = true;
	}
}

// -----------------------------------------------------------------
/// �U���̑_�����
/// �v���C���[����������_�����߂܂�
/// [in] pullVec �}�E�X�̃N���b�N�n�_����̈������苗��
// -----------------------------------------------------------------
void Player::Aim(const glm::vec2 & pullVec){
	if(mState != STATE::AIM && mState != STATE::SIT) return;

	// �������肪�ア�ꍇ�͂��Ⴊ�ݏ�Ԃɖ߂�
	if(glm::length(pullVec) <= 10){
		ChangeState(STATE::SIT);
		mScale.z = 1;
		return;
	}

	ChangeState(STATE::AIM);

	// �L�����N�^�[�̌�����ς���
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(pullVec))) * 180.0f / glm::pi<float>();
	if(pullVec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() / 180.0f);

	// �L�����N�^�[�������L�΂�
	mScale.z = 1 + glm::length(pullVec) * 0.02f; // 0.02f�͕␳�n
	// 3�ȏ�̒����ɂ͈�������Ȃ�
	if(mScale.z > 3) mScale.z = 3;

	// �����L�΂����S�_�����炷
	mPos = mAimCenter + glm::normalize(glm::vec3(-pullVec.x, 0.0f, -pullVec.y)) * model.getSize().z / 2.0f;
}


// ------------------------------------------------------------------
/// �U��
/// ��������͂ɉ����Ĉ��������������֔��ł����܂�
// ------------------------------------------------------------------
void Player::Atack(glm::vec2 pullVec){
	if(mState != STATE::AIM)return;

	ChangeState(STATE::ATACK);
	mAtackSE.PlaySE();

	// �L�����N�^�[�̌����ݒ�
	float r;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(pullVec))) * 180.0f / glm::pi<float>();
	if(pullVec.x < 0) r = -r;
	mRotate.y = r;
	mFront = glm::rotateY(glm::vec3(0.0f, 0.0f, -1.0f), r * glm::pi<float>() /180.0f);

	// ����
	if(glm::length(pullVec) >= 112) pullVec = glm::normalize(pullVec) * 112.0f;
	mMoveVec = (glm::vec3(-pullVec.x, 0.0f, -pullVec.y)*0.015f);
	mScale.z = 1;
	mRotate.x = -10;
}

// ------------------------------------------------------------
/// �_���[�W����
/// [in] vec ������ԕ���
void Player::Damage(const glm::vec3 &vec){
	mLand = false;
	mPos += glm::vec3(0.0f, 0.1f, 0.0f); // ������ƕ�������
	mRotate.x = 20;
	model.setRotate(mRotate);
	setScale(1.0f);
	mMoveVec.x = vec.x*0.2f;
	mMoveVec.z = vec.z*0.2f;
	mMoveVec.y = 0.2f;
	mVisible = true;
	mFlashCount = 0;
	mHitPoint--;

	InvaildCol(3); // ���G��
}