#pragma once
#include "Collision.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Stage.h"
#include "Sound.h"

class CollisionManager
{
private:
	bool BossBattle; // �{�X��t���O

	Sound mHitSE;

public:
	CollisionManager(void);
	~CollisionManager(void);

	void PlayerVSEnemy(Player &player, EnemyManager &EM); // �v���C���[�ƓG
	void EnemyVSEnemy(EnemyManager &EM);				  // �G���m�̓����蔻��
	void PlayerVSStage(Player &player, Stage &stage);	  // �v���C���[�ƃX�e�[�W
	void EnemysVSStage(EnemyManager &EM, Stage &stage);   // �G�ƃX�e�[�W
	void PlayerVSShot(Player &player, ShotManager* SM);   // �e�ƃv���C���[

	// �{�X�o�g���t���O�̐ݒ�
	inline void setBossFlag(bool flag) { BossBattle = flag; }
};

