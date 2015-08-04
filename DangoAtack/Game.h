#pragma once
#include "Window.h"
#include "Common.h"
#include "Scene.h"
#include "Title.h"
#include "GameMain.h"
#include "Loading.h"

// ---------------------------------------------------------------------------
/// �Q�[���E�B���h�E
/// �V�[���̊Ǘ��Ȃǂ��s��
// ---------------------------------------------------------------------------

class Game : public Window
{
public:
	Game(int width = WIN_W, int height = WIN_H, const char *title = TITLE_NAME);
	~Game(void);

	void Init(); // ������
	void Update(); // �X�V
	void Draw(); // �`��



private:
	Scene* ActiveScene; // ���ݎg�p���Ă���V�[���I�u�W�F�N�g�̃|�C���^
	Scene::SCENE scene; // ���݂ǂ̃V�[�����g�p���Ă��邩

	Loading loading; // ���[�f�B���O��ʂ̕\��

};

