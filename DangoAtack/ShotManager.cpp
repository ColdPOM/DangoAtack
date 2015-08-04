#include "ShotManager.h"


ShotManager::ShotManager(void)
{
}


ShotManager::~ShotManager(void)
{
	delete[] mShots;
}

// ----------------------------------------------------------
/// ������
/// [in] nom ����������e�̐�
// ----------------------------------------------------------
void ShotManager::Init(const int nom){
	mShotCount = nom;
	mShots = new Shot[mShotCount]();

	for(int i = 0; i < mShotCount; i++){
		mShots[i].Init(this);
	}
}


// -----------------------------------------------------------
/// �X�V
// -----------------------------------------------------------
void ShotManager::Update(){
	for(int i = 0; i < mShotCount; i++){
		mShots[i].Update();
	}
}


// -----------------------------------------------------------
/// �`��
// -----------------------------------------------------------
void ShotManager::Draw(){
	// �`�揇�ɕ��בւ��i��̓J�����Ƃ̋����j
	std::sort(mActiveList.begin(), mActiveList.end(), 
		[](Shot*& left, Shot*& right) { return left->getDistance() > right->getDistance();});


	// �A�N�e�B�u�ɂȂ��Ă�����̂����`��
	for(int i = 0; i < mActiveList.size(); i++){
		mActiveList[i]->Draw();
	}
}
