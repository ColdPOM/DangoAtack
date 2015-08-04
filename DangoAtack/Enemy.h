#pragma once
#include "Common.h"
#include "GameObject.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Shot.h"

class EnemyManager;

class Enemy : public GameObject
{
private:
	EnemyManager* mEnemyManager; // �������Ǘ�����}�l�[�W���[
	Player* mPlayer;     // �v���C���[�̎Q�Ɨp
	int mState;			 // �G�̏��
	int mType;           // �G�̎��
	int mHitPoint;       // �G��HP

	float mAtackTime; // �U�����o�������Ԃ̋L�^

	// �J�E���^�Ƃ�
	int mAtackCount;   // �U�����Ԃ̃J�E���g
	int mDeathCount;   // HP���[���ɂȂ��Ă���̎���

	// �t���O
	bool mAtackComp; // �U�����o���؂������ǂ���

	// ZAKO�p
	float mScaleMeter; // �U�����ȂǂɎg���X�P�[���p
	bool mScaleMotion;   // ���[�V�������g�傷�邩�k�����邩
	float mMotionSpeed;  // ���[�V�������x

	// FIRE�p
	Shot* mShot;  // ���˂���e

	// STONE�p
	int mWalkCount;        // ��������̃^�C�~���O���v�邽�߂̃J�E���g
	glm::vec3 mTargetPos;  // �U�����̖ڕW�n�_
	bool mCameTargetPoint; // �ړI�n�ɒ�������
	bool mBarrier;         // �������͖��G

public:
	Enemy(void);
	~Enemy(void);

	enum TYPE { ZAKO, FIRE, STONE, BOSS };       // �G�̎��
	enum STATE { NEUTRAL, ATACK, DAMAGE }; // �G�̏��

	void Init(EnemyManager* EM, Player* player, int type);   // ������
	void Update();  // �X�V

	// ��Ԃ̕ύX
	inline void ChangeState(STATE state) { mState = state; }  

	// ���g���G�l�~�[�}�l�[�W���[�̃A�N�e�B�u���X�g���珜�O����
	void eraseMySelf();

	// �A�N�V����
	void Chase();  // �v���C���[��ǐ�
	void Atack();  // �U������
	void Land();   // ���n����
	void Damage(); // �_���[�W����
	void Turn(glm::vec3 target, float delta);  // �w�肳�ꂽ����������

	// �Q�b�^�[
	inline bool getIsBarrier() { return mBarrier; }
	inline int getType() { return mType; }
	inline int getState() { return mState; }
	inline int getHP() { return mHitPoint; }

	// �Z�b�^�[
	inline void setShot(Shot* shot) { mShot = shot; } // �g�p����e���Z�b�g����

	// �G�̔z�u
	void setEnemy(EnemyManager *EM, Player *player, int type, float x, float y, float z);

	// �G���A�N�e�B�u��
	void Active();

};

