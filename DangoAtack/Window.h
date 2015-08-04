#pragma once
#include "Common.h"


// -----------------------------------------------------------------------------------------------------------
/// ウインドウの設定を行い生成するクラス
/// このクラスを継承したクラスのインスタンスを一つ以上生成する必要がある
class Window
{
protected:
	GLFWwindow *window;

public:
	//コンストラクタ
	Window (int width = WIN_W, int height = WIN_H, const char *title = TITLE_NAME); //ウィンドウを生成します
	// デストラクタ
	virtual ~Window();	// ウィンドウを破棄します

	virtual void Init(); // 初期化処理
	virtual void Update(); // 更新処理
	virtual void Draw(); // 描画処理
	int	shouldClose() {	return	glfwWindowShouldClose(window); } //ウィンドウを破棄するかどうか
	void swapBuffers(); // ダブルバッファの切り替えとイベント取得
};

