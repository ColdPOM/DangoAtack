#pragma once
#include "Common.h"
#include "Shader.h"

// --------------------------------------------------------------
/// デバッグ用の関数をまとめたクラス
/// 使用する際は最初にInit()で初期化する必要があります
// --------------------------------------------------------------
class DebugGL
{
public:
	DebugGL(void);
	~DebugGL(void);

	void Init();     // 初期化処理

	// vec2の変数にコメントをつけて出力
	static inline void printVec2(const char* comment, glm::vec2 value){
		printf("%s (%f, %f)\n", comment, value.x, value.y);
	}

	// vec3の変数にコメントをつけて出力
	static inline void printVec3(const char* comment, glm::vec3 value){
		printf("%s (%f, %f, %f)\n", comment, value.x, value.y, value.z);
	}

	void DrawLine(glm::vec3 point1, glm::vec3 point2, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)); // 線の描画
	void DrawAxis();   // XYZ軸を表示 
	void DrawSphereCol(glm::vec3 pos, float r, glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f)); // 球の当たり判定の範囲の表示



private:
	Shader shader;
	GLuint vertexbuffer;

	GLuint vertexLocation;
	GLuint colorLocation;

};

