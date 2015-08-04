#pragma once
#include "Common.h"
#include "GameObject.h"
#include "ShotManager.h"
#include "Billboard.h"

class ShotManager;

class Shot
{
private:
	Billboard mBillboad; // �`�悷��e
	ShotManager* mShotManager; // �������Ǘ�����}�l�[�W���[
	GameObject* mTarget;     // �ڕW�Ƃ���I�u�W�F�N�g
	const float mLifeTime;   // ��������
	float mLifeCount;        // ���˂���Ă���̎���

	glm::vec3 mPos;    // ���W
	float mScale;      // �g�嗦

	bool mIs;            // �����t���O
	glm::vec3 mFront;    // �O���x�N�g��
	glm::vec3 mMoveVec;  // �I�u�W�F�N�g�̓�����\���x�N�g��
	float mSpeed;        // �ړ��X�s�[�h
	bool mVisible;       // ��
	float mDistance;     // �J��������̋���

public:
	Shot(void);
	~Shot(void);

	void Init(ShotManager* SM);    // ������
	void Update();  // �X�V
	void Draw(); // �`��

	void Trigger(const glm::vec3 &pos, GameObject* target); // �e����
	void Fin(); // ����

	// ���g���V���b�g�}�l�[�W���[�̃A�N�e�B�u���X�g�ɒǉ�����
	void pushActiveList();

	// ���g���V���b�g�}�l�[�W���[�̃A�N�e�B�u���X�g���珜�O����
	void eraseMySelf();

	// �Q�b�^�[
	inline glm::vec3 getPos() { return mPos; }		  // �|�W�V�����̎擾
	inline float getScale() { return mScale; }	      // �g�嗦�̎擾
	inline bool getIs() { return mIs; };			  // �����t���O�̎擾			
	inline glm::vec3 getFront() { return mFront; }	   // �O���x�N�g���̎擾
	inline glm::vec3 getMoveVec() { return mMoveVec; } // �ړ��x�N�g���̎擾
	inline bool getVisible() { return mVisible; }    // �����ǂ����擾
	inline float getDistance() { return mDistance; }

	// �Z�b�^�[
	inline void setPos(glm::vec3 pos) { mPos = pos; }	  // �|�W�V�����̐ݒ�
	inline void setScale(float scale) { mScale = scale; } // �g�嗦�̐ݒ�(XYZ�����Ƃ̑傫���w��
	inline void setMoveVec(glm::vec3 vec) { mMoveVec = vec; }  // �ړ��x�N�g����ݒ�
	inline void setVisible(bool visble) { mVisible = visble; } // ����
};

