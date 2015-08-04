#pragma once
#include "Model.h"

class Stage
{
private:
	bool BossBattle; // �{�X��t���O

	Model mGround; // ��
	Model mLand;   // �{�X���
	Model mSky;    // ��
	Model mTree;  // ��
	glm::vec3* mTreePos; // �؂̍��W���X�g
	const int mTreeCount; // �؂̐�

public:
	Stage(void);
	~Stage(void);

	void Init();   // ������
	void Update(); // �X�V
	void Draw();   // �`��

	// �Q�b�^�[
	inline Model* getGround() { return &mGround; } // �����f���̎擾
	inline Model* getLand() { return &mLand; } // �{�X��ꃂ�f���̎擾
	inline float getTreeHeight() { return mTree.getSize().y; } //�؂̍������擾
	inline int getTreeCount() { return mTreeCount; } // �؂̐����擾
	inline glm::vec3* getTreePos() { return mTreePos; } // �؂̍��W���X�g�̎擾

	// ��I�u�W�F�N�g�̍��W�w��
	inline void setSkyPos(glm::vec3 pos) { return mSky.setPos(pos); }

	// �{�X�o�g���t���O�̐ݒ�
	inline void setBossFlag(bool flag) { BossBattle = flag; } 
};

