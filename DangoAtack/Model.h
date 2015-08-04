#pragma once
#include "Common.h"
#include "PMD.h"
#include "Shader.h"
#include "DDS.h"

// --------------------------------------------------------
/// 3Dモデルを扱うクラス
// --------------------------------------------------------
class Model
{
public:
	Model();
	~Model(void);

	void Load(const char* fileName, const char* path);   // 読み込み
	void Draw();   // 描画

	// セッター
	inline void setPos(const glm::vec3& pos) { mPos = pos; }
	inline void setPos(float x, float y, float z) { mPos.x = x; mPos.y = y; mPos.z = z; }
	inline void setScale(const float scale) { mScale = glm::vec3(scale, scale, scale); }
	inline void setScale(const glm::vec3& scale) { mScale = scale; }
	inline void setRotate(const glm::vec3& rot) { mRotate = rot; }
	inline void Move(const glm::vec3& vec) { mPos += vec; }

	// ゲッター
	inline glm::vec3 getPos() { return mPos; }
	inline glm::vec3 getRotate() { return mRotate; }
	inline glm::vec3 getSize() { return glm::vec3(mModelSize.x * mScale.x, mModelSize.y * mScale.y, mModelSize.z * mScale.z); } 
	inline glm::vec3 getOriginalSize() { return mModelSize; } 
	inline bool IsLoad() { return loadFlag; }
	inline glm::mat4 getModelMatrix() { return modelMatrix; }
	inline glm::mat4 getPVM() { return pvmMatrix; }
	inline Polygon* getPolygons() { return polygonList; }
	inline GLuint getPolygonCount() { return polygonCount; }



private:
	pmd::PMD pmdfile;      // PMDモデルデータ
	Shader shader;		   // シェーダ
	GLuint vertexArray;    // バーテックスアレイオブジェクト
	GLuint* texID;		   // テクスチャーのID
	Polygon* polygonList;  // ポリゴンの一覧 
	GLuint polygonCount;   // ポリゴンの数
	

	bool loadFlag;  // モデルのロード完了フラグ

	glm::vec3 mPos;		// 座標
	glm::vec3 mRotate;  // 回転率
	glm::vec3 mScale;   // 拡大率

	glm::vec3 mModelSize; // モデルのサイズ

	// シェーダーに送るデータ
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::mat4 rotateMatrix;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 pvmMatrix;
};

