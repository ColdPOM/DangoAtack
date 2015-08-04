#pragma once
#include "Common.h"
#include "Model.h"

class GameObject
{
protected:
	Model model; // ���f���f�[�^

	glm::vec3 mPos;    // ���W
	glm::vec3 mScale;  // �g�嗦
	glm::vec3 mRotate; // ��]��

	bool mIs;            // �����t���O
	glm::vec3 mFront;    // �O���x�N�g��
	glm::vec3 mMoveVec;  // �I�u�W�F�N�g�̓�����\���x�N�g��
	float mSpeed;        // �ړ��X�s�[�h
	bool mLand;          // ���n�t���O
	bool mVisible;       // ��

	bool mStopFlag;  // �q�b�g�X�g�b�v�t���O
	int mStopCount;  // �q�b�g�X�g�b�v�J�E���g

	bool mIsCol;        // �����蔻��\���ǂ���
	int mInvaildCount;  // ���G���ԃJ�E���g

public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual void Init();   // ������
	virtual void Update(); // �X�V
	virtual void Draw();   // �`��

	// �q�b�g�X�g�b�v
	/// [in] stopTime �q�b�g�X�g�b�v�̒���(�t���[����)
	inline void Stop(float stopTime) { mStopFlag = true; mStopCount = stopTime; }

	// ���G��
	/// [in] invaildTime ���G���Ԃ̒���(�b)
	inline void InvaildCol(float invaildTime) { mIsCol = false; mInvaildCount = FPS * invaildTime; }

	// �Q�b�^�[
	inline glm::vec3 getPos() { return mPos; }		  // �|�W�V�����̎擾
	inline glm::vec3 getScale() { return mScale; }	  // �g�嗦�̎擾
	inline glm::vec3 getRotate() { return mRotate; }  // ��]���̎擾
	inline bool getIs() { return mIs; };			  // �����t���O�̎擾			
	inline glm::vec3 getFront() { return mFront; }	   // �O���x�N�g���̎擾
	inline glm::vec3 getMoveVec() { return mMoveVec; } // �ړ��x�N�g���̎擾
	inline bool getIsLand() { return mLand; }          // �n�ʂɋ��邩�ǂ�������
	inline glm::vec3 getCenter() { 
		float y = mPos.y + model.getSize().y/2; 
		return glm::vec3(mPos.x, y, mPos.z);}							   // �I�u�W�F�N�g�̒��S�̎擾
	inline glm::vec3 getSize() { return model.getSize(); }				   // �g�嗦���l���������f���̑傫���擾
	inline glm::vec3 getOriginalSize() { return model.getOriginalSize(); } // ���f���̌��̑傫���擾 
	inline bool IsCol() { return  mIsCol; }								   // �����蔻�肪�L�����ǂ���
	inline glm::vec3 getTop() { return mPos + glm::vec3(0.0f, getSize().y, 0.0f); } // �I�u�W�F�N�g�̓����W
	inline bool getVisible() { return mVisible; };                         // �����ǂ����擾

	// �Z�b�^�[
	inline void setPos(glm::vec3 pos) { mPos = pos; }	// �|�W�V�����̐ݒ�
	inline void setPos(float x, float y, float z) { mPos.x = x; mPos.y = y; mPos.z = z; }	// �|�W�V�����̐ݒ�
	inline void setScale(float scale) { mScale.x = scale; mScale.y = scale; mScale.z = scale; } // �g�嗦�̐ݒ�(XYZ�����Ƃ̑傫���w��
	inline void setScale(glm::vec3 scale) { mScale = scale; }  // �g�嗦�̐ݒ�(���f���S�̂̑傫��)
	inline void setMoveVec(glm::vec3 vec) { mMoveVec = vec; }  // �ړ��x�N�g����ݒ�
	inline void setRotate(glm::vec3 rot) { mRotate = rot; }
	inline void setLand(bool land) { mLand = land; }
	inline void setVisible(bool visble) { mVisible = visble; }
};

