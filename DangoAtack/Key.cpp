#include "Key.h"


Key::Key(void)
{
}


Key::~Key(void)
{
}

// --------------------------------------------------------------------------------
/// �L�[�N���X�̏�����
/// �L�[�N���X���g�p����ۂ͍ŏ���Init()�ŏ���������K�v������܂�
/// [in] win �A�N�e�B�u�E�B���h�E�̃n���h��
// --------------------------------------------------------------------------------
void Key::Init(GLFWwindow * win){
	window = win;

	mPreA = false;
	mNowA = false;
	mPreS = false;
	mNowS = false;
	mPreD = false;
	mNowD = false;
	mPreW = false;
	mNowW = false;
	mPreSpace = false;
	mNowSpace = false;

}


// ---------------------------------------------------------------------------------
/// �L�[��Ԃ̍X�V
/// �O�t���[���ŃL�[��������Ă������A���t���[���ŃL�[��������Ă��邩���ׂ܂�
/// �L�[�擾�̊֐����Ăяo���O�ɕK����x�����Ăяo���Ă�������
// ---------------------------------------------------------------------------------
void Key::Update(){
    mPreA = mNowA;
	mNowA = (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS);

	mPreS = mNowS;
	mNowS = (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS);

	mPreD = mNowD;
	mNowD = (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS);

	mPreW = mNowW;
	mNowW = (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS);

	mPreSpace = mNowSpace;
	mNowSpace = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS);
}


// -------------------------------------------------------------------------------------
/// �L�[������������Ă��Ȃ�
/// ����������Ă��Ȃ��ꍇtrue��Ԃ��܂�
/// �V���Ɏ擾�ł���L�[��ǉ������ꍇ�͉�����Ă��Ȃ���������̊֐��ɂ��ǉ����Ă�������
/// [out] bool �L�[�������Ă��Ȃ� true, ���������Ă��� false 
// --------------------------------------------------------------------------------------
bool Key::NoKey(){
	if(mNowA) return false;
	if(mNowS) return false;
	if(mNowD) return false;
	if(mNowW) return false;
	if(mNowSpace) return false;

	// �ǂ̃L�[��������Ă��Ȃ�����
	return true;
}