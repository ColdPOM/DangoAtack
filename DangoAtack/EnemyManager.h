#pragma once
#include "Enemy.h"
#include "Player.h"
#include "ShotManager.h"
#include <vector>

class Enemy;

class EnemyManager
{
private:
	bool GameClear; // �Q�[���N���A�t���O

	Player* mPlayer;                    // �v���C���[�I�u�W�F�N�g�̃|�C���^
	Enemy* mEnemys;                     // �G�I�u�W�F�N�g�z��
	const int mEnemyCount;              // �o���ł���G�̐�
	std::vector<Enemy*> mActiveList;    // �A�N�e�B�u���X�g

	ShotManager mShotManager; // �G�����e�̓V���b�g�}�l�[�W���[�ŊǗ�

public:
	EnemyManager(void);
	~EnemyManager(void);

	void Init(Player *player);    // ������
	void Update();  // �X�V
	void Draw();    // �`��

	enum TYPE { ZAKO, FIRE, STONE, BOSS };  // �G�̎��
	void SetEnemy(int nom, TYPE type, float x, float y, float z); // �G��z�u����
	void ActiveEnemy(int beginNom, int endNom); // �G���A�N�e�B�u��Ԃɂ���

	// �Q�b�^�[
	inline Enemy* getEnemys() { return mEnemys ; }
	inline int getEnemyCount() { return mEnemyCount; }
	inline std::vector<Enemy*>* getActiveList() { return &mActiveList; }
	inline ShotManager* getShotManager() { return &mShotManager; }
	inline bool getGameClear() { return GameClear; }

	// �A�N�e�B�u���X�g�̑���
	inline void pushActiveObject(Enemy* enemy) { mActiveList.push_back(enemy); }       // �����ɔ�����s��Enemy�ւ̎Q�Ƃ�ǉ� 
	inline void eraseActiveObject(int i) { mActiveList.erase(mActiveList.begin() + i); }  // �A�N�e�B�u���X�g��i�Ԗڂ̗v�f���폜
};

