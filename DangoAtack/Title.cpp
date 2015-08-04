#include "Title.h"

// ------------------------------------------------------
// �R���X�g���N�^
// [in] window �g�p����E�B���h�E�̃n���h��
// ------------------------------------------------------
Title::Title(GLFWwindow *window):Scene(window),
	mFadeSpeed(0.02f),
	mFadeFlag(false),
	mStart(false)
{
	mScene = SCENE::TITLE_SCENE;
	Init();
}


Title::~Title(void)
{
}


// ----------------------------------------------------------------------------
/// �ʃX���b�h�ł̃��[�h����
/// [in] self ���N���X�̃|�C���^
/// ---------------------------------------------------------------------------
void Title::Load(Title* self){
	

	/*self->mBGM.PlayBGM("sound/bgm.wav");
	self->mStartSE.LoadSE("sound/start.wav");

	while(true){
		if(self->mBGM.LoadComp()) break;
	}*/

	self->mLoadComp = true;
}


// ----------------------------------------------------------------------------
/// ����������
/// [in] window �g�p����E�B���h�E�̃n���h��
// ----------------------------------------------------------------------------
void Title::Init(){
	Scene::Init();
	FadeIn(0.5f);

	mBackTex.Load("texture/title.dds");
	mStartTex.Load("texture/start.dds");

	mBGM.PlayBGM("sound/bgm.wav",true);
	mStartSE.LoadSE("sound/start.wav");

	std::thread th(Load, this);
	th.detach();
}


// ---------------------------------------------------------------------------
/// �X�V
// ---------------------------------------------------------------------------
Scene::SCENE Title::Update(){
	Scene::Update();

	// �X�^�[�g�\���̓_��
	if(mFadeFlag){
		mStartTex.setAlpha(mStartTex.getAlpha() - mFadeSpeed);
		if(mStartTex.getAlpha() <= 0.0f) mFadeFlag = false;
	}
	else{
		mStartTex.setAlpha(mStartTex.getAlpha() + mFadeSpeed);
		if(mStartTex.getAlpha() >= 1.0f) mFadeFlag = true;
	}

	// �X�^�[�g
	if(!mStart && mMouse.IsClickLeftButton()) {
		mStartSE.PlaySE();
		mStart = true;
		mStartTex.setAlpha(1.0f);
		mFadeSpeed = 0.1f;
		FadeOut(2.0f);
	}

	// �Q�[�����C����
	if(mFadeOutComp){
		ChangeScene(SCENE::GAMEMAIN_SCENE);
	}
	
	return mScene;
}


// ---------------------------------------------------------------------------
/// �`��
// ---------------------------------------------------------------------------
void Title::Draw(){
	mBackTex.Draw();
	mStartTex.Draw(WIN_W/2 - mStartTex.getWidth()/2, WIN_H - 170);

	Scene::Draw();
}