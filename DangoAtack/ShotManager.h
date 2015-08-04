#pragma once
#include "Common.h"
#include "Shot.h"
#include <vector>

class Shot;

class ShotManager
{
public:
	ShotManager(void);
	~ShotManager(void);

	void Init(const int nom);    // ������
	void Update();				 // �X�V
	void Draw();				 // �`��

	// �Q�b�^�[
	inline Shot* getShots() { return mShots ; }
	inline int getShotCount() { return mShotCount; }
	inline std::vector<Shot*> getActiveList() { return mActiveList; }

	// �A�N�e�B�u���X�g�̑���
	inline void pushActiveObject(Shot* Shot) { mActiveList.push_back(Shot); }    // �A�N�e�B�u���X�g�ɒǉ� 
	inline void eraseActiveObject(int i) {mActiveList.erase(mActiveList.begin() + i); }  // �A�N�e�B�u���X�g��i�Ԗڂ̗v�f���폜
	


private:
	Shot* mShots;                  // �e�I�u�W�F�N�g�z��
	int mShotCount;                // �e�̐�
	std::vector<Shot*> mActiveList;    // �A�N�e�B�u���X�g
};

