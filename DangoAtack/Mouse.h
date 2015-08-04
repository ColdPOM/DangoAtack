#pragma once
#include "Common.h"

class Mouse
{
private:
	GLFWwindow *window;

	double mPosX, mPosY; // �}�E�X�J�[�\���ʒu
	glm::vec2 mClickPos; // �Ō�ɃN���b�N���ꂽ���W

	bool mPreLeftButton;
	bool mNowLeftButton;
	bool mPreRightButton;
	bool mNowRightButton;
	bool mPreMiddleButton;
	bool mNowMiddleButton;

public:
	Mouse(void);
	~Mouse(void);

	void Init(GLFWwindow *win); // ������
	void Update();              // �}�E�X��Ԃ̍X�V
	
	glm::vec2 getMousePos();												 // �}�E�X���W�̎擾
	inline glm::vec2 getClickPos() { return mClickPos;}						 // �Ō�̃N���b�N�ʒu�̎擾
	inline glm::vec2 getPullVec() { return getMousePos() - getClickPos(); }  // �Ō�̃N���b�N�n�_����}�E�X���W�ւ̃x�N�g��

	// ----------------------------------------------------------------------------
	/// �}�E�X�{�^���̏�Ԏ擾
	/// ���ꂼ��̃{�^����Ԃ��擾�ł��܂�
	/// IsDown:�����Ă���, IsClick:�N���b�N���ꂽ, IsRelease:������, IsUp:�����Ă���
	// ----------------------------------------------------------------------------

	// ���{�^��
	inline bool IsDownLeftButton() { return mNowLeftButton; }
    inline bool IsClickLeftButton() { return !mPreLeftButton && mNowLeftButton; }
    inline bool IsReleaseLeftButton() { return mPreLeftButton && !mNowLeftButton; }
    inline bool IsUpLeftButton() { return !mNowLeftButton; }

	// �E�{�^��
	inline bool IsDownRightButton() { return mNowRightButton; }
    inline bool IsClickRightButton() { return !mPreRightButton && mNowRightButton; }
    inline bool IsReleaseRightButton() { return mPreRightButton && !mNowRightButton; }
    inline bool IsUpRightButton() { return !mNowRightButton; }

	// ���{�^��
	inline bool IsDownMiddleButton() { return mNowMiddleButton; }
    inline bool IsClickMiddleButton() { return !mPreMiddleButton && mNowMiddleButton; }
    inline bool IsReleaseMiddleButton() { return mPreMiddleButton && !mNowMiddleButton; }
    inline bool IsUpMiddleButton() { return !mNowMiddleButton; }
};

