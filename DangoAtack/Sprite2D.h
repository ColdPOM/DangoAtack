#pragma once
#include "Common.h"
#include "Shader.h"
#include "DDS.h"

// ----------------------------------------------------------------------
/// 2Dテクスチャーを扱うクラス
/// テクスチャーの座標はウィンドウ座標で指定する
/// 座標はウィンドウの左上を原点とする左手座標系(GLFWのスクリーン座標に合わせるため)
// ----------------------------------------------------------------------

class Sprite2D
{
public:
	Sprite2D(void);
	~Sprite2D(void);

	void Load(const char* fileName);   // 読み込み
	void Draw();   // 描画
	void Draw(float pX, float pY, float alpha = -1.0f); // 座標と透明度指定描画

	// セッター
	inline void setScale(const float scale) { mScale = glm::vec2(scale, scale); }
	inline void setScale(const float w, const float h) { mScale = glm::vec2(w, h); }
	inline void setScale(const glm::vec2 scale) { mScale = scale; }
	inline void setPos(const glm::vec2& pos) { mPos = pos; }
	inline void setPos(const float x, const float y) { mPos = glm::vec2(x, y); }
	inline void Move(const float x, const float y) { mPos += glm::vec2(x,y); }   // 指定したベクトル分移動させる
	inline void setRotate(const float rot) { mRotate = rot; }
	inline void setAlpha(float alpha) { mAlpha= alpha; }

	// ゲッター
	inline glm::vec2 getPos() { return mPos; }
	inline float getRotate() { return mRotate; }
	inline glm::vec2 getTexSize() { return mTexSize; } 
	inline float getWidth() { return mTexSize.x; }
	inline float getHeight() { return mTexSize.y; }
	inline float getAlpha() { return mAlpha; }

private:
	Shader shader;		   // シェーダ
	GLuint vertexArray;    // バーテックスアレイオブジェクト
	GLuint texID;		   // テクスチャーのID

	glm::vec2 mPos;		// 座標
	float mRotate;      // 回転率
	glm::vec2 mScale;   // 拡大率
	glm::vec2 mTexSize; // テクスチャーのサイズ
	float mAlpha;       // 透明度
	glm::vec2 mReducedScale; // 図形の大きさ固定用

	// シェーダーに送るデータ
	glm::mat4 rotateMatrix;
	glm::mat4 modelMatrix;
};

