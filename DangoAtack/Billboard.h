#pragma once
#include "Collision.h"
#include "Shader.h"
#include "DDS.h"

// ----------------------------------------------------------------
/// ビルボードを扱うクラス
/// 通常のビルボードとY軸回転のビルボードが使用できます
// ----------------------------------------------------------------

class Billboard
{
private:
	Shader shader;		   // シェーダ
	GLuint vertexArray;    // バーテックスアレイオブジェクト
	GLuint texID;		   // テクスチャーのID

	glm::vec3 mPos;		// 座標
	glm::vec3 mRotate;  // 回転率
	glm::vec3 mScale;   // 拡大率

	// シェーダーに送るデータ
	glm::mat4 rotateMatrix;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 pvmMatrix;

	// プリミティブの描画
	void Draw();

public:
	Billboard(void);
	~Billboard(void);

	void Load(const char* fileName, const char* path);   // 読み込み
	void DrawBill();  // 通常のビルボード描画
	void DrawBillY(); // Y軸ビルボードの描画

	// セッター
	inline void setScale(const float scale) { mScale = glm::vec3(scale, scale, 1.0f); }
	inline void setScale(const glm::vec2& scale) { mScale = glm::vec3(scale.x, scale.y, 1.0f); }
	inline void setPos(const glm::vec3& pos) { mPos = pos; }
	inline void Move(const glm::vec3& vec) { mPos += vec; }

	// ゲッター
	inline glm::vec3 getPos() { return mPos; }
	inline glm::vec2 getSize() { return glm::vec2(mScale.x, mScale.y); }
	inline glm::mat4 getModelMatrix() { return modelMatrix; }
	inline glm::mat4 getPVM() { return pvmMatrix; }
};

