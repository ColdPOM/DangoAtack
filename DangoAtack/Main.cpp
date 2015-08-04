#include "Common.h"
#include "Game.h"

// リリース時にはコマンドラインウィンドウを消す
#ifndef _DEBUG
#pragma	comment(linker,	"/subsystem:\"windows\"	/entry:\"mainCRTStartup\"")
#endif


// -----------------------------------------------------------------------------------
/// メイン
/// プログラムの始まり
/// ターゲット：Windwos
// -----------------------------------------------------------------------------------
int main(void)
{
	//glfwの初期化
    if (!glfwInit()) exit(EXIT_FAILURE);

	//ウィンドウの生成
	Game gameWindow;

	// glewの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// OpenALの初期化
	ALCdevice* alDevice = alcOpenDevice(nullptr);
	ALCcontext* alContext = alcCreateContext(alDevice, nullptr);
	alcMakeContextCurrent(alContext);

	// OpenGLとOpenALの情報表示
#ifdef _DEBUG
	// OpenGLの情報表示
	std::cout << glGetString(GL_VERSION) << "\n";
	std::cout << glGetString(GL_VENDOR) << "\n";
	std::cout << glGetString(GL_RENDERER) << "\n" << std::endl;

	int n;
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &n) ;
	std::cout << "テクスチャーユニット数 " << n << "\n" << std::endl;

	// OpenALの情報表示
	const ALchar* device_list = alcGetString(nullptr, ALC_DEVICE_SPECIFIER);
	std::cout << "サウンドデバイス " << device_list << "\n" << std::endl;

#endif


	// 背面をカリング
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// ピクセルブレンディングを有効化
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// 深度テストを有効化
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_TEXTURE_2D);

	// 背景色の設定
	glClearColor(0,0,0,0);

	// ゲームの初期化
	gameWindow.Init();

	// タイムの初期化
	glfwSetTime(0.0f);

	// FPS管理用
	const float FRAME_DELTA = 1.0f / FPS; // フレーム間の時間
	float time = 0;         // 時間を格納する変数
	float deltaTime = 0.0f; // 前フレームとの時間差


	//whileループ
    while (gameWindow.shouldClose() ==	GL_FALSE)
    {
		// FPSの固定
		deltaTime = static_cast<float>(glfwGetTime()) - time;
		if(deltaTime < FRAME_DELTA) continue;
		time = static_cast<float>(glfwGetTime());

		// バッファのクリア
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// ウィンドウの更新・描画
		gameWindow.Update();
		gameWindow.Draw();

		gameWindow.swapBuffers();
		glfwPollEvents();

	}

	// 終了処理
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(alContext);
	alcCloseDevice(alDevice);
	glfwTerminate();
    exit(EXIT_SUCCESS);
}