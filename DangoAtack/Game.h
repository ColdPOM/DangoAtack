#pragma once
#include "Window.h"
#include "Common.h"
#include "Scene.h"
#include "Title.h"
#include "GameMain.h"
#include "Loading.h"

// ---------------------------------------------------------------------------
/// ゲームウィンドウ
/// シーンの管理などを行う
// ---------------------------------------------------------------------------

class Game : public Window
{
public:
	Game(int width = WIN_W, int height = WIN_H, const char *title = TITLE_NAME);
	~Game(void);

	void Init(); // 初期化
	void Update(); // 更新
	void Draw(); // 描画



private:
	Scene* ActiveScene; // 現在使用しているシーンオブジェクトのポインタ
	Scene::SCENE scene; // 現在どのシーンを使用しているか

	Loading loading; // ローディング画面の表示

};

