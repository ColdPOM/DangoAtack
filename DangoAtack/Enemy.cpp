#include "Enemy.h"
#include "DebugGL.h"


Enemy::Enemy(void)
{
}


Enemy::~Enemy(void)
{
}


// -------------------------------------------------------------
/// �G���̏�����
/// �G�𐶐�����ꍇ�͕K��1�x�Ăяo���K�v������܂�
/// [in] EM ���g���Ǘ�����}�l�[�W���[
/// [in] player �v���C���[�̎Q�Ɨp�|�C���^
/// [in] type �G�̎��
// -------------------------------------------------------------
void Enemy::Init(EnemyManager* EM, Player* player, int type){
	GameObject::Init();
	mType = type;

	// �^�C�v���Ƃ̐ݒ�
	switch (mType)
	{
	// �G��
	case TYPE::ZAKO : 
		if(!model.IsLoad()) model.Load("ene01.pmd", "model/enemy");
		mHitPoint = 2;
		mSpeed = 0.065f;
		mMotionSpeed = 0.005f;
		break;

	// �΂��ӂ��G
	case TYPE::FIRE:
		if(!model.IsLoad()) model.Load("ene02.pmd", "model/enemy");
		mHitPoint = 3;
		mSpeed = 0.05f;
		break;

	// ����ۂ��G
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
		std::cout << "�g�p�ł��Ȃ��G�̃^�C�v���w�肵�Ă��܂�" << std::endl;
		break;
	}

	// ���ʂ̐ݒ�
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
/// �G��z�u
/// �����������������ɍs��
/// [in] EM ���g���Ǘ�����}�l�[�W���[
/// [in] player �v���C���[�̎Q�Ɨp�|�C���^
/// [in] type �G�̎��
/// [in] x,y,z �z�u������W
// -----------------------------------------------------------------
void Enemy::setEnemy(EnemyManager *EM, Player *player, int type, float x, float y, float z){
	Init(EM, player, type);
	mPos = glm::vec3(x, y, z);
}



// --------------------------------------------------------------
/// �G�̍X�V
/// �G�̏����X�V
// --------------------------------------------------------------
void Enemy::Update(){
	if(!mIs) return;
	GameObject::Update();
	if(mStopFlag) return;

	// �d��
	if(!mLand) mMoveVec.y -= gravity;

	// �n�ʖ��C
	if(mLand){
		if(glm::length(mMoveVec) > 0.1f) mMoveVec -= glm::normalize(mMoveVec) * 0.05f;
		if(glm::length(mMoveVec) <= 0.1f) mMoveVec *= 0;
	}


	// �G�̎�ނ��Ƃ̏���
	switch (mType){
	// ----------------------------------------�G��-----------------------------------------------------
	case TYPE::ZAKO:
		// �U��
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x*1.5f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(mAtackCount >= 60){ // �j���[�g������Ԃɖ߂�
				ChangeState(STATE::NEUTRAL);
				mScaleMeter = 1.0f;
				mAtackCount = 0;
			}
			else if(mAtackComp && mScaleMeter > 1.0f){ // �U�����I���k��
				mScaleMeter -= 0.1f;
			}
			else if(!mAtackComp && mAtackCount >= 30 && mScaleMeter < 2.5f){ // �c���
				mScaleMeter += 0.5f;
				if(mScaleMeter >= 2.5f) mAtackComp = true; // �U������
			}
			else if (!mAtackComp)mScaleMeter -= 0.012f; // �\������

			setScale(mScaleMeter);
		}

		// �v���C���[�̒ǐ�
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// �A�j���[�V����
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



		// ----------------------------------------�΂��ӂ��G--------------------------------------------------
	case TYPE::FIRE:
		// �U��
		if(mState == STATE::NEUTRAL && !mShot->getIs() && glm::length(mPlayer->getPos() - mPos) < 15 && glfwGetTime() - mAtackTime >= 7.0f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
			mAtackTime = glfwGetTime();
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(!mAtackComp && mAtackCount >= 30 && mScaleMeter > 1.0f){ // �΂𐁂�
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
			else if (!mAtackComp)mScaleMeter += 0.012f; // �\������

			setScale(mScaleMeter);
			Turn(mPlayer->getPos(), 10); // �v���C���[�̕�������
		}

		// �v���C���[�̒ǐ�
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// �A�j���[�V����
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



		// ----------------------------------------�΂̓G----------------------------------------------------
	case TYPE::STONE:
		// �U��
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x*2){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mWalkCount = 0;
			mTargetPos = mPlayer->getPos() + glm::vec3(0.0f, 10.0f, 0.0f);
			mCameTargetPoint = false;
		}
		if(mState == STATE::ATACK) {
			// �ڕW�n�_�ւ̃x�N�g��
			glm::vec3 vec = mTargetPos - mPos;
			if(!mCameTargetPoint && glm::length(vec) > 0.1f){ // �ڕW�̏��Ɍ�����
				mMoveVec.y += gravity; // �d�͂���������
				mPos += glm::normalize(vec)*0.5f;
				Turn(mTargetPos, 5);

				if(glm::length(vec) <= 1.0f){ // �ڕW�n�_�ɓ���
					mCameTargetPoint = true;
					mMoveVec += glm::vec3(0.0f, -1.0f, 0.0f);
					mBarrier = true;
				}
			}
			else if(mLand){ // ���n
				mAtackCount++;
				mBarrier = false;
				if(mAtackCount >= 120){ // �j���[�g������Ԃɖ߂�
					ChangeState(STATE::NEUTRAL);
					mAtackCount = 0;
				}
			}
		}

		// �v���C���[�̒ǐ� (���肸��ƈ�������悤�ɐi��)
		else if(mState == STATE::NEUTRAL){
			mWalkCount++;
			if(mWalkCount < 30)	Chase();
			else if(mWalkCount >= 60) mWalkCount = 0;
		}

		break;

		// ----------------------------------------�{�X----------------------------------------------------
		case TYPE::BOSS:
		// �U��
		if(mState == STATE::NEUTRAL && glm::length(mPlayer->getPos() - mPos) < getSize().x * 0.9f){
			ChangeState(STATE::ATACK);
			mAtackCount = 0;
			mAtackComp = false;
			mScaleMeter = 1.0f;
		}
		if(mState == STATE::ATACK) {
			mAtackCount++;
			
			if(mAtackCount >= 40){ // �j���[�g������Ԃɖ߂�
				ChangeState(STATE::NEUTRAL);
				mScaleMeter = 1.0f;
				mAtackCount = 0;
			}
			else if(mAtackComp && mScaleMeter > 1.0f){ // �U�����I���k��
				mScaleMeter -= 0.1f;
			}
			else if(!mAtackComp && mAtackCount >= 15 && mScaleMeter < 2.5f){ // �c���
				mScaleMeter += 0.5f;
				if(mScaleMeter >= 2.5f) mAtackComp = true; // �U������
			}
			else if (!mAtackComp)mScaleMeter -= 0.012f; // �\������

			setScale(mScaleMeter);
		}

		// �v���C���[�̒ǐ�
		else if(mState == STATE::NEUTRAL){
			Chase();
			mMotionSpeed = 0.012f;
		}

		// �A�j���[�V����
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






	// �ړ�
	mPos += mMoveVec;

	// HP�[��
	if(mHitPoint <= 0) mDeathCount++;

	// HP�[���ɂȂ��Ă����莞�Ԃŏ���
	if(mDeathCount >= FPS * 3){
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// ������
	if(mPos.y <= -50) {
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// �v���C���[�Ƌ��������ꂷ����Ə���
	if(mIs && mPlayer->getPos().z - mPos.z  >= 200){
		mIs = false;
		mHitPoint = 0;
		eraseMySelf();
	}

	// ���f���ɍ��W����K�p
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

}

// ----------------------------------------------------------------
/// ���n
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
/// �v���C���[�̒ǐ�
// --------------------------------------------------------------
void Enemy::Chase(){
	glm::vec3 vec = mPlayer->getPos() - mPos;

	// �L�����N�^�[�̈ړ�
	glm::vec3 v = glm::normalize(glm::vec3(vec.x, 0, vec.z)) * mSpeed;
	mMoveVec.x = v.x;
	mMoveVec.z = v.z;

	Turn(mPlayer->getPos(), 10);
}


// --------------------------------------------------------------
/// �_���[�W����
/// �v���C���[�̃A�^�b�N���󂯂����Ɏg�p���܂�
/// [in] AtackVec �v���C���[�̃A�^�b�N���̈ړ��x�N�g��
// --------------------------------------------------------------
void Enemy::Damage(){
	ChangeState(STATE::DAMAGE);
	mLand = false;
	mPos += glm::vec3(0.0f, 0.1f, 0.0f); // ������ƕ�������
	mRotate.x = 20;
	model.setRotate(mRotate);
	setScale(1.0f);
	if(glm::length(mPlayer->getMoveVec()) >= 0.6f)mHitPoint--;

	float vecLengthY = glm::length(mPlayer->getMoveVec()); // �c�����̐�����ѓx����
	float vecLengthXZ = 0.2f; // �������̐�����ѓx����
	if(mHitPoint <= 0) {
		vecLengthY = 5.0f;
		vecLengthXZ = 3.0f;
	}

	mMoveVec = mPlayer->getMoveVec()*vecLengthXZ + glm::vec3(0.0f, 0.1f*vecLengthY*3, 0.0f); // ������ѓx����
	InvaildCol(1.0f); // ���G��
}


// ----------------------------------------------------------------------------
/// �w�肳�ꂽ��������(Y����]�̂݁j
/// [in] delta �U������ɂ�����Ԋu�B�傫���قǂ������U�����
// ----------------------------------------------------------------------------
void Enemy::Turn(glm::vec3 target, float delta){
	glm::vec3 vec = target - mPos;

	float r;
	// �G�̐��ʃx�N�g���ƃv���C���[�����x�N�g���Ԃ̊p�x
	float dot = glm::dot(glm::vec2(mFront.x, mFront.z), glm::normalize(glm::vec2(vec.x, vec.z)));
	if(glm::abs(dot - 1) > 0.0001f){
		r = glm::acos(dot) * 180.0f / glm::pi<float>();
		// �p�x��G���ʂ��甼���v���肪�v���X�A���v��肪�}�C�i�X�̊p�x�ɂ���
		glm::vec3 a = glm::rotateY(mFront, glm::pi<float>()/2.0f);
		glm::vec2 b = glm::vec2(a.x, a.z);
		if(glm::dot(b, glm::normalize(glm::vec2(vec.x, vec.z))) < 0) r = -r;
	}
	else r = 0;

	// ��]������
	mRotate.y += r/delta;
	mFront = glm::rotateY(mFront, r/delta * glm::pi<float>() / 180.0f);
}


// ------------------------------------------------------------------
/// �G�l�~�[�}�l�[�W���[�̃A�N�e�B�u���X�g���玩�g�����O����
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
/// �G���A�N�e�B�u�ɂ���
// -------------------------------------------------------------------
void Enemy::Active(){
	mIs = true;
	mEnemyManager->pushActiveObject(this);
}