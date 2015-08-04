#include "Scene.h"

// ------------------------------------------------------
/// �R���X�g���N�^
/// [in] window �g�p����E�B���h�E�̃n���h��
// ------------------------------------------------------
Scene::Scene(GLFWwindow *window):
	mLoadComp(false),
	mFadeTime(0.0f),
	mFadeInStart(false),
	mFadeInComp(false),
	mFadeOutStart(false),
	mFadeOutComp(false)
{
	mMouse.Init(window);
	listnerPos[0] = 0.0f;
	listnerPos[1] = 0.0f;
	listnerPos[2] = 0.0f;
}

// ------------------------------------------------------
/// �f�X�g���N�^
// ------------------------------------------------------
Scene::~Scene(void)
{
}

// -----------------------------------------------------------------
/// ������
// -----------------------------------------------------------------
void Scene::Init(){
	mFadeTex.Load("texture/black.dds");
	mFadeTex.setPos(WIN_W/2.0f, WIN_H/2.0f);
	mFadeTex.setScale(WIN_W, WIN_H);
	mFadeTex.setAlpha(0.0f);
}

// -----------------------------------------------------------------
/// �X�V
// -----------------------------------------------------------------
Scene::SCENE Scene::Update(){
	mMouse.Update(); // �}�E�X��Ԃ̍X�V

	// �t�F�[�h�C������
	if(mFadeInStart && !mFadeInComp){
		mFadeTex.setAlpha(mFadeTex.getAlpha() - 1.0 / (mFadeTime*FPS));
		if(mFadeTex.getAlpha() <= 0.0){
			mFadeTex.setAlpha(0.0f);
			mFadeInComp = true;
		}
	}

	// �t�F�[�h�A�E�g����
	else if(mFadeOutStart && !mFadeOutComp){
		mFadeTex.setAlpha(mFadeTex.getAlpha() + 1.0 / (mFadeTime*FPS));
		if(mFadeTex.getAlpha() >= 1.0){
			mFadeTex.setAlpha(1.0f);
			mFadeOutComp = true;
		}
	}

	return mScene;
}

// -----------------------------------------------------------------
/// �`��
/// �p�����Draw�֐��̍Ō�ɕK�����s����K�v������
// -----------------------------------------------------------------
void Scene::Draw(){
	glDisable(GL_DEPTH_TEST);
	mFadeTex.Draw();
	glEnable(GL_DEPTH_TEST);
}


// -----------------------------------------------------------------
/// �t�F�[�h�C���J�n
// -----------------------------------------------------------------
void Scene::FadeIn(float fadeTime){
	mFadeTex.setAlpha(1.0f);
	mFadeTime = fadeTime;
	mFadeInComp = false;
	mFadeInStart = true;
	mFadeOutStart = false;

}


// -----------------------------------------------------------------
/// �t�F�[�h�A�E�g�J�n
// -----------------------------------------------------------------
void Scene::FadeOut(float fadeTime){
	mFadeTex.setAlpha(0.0f);
	mFadeTime = fadeTime;
	mFadeOutComp = false;
	mFadeOutStart = true;
	mFadeInStart = false;
}
