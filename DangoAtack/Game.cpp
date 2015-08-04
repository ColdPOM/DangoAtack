#include "Game.h"

// -----------------------------------------------------------------------
/// �R���X�g���N�^
/// [in] window �g�p����E�B���h�E�̃n���h��
// -----------------------------------------------------------------------
Game::Game(int width, int height, const char *title)
	: Window(width, height, title)
{
}

// -----------------------------------------------------------------------
/// �f�X�g���N�^
// -----------------------------------------------------------------------
Game::~Game(void)
{
	delete ActiveScene;
}




// ----------------------------------------------------------------------
/// ����������
// ----------------------------------------------------------------------
void Game::Init(){
	// �^�C�g���V�[������n�܂�
	scene = Scene::SCENE::TITLE_SCENE; 
	ActiveScene = new Title(window);

	loading.Init();
}

// -----------------------------------------------------------------------
/// �X�V����
// -----------------------------------------------------------------------
void Game::Update(){
	// ���[�h��
	if(!ActiveScene->LoadComp()){
		loading.Update();
		return;
	}

	// �V�[���؂�ւ��m�F
	if(ActiveScene->Update() == scene) return;
	else scene = ActiveScene->getScene();

	// �V�[���؂�ւ�
	switch (scene)
	{
	// �^�C�g����ʂ�
	case Scene::TITLE_SCENE:
		delete ActiveScene;
		ActiveScene = new Title(window);
	break;

	// �Q�[�����C����
	case Scene::GAMEMAIN_SCENE:
		delete ActiveScene;
		ActiveScene = new GameMain(window);
	break;

	default:
		std::cout << "�g�p�ł��Ȃ��V�[�����w�肵�Ă��܂�" << std::endl;
		break;
	}
}


// ----------------------------------------------------------------------
// �`�揈��
// ----------------------------------------------------------------------
void Game::Draw(){
	if(!ActiveScene->LoadComp()) {
		loading.Draw();
		return;
	}

	ActiveScene->Draw();
}
