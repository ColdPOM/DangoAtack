#pragma once
#include "Common.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "Sound.h"

class Title : public Scene
{
public:
	Title(GLFWwindow *window);
	~Title(void);

	void Init();    // ������
	SCENE Update();	// �X�V
	void Draw();    // �`��


private:
	Sprite2D mBackTex;  // �w�i�e�N�X�`��
	Sprite2D mStartTex; // �N���b�N�X�^�[�g����

	Sound mBGM;     // BGM
	Sound mStartSE; // ��ʃN���b�N���̉�

	float mFadeSpeed; // �_�ł̑���
	bool mFadeFlag;   // �N���b�N�X�^�[�g�̓_�łɎg��
	bool mStart;      // �X�^�[�g�������ꂽ
};

