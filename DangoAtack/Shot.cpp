#include "Shot.h"


Shot::Shot(void) : mLifeTime(5.0f * FPS)
{
}


Shot::~Shot(void)
{
}


// -------------------------------------------------------------
/// �e�̏�����
/// [in] SM ���g���Ǘ����Ă���}�l�[�W���[�̃A�h���X
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
/// �e�̍X�V
// ---------------------------------------------------------------
void Shot::Update(){
	if(!mIs) return;

	// ��莞�Ԃŏ���
	mLifeCount++;
	if(mLifeCount >= mLifeTime){
		Fin();
		return;
	}

	// �^�[�Q�b�g��ǐՂ���
	glm::vec3 vec = glm::normalize(mTarget->getPos() - mPos) * mSpeed;
	mMoveVec.x = vec.x;
	mMoveVec.z = vec.z;

	// �ړ�
	mPos += mMoveVec;

	// ���f���ɍ��W����K�p
	mBillboad.setPos(mPos);
	mBillboad.setScale(mScale);

	mDistance = glm::length(camPos - mPos);
}

// --------------------------------------------------------------
/// �e�̕`��
// --------------------------------------------------------------
void Shot::Draw(){
	mBillboad.DrawBill();
}


// ---------------------------------------------------------------
/// �e�̔���
/// [in] pos ���ˈʒu
/// [in] target �ڕW�Ƃ���I�u�W�F�N�g�̃n���h��
// ---------------------------------------------------------------
void Shot::Trigger(const glm::vec3 &pos, GameObject* target){
	mIs = true;
	mVisible = true;
	mPos = pos + glm::vec3(0.0f, mBillboad.getSize().y/2, 0.0f);
	mTarget = target;
	mLifeCount = 0;
}


// -------------------------------------------------------------------
/// �V���b�g�}�l�[�W���[�̃A�N�e�B�u���X�g�ɒǉ�����
// -------------------------------------------------------------------
void Shot::pushActiveList(){
	mShotManager->pushActiveObject(this);
}

// ------------------------------------------------------------------
/// �V���b�g�}�l�[�W���[�̃A�N�e�B�u���X�g���玩�g�����O����
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
/// �e�̏���
// ----------------------------------------------------------------------
void Shot::Fin(){
	mIs = false;
	mVisible = false;

	// �}�l�[�W���[�̃A�N�e�B�u���X�g���玩�g���O��
	eraseMySelf();	
}
