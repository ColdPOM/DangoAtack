#pragma once
#include "Common.h"
#include "Mouse.h"
#include "Sprite2D.h"
#include <thread>

// ------------------------------------------------------
/// �V�[���N���X
/// �p�����Ďg��
// ------------------------------------------------------

class Scene
{
public: 
	
	enum SCENE { TITLE_SCENE, GAMEMAIN_SCENE}; // �V�[���̎��

	Scene(GLFWwindow *window);
	virtual ~Scene(void);

	virtual void Init();    // ������
	virtual SCENE Update();	// �X�V
	virtual void Draw();    // �`��

	void FadeIn(float fadeTime);  // �t�F�[�h�C��
	void FadeOut(float fadeTime); // �t�F�[�h�A�E�g

	// �V�[���̐؂�ւ�
	/// [in] scene �؂�ւ���V�[��
	inline void ChangeScene(SCENE scene) { mScene = scene; } 

	// �ȍ~��V�[����Ԃ�
	// �V�[���؂�ւ��̎��̂ݎg�p
	inline SCENE getScene() { return mScene; }

	inline bool LoadComp() { return mLoadComp; } // ���[�h��������������Ԃ�


	
protected:
	Mouse mMouse; // �}�E�X�I�u�W�F�N�g

	SCENE mScene; // �V�[���؂�ւ��p�B�A�b�v�f�[�g�֐��̖߂�l

	bool mLoadComp;    // �V�[���̃��[�h�����t���O

	float mFadeTime;    // �t�F�[�h�Ɋ|���鎞��
	bool mFadeInStart;  // �t�F�[�h�C���J�n�t���O
	bool mFadeInComp;   // �t�F�[�h�C�������t���O
	bool mFadeOutStart; // �t�F�[�h�A�E�g�����t���O
	bool mFadeOutComp;  // �t�F�[�h�A�E�g�����t���O


private:
	Sprite2D mFadeTex; // �t�F�[�h�p�e�N�X�`��
};

