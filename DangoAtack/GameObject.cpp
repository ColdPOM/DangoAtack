#include "GameObject.h"


GameObject::GameObject(void)
{
}


GameObject::~GameObject(void)
{
}

// --------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�̏�����
// --------------------------------------------------------
void GameObject::Init(){
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);
	mRotate = glm::vec3(0.0f, 0.0f, 0.0f);

	mIs = false;
	mFront = glm::vec3(0.0f, 0.0f, -1.0f);
	mVisible = false;
	mLand = false;

	mStopCount = -1;
	mInvaildCount = -1;

	mStopFlag = false;
	mIsCol = true;
}


// -------------------------------------------------------------------
/// �Q�[���I�u�W�F�N�g�̍X�V
/// �����̂���I�u�W�F�N�g�͌p�����Update�֐��̐擪�ł��̊֐����Ă�
// -------------------------------------------------------------------
void GameObject::Update(){
	if(!mIs) return;

	// �q�b�g�X�g�b�v���ԃJ�E���g
	if(mStopCount >= 0) mStopCount--;
	else mStopFlag = false;

	// ���G���ԃJ�E���g
	if(mInvaildCount >= 0) mInvaildCount--;
	else {
		mIsCol = true;
		mVisible = true;
	}
}


// --------------------------------------------------------------------
/// ���f���̕`��
// --------------------------------------------------------------------
void GameObject::Draw(){
	if(!mVisible || !mIs) return;

	// ���f���ɍ��W����K�p
	model.setPos(mPos);
	model.setScale(mScale);
	model.setRotate(mRotate);

	model.Draw();
}

