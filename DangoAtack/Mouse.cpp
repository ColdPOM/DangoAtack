#include "Mouse.h"


Mouse::Mouse(void)
{
}

Mouse::~Mouse(void)
{
}

// -------------------------------------------------------
/// �}�E�X�N���X�̏�����
/// [in] win �A�N�e�B�u�E�B���h�E�̃n���h��
// -------------------------------------------------------
void Mouse::Init(GLFWwindow *win){
	window = win;
	glfwGetCursorPos(window, &mPosX, &mPosY); 

	mPreLeftButton = false;
	mNowLeftButton = false;
	mPreRightButton = false;
	mNowRightButton = false;
	mPreMiddleButton = false;
	mNowMiddleButton = false;
}

void Mouse::Update(){
	
	// ���{�^��
	mPreLeftButton = mNowLeftButton;
	mNowLeftButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

	// �E�{�^��
	mPreRightButton = mNowRightButton;
	mNowRightButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

	// �E�{�^��
	mPreMiddleButton = mNowMiddleButton;
	mNowMiddleButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);


	// �N���b�N�ʒu�̍��W��ێ�
	// ���{�^��
	if(IsClickLeftButton()){
		glfwGetCursorPos(window, &mPosX, &mPosY);
		mClickPos = glm::vec2(static_cast<float>(mPosX), static_cast<float>(mPosY));
	}

}

// --------------------------------------------------------
/// �}�E�X���W���擾���܂�
/// [out] glm::vec2 �}�E�X���W 
glm::vec2 Mouse::getMousePos(){
	glfwGetCursorPos(window, &mPosX, &mPosY);
	return glm::vec2(static_cast<float>(mPosX), static_cast<float>(mPosY));
}
