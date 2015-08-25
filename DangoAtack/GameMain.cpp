#include "GameMain.h"
#include<map>

GameMain::GameMain(GLFWwindow *window):Scene(window)
{
	mScene = SCENE::GAMEMAIN_SCENE;

	// �}�E�X�z�C�[�����쎞�̃R�[���o�b�N�Ƃ���wheel�֐���o�^
	glfwSetScrollCallback(window, Wheel); 
	Init();
}


GameMain::~GameMain(void)
{
}


// ---------------------------------------------------------------------
/// ���\�[�X�̃��[�h
/// [in] self ���N���X�̃|�C���^
// ---------------------------------------------------------------------
void Load(GameMain* self){

}

float GameMain::mWheelCount = 1; // �z�C�[���̉�]��

// ----------------------------------------------------------------------
/// ����������
// ----------------------------------------------------------------------
void GameMain::Init(){
	Scene::Init();
	mPauseTex.Load("texture/pause.dds");
	mGameOverTex.Load("texture/gameover.dds");
	mGameOverTex.setAlpha(0.0f);
	mGameClearTex.Load("texture/clear.dds");
	mGameClearTex.setAlpha(0.0f);
	mLoadComp = true;

	BGM.PlayBGM("sound/bgm2.wav", true);

	FadeIn(0.1f);

	mPause = false;
	mWheelCount = 1;
	mStage.Init();
	mPlayer.Init(&mMouse);
	mEnemys.Init(&mPlayer);

	mCollisionManager.setBossFlag(false);
	mStage.setBossFlag(false);

	camPos = mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f);
	lookAt = mPlayer.getPos() + mPlayer.getFront()*2.0f;

}


// -----------------------------------------------------------------------
/// �}�E�X�z�C�[������̎擾
/// �}�E�X�z�C�[���̑��쎞�R�[���o�b�N�Ƃ��ČĂ΂�܂�
/// [in] *window �ΏۃE�B���h�E�̃n���h��
/// [in] x �}�E�X�z�C�[���̉�����]
/// [in] y �}�E�X�z�C�[���̏c����]
// -----------------------------------------------------------------------
void GameMain::Wheel(GLFWwindow *window, double x,	double y){
	mWheelCount -= y;
	if(mWheelCount < 1) mWheelCount = 1;
	if(mWheelCount > 4) mWheelCount = 4;
};


// -----------------------------------------------------------------------
/// �X�V����
// -----------------------------------------------------------------------
Scene::SCENE GameMain::Update(){
	Scene::Update();
	// �|�[�Y
	if(mMouse.IsClickMiddleButton()){
		mPause = !mPause;
	}
	if(mPause) return mScene;

	// �X�e�[�W�̃A�b�v�f�[�g
	mStage.Update();

	// �v���C���[�̃A�b�v�f�[�g
	mPlayer.Update();

	// �G�̃A�b�v�f�[�g
	mEnemys.Update();
	
	// �����蔻��
	if(!mEnemys.getActiveList()->empty())mCollisionManager.PlayerVSEnemy(mPlayer, mEnemys);   // �v���C���[�ƓG
	if(!mEnemys.getActiveList()->empty())mCollisionManager.EnemyVSEnemy(mEnemys);			    // �G���m
	mCollisionManager.PlayerVSStage(mPlayer, mStage);									    // �v���C���[�ƃX�e�[�W
	if(!mEnemys.getActiveList()->empty())mCollisionManager.EnemysVSStage(mEnemys, mStage);    // �G�ƃX�e�[�W
	mCollisionManager.PlayerVSShot(mPlayer, mEnemys.getShotManager());					    // �e�ƃv���C���[

	// �{�X��˓�
	if(mPlayer.getPos().z >= 760) {
		mCollisionManager.setBossFlag(true);
		mStage.setBossFlag(true);
		mPlayer.setBossFlag(true);
	}

	// �J�������[�N
	// �J�����ʒu
	if(mPlayer.getState() != Player::STATE::ATACK) camPos += (mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f)*mWheelCount - camPos) / 3.0f;
	else camPos += (mPlayer.getPos() + glm::vec3(0.0f, 5.0f, -10.0f)*mWheelCount - camPos) / 10.0f;
	

	// �����_
	if(mPlayer.getState() != Player::STATE::ATACK && mPlayer.getState() != Player::STATE::AIM)lookAt += ((mPlayer.getPos() + mPlayer.getFront()*2.5f) - lookAt) / 5.0f;
	else if(mPlayer.getState() == Player::STATE::AIM) lookAt += ((mPlayer.getPos() + mPlayer.getFront()*5.0f) - lookAt) / 5.0f;
	else lookAt = mPlayer.getPos();

	mStage.setSkyPos(mPlayer.getPos());

	// BGM�̃\�[�X�̐ݒ�
	BGM.setPos(listnerPos[0], listnerPos[1], listnerPos[2]);

	// �^�C�g����
	if((mEnemys.getGameClear() || mPlayer.getGameOver()) && mMouse.IsClickLeftButton() && !mFadeOutStart) FadeOut(2.0f);
	if(mFadeOutComp) ChangeScene(SCENE::TITLE_SCENE);

	if(!mEnemys.getGameClear() && mPlayer.getGameOver() &&  mGameOverTex.getAlpha() < 1.0f) mGameOverTex.setAlpha(mGameOverTex.getAlpha() + 0.01f);
	if(mEnemys.getGameClear() && mGameClearTex.getAlpha() < 1.0f) mGameClearTex.setAlpha(mGameClearTex.getAlpha() + 0.05f);

	return mScene;
}


// ----------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------
void GameMain::Draw(){
	mStage.Draw();
	mPlayer.Draw();
	mEnemys.Draw();

	if(mPause)mPauseTex.Draw();
	if(mPlayer.getGameOver())mGameOverTex.Draw();
	if(mEnemys.getGameClear())mGameClearTex.Draw();

	Scene::Draw();
}

