#include "Mouse.h"


Mouse::Mouse(void)
{
}

Mouse::~Mouse(void)
{
}

// -------------------------------------------------------
/// マウスクラスの初期化
/// [in] win アクティブウィンドウのハンドル
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
	
	// 左ボタン
	mPreLeftButton = mNowLeftButton;
	mNowLeftButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS);

	// 右ボタン
	mPreRightButton = mNowRightButton;
	mNowRightButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS);

	// 右ボタン
	mPreMiddleButton = mNowMiddleButton;
	mNowMiddleButton = (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS);


	// クリック位置の座標を保持
	// 左ボタン
	if(IsClickLeftButton()){
		glfwGetCursorPos(window, &mPosX, &mPosY);
		mClickPos = glm::vec2(static_cast<float>(mPosX), static_cast<float>(mPosY));
	}

}

// --------------------------------------------------------
/// マウス座標を取得します
/// [out] glm::vec2 マウス座標 
glm::vec2 Mouse::getMousePos(){
	glfwGetCursorPos(window, &mPosX, &mPosY);
	return glm::vec2(static_cast<float>(mPosX), static_cast<float>(mPosY));
}
