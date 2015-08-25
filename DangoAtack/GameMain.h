#pragma once
#include "Common.h"
#include "Scene.h"
#include "Stage.h"
#include "Player.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Sprite2D.h"
#include "Sound.h"

// -------------------------------------------------------------------------------
///  ���C���Q�[��
// -------------------------------------------------------------------------------


class GameMain : public Scene
{
public:
	GameMain(GLFWwindow *window);
	~GameMain(void);

	// �}�E�X�z�C�[������̎擾
	static void Wheel(GLFWwindow *window, double x,	double y);

	void Init();    // ������
	SCENE Update();  // �X�V
	void Draw();    // �`��



private:
	bool mPause; // �ꎞ��~�t���O
	static float mWheelCount;

	CollisionManager mCollisionManager;

	// �e�N�X�`��
	Sprite2D mPauseTex;      // �|�[�Y���̕\��
	Sprite2D mGameOverTex;   // �Q�[���I�[�o�[���̕\��
	Sprite2D mGameClearTex;  //�Q�[���N���A�[���̕\��

	// �T�E���h
	Sound BGM;

	// �I�u�W�F�N�g
	Player mPlayer;
	EnemyManager mEnemys;
	Stage mStage;


	// ���\�[�X�̃��[�h
	static void Load(GameMain* self);
};

