#pragma once
#include "Common.h"


// -----------------------------------------------------------------------------------------------------------
/// �E�C���h�E�̐ݒ���s����������N���X
/// ���̃N���X���p�������N���X�̃C���X�^���X����ȏ㐶������K�v������
class Window
{
protected:
	GLFWwindow *window;

public:
	//�R���X�g���N�^
	Window (int width = WIN_W, int height = WIN_H, const char *title = TITLE_NAME); //�E�B���h�E�𐶐����܂�
	// �f�X�g���N�^
	virtual ~Window();	// �E�B���h�E��j�����܂�

	virtual void Init(); // ����������
	virtual void Update(); // �X�V����
	virtual void Draw(); // �`�揈��
	int	shouldClose() {	return	glfwWindowShouldClose(window); } //�E�B���h�E��j�����邩�ǂ���
	void swapBuffers(); // �_�u���o�b�t�@�̐؂�ւ��ƃC�x���g�擾
};

