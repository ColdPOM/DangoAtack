#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform2.hpp"
#include <mutex>

// タイトル
#define TITLE_NAME "DngoChanAttack!"

// 画面情報
#define WIN_W  840        // 画面横幅
#define WIN_H  600        // 画面縦幅
#define FAR_CLIP 1000.0f  // ファークリップ
#define NEAR_CLIP 0.1f    // ニアクリップ

#define FPS 60 // フレームレート

extern float aspect;      // アスペクト比
extern float perspective; // 視野角

extern std::mutex gMutex;

// カメラ
extern glm::vec3 camPos; // カメラ座標
extern glm::vec3 lookAt; // 視点
extern glm::vec3 upper;  // カメラの上方向ベクトル

// リスナー
extern float listnerPos[]; // リスナーの位置

extern float gravity; // 重力加速度

// -------構造体-----------
// ポリゴン情報
struct Polygon {
	glm::vec3 vertex[3];
	glm::vec3 normal;
};