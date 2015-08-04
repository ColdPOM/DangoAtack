#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Sprite2D.h"
#include "Sound.h"

class Player : public GameObject
{
public:
	Player(void);
	~Player(void);

	enum STATE { NEUTRAL, SIT, JUMP, AIM, ATACK}; //�@�v���C���[�̏��
	enum FACE { NOMAL, SMILE };             //  �v���C���[�̕\��

	void Init(Mouse *mouse); // ������
	void Update();           // �X�V
	void Draw();             // �`��

	// �A�N�V����
	void Move(const glm::vec2 &mousePos);   // �ړ�
	void Click();  // ��ʂ��N���b�N���ꂽ�Ƃ��̏���
	void Jump();   // �W�����v
	void Land();   // ���n
	void Aim(const glm::vec2 &pullVec);    // �U������������
	void Atack(glm::vec2 pullVec);         // �U��
	void Damage(const glm::vec3 &vec);     // �_���[�W����

	// ��Ԃ̕ύX
	inline void ChangeState(STATE state) { mState = state; }

	// �Q�b�^�[
	inline int getState() { return mState; }
	inline bool getGameOver() { return GameOver; }

	// �{�X��t���O�̃Z�b�g
	inline void setBossFlag(bool flag) { BossBattle = flag; }



private:
	Mouse* mMouse; // �}�E�X�ւ̃n���h�� 

	Sound mJumpSE;
	Sound mAtackSE;

	bool BossBattle; // �{�X��t���O
	bool GameOver;   // �Q�[���I�[�o�[�t���O

	Sprite2D mHeartTex;  // HP�p�e�N�X�`��
	int mHitPoint;       // �G��HP
	glm::vec3 mKeepVec;  // �u���[�L�O�̈ړ��x�N�g���ێ��p
	int mKeepTime;       // mKeepVec��ێ����Ă����鎞��
	glm::vec3 mAimCenter;  // �G�C�����̉�]�̒��S
	glm::vec3 mRestartPos; // �����|�C���g
	bool mFlash;     // �_�ł��邩�ǂ���
	int mFlashCount; // �_�ł̃^�C�~���O�J�E���g
	int mLandCount;  // �����|�C���g�擾�̃^�C�~���O���v�邽�߂̕ϐ�

	bool mScaleMotion;   // ���[�V�������g�傷�邩�k�����邩
	float mMotionSpeed;  // ���[�V�������x

	int mState;      // �v���C���[�̏��
	int mFace;       // �\��
};

