#include "Game.h"

// -----------------------------------------------------------------------
/// コンストラクタ
/// [in] window 使用するウィンドウのハンドル
// -----------------------------------------------------------------------
Game::Game(int width, int height, const char *title)
	: Window(width, height, title)
{
}

// -----------------------------------------------------------------------
/// デストラクタ
// -----------------------------------------------------------------------
Game::~Game(void)
{
	delete ActiveScene;
}




// ----------------------------------------------------------------------
/// 初期化処理
// ----------------------------------------------------------------------
void Game::Init(){
	// タイトルシーンから始まる
	scene = Scene::SCENE::TITLE_SCENE; 
	ActiveScene = new Title(window);

	loading.Init();
}

// -----------------------------------------------------------------------
/// 更新処理
// -----------------------------------------------------------------------
void Game::Update(){
	// ロード中
	if(!ActiveScene->LoadComp()){
		loading.Update();
		return;
	}

	// シーン切り替え確認
	if(ActiveScene->Update() == scene) return;
	else scene = ActiveScene->getScene();

	// シーン切り替え
	switch (scene)
	{
	// タイトル画面へ
	case Scene::TITLE_SCENE:
		delete ActiveScene;
		ActiveScene = new Title(window);
	break;

	// ゲームメインへ
	case Scene::GAMEMAIN_SCENE:
		delete ActiveScene;
		ActiveScene = new GameMain(window);
	break;

	default:
		std::cout << "使用できないシーンを指定しています" << std::endl;
		break;
	}
}


// ----------------------------------------------------------------------
// 描画処理
// ----------------------------------------------------------------------
void Game::Draw(){
	if(!ActiveScene->LoadComp()) {
		loading.Draw();
		return;
	}

	ActiveScene->Draw();
}
