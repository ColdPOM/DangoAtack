#include "Key.h"


Key::Key(void)
{
}


Key::~Key(void)
{
}

// --------------------------------------------------------------------------------
/// キークラスの初期化
/// キークラスを使用する際は最初にInit()で初期化する必要があります
/// [in] win アクティブウィンドウのハンドル
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
/// キー状態の更新
/// 前フレームでキーが押されていたか、現フレームでキーが押されているか調べます
/// キー取得の関数を呼び出す前に必ず一度だけ呼び出してください
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
/// キーが何も押されていない
/// 何も押されていない場合trueを返します
/// 新たに取得できるキーを追加した場合は押されていない判定をこの関数にも追加してください
/// [out] bool キーを押していない true, 何か押している false 
// --------------------------------------------------------------------------------------
bool Key::NoKey(){
	if(mNowA) return false;
	if(mNowS) return false;
	if(mNowD) return false;
	if(mNowW) return false;
	if(mNowSpace) return false;

	// どのキーも押されていなかった
	return true;
}