#include "Collision.h"


// ------------------------------------------------------------------------------
/// 円柱どうしの当たり判定
/// [in] pos1 円柱1の中心座標
/// [in] r1   円柱1の半径
/// [in] h1   円柱1の高さ
/// [in] pos2 円柱2の中心座標
/// [in] r2   円柱2の半径
/// [in] h2   円柱2の高さ
/// [out] bool 円柱どうしが当たっていればtrueそうでなければfalseを返す
// ------------------------------------------------------------------------------
bool Collision::HitCylinder(glm::vec3 pos1, float r1, float h1, glm::vec3 pos2, float r2, float h2){
	// 高さを比べ当たる可能性があるか調べる
	if(pos1.y > pos2.y + h2) return false;
	if(pos1.y + h1 < pos2.y) return false;
	
	// 真上から見た円の当たり判定で当たっていなければtrue円柱どうしは当たっていない
	if(glm::length(glm::vec2(pos1.x, pos1.z) - glm::vec2(pos2.x, pos2.z)) > r1 + r2) return false;

	return true;
}

// ------------------------------------------------------------------------------
/// 球どうしの当たり判定
/// [in] pos1 球1の中心座標
/// [in] r1   球1の半径
/// [in] pos2 球2の中心座標
/// [in] r2   球2の半径
/// [out] bool 球どうしが当たっていればtrueそうでなければfalseを返す
// ------------------------------------------------------------------------------
bool Collision::HitSphere(glm::vec3 pos1, float r1, glm::vec3 pos2, float r2){
	if(glm::length(pos1 - pos2) <= r1 + r2) return true;
	
	return false;
}


// --------------------------------------------------------------------------------------
/// ボックス同士の当たり判定AABB
/// オブジェクトの中心は底面の中心とする
/// [in] pos1  ボックス1の座標
/// [in] size1 ボックス1のサイズ 
/// [in] pos2  ボックス2の座標
/// [in] size2 ボックス2のサイズ
/// [out] bool 当たっている場合はtrueそうでない場合はfalseを返す
// ---------------------------------------------------------------------------------------
bool Collision::HitAABB(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2){
	// 当たらないケース
	if(pos1.y > pos2.y + size2.y) false;
	if(pos1.y + size1.y < pos2.y) false;
	if(pos1.x + size1.x/2 < pos2.x - size2.x/2) false;
	if(pos1.x - size1.x/2 > pos2.x + size2.x/2) false;
	if(pos1.z + size1.z/2 < pos2.z - size2.z/2) false;
	if(pos1.z - size2.z/2 > pos2.z + size2.z/2) false;

	// 全ての当たらないケースに該当しない場合は当たっている
	return true;
}


// -----------------------------------------------------------------------------------------
/// 線分と平面の当たり判定
/// [in] point1 線分の始点
/// [in] point2 線分の終点
/// [in] planePos 平面の
/// [out] bool 当たっている場合はtrueそうでない場合はfalseを返す
// -----------------------------------------------------------------------------------------
bool Collision::HitLineVSPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 planePos, glm::vec3 normal){
	// 線分の片方の点が面の表側にありもう片方が裏側にあるとき当たっている
	if(glm::dot(point1 - planePos, normal) * glm::dot(point2 - planePos, normal) <= 0) return true;

	// 当たっていない
	return false;
}


// ------------------------------------------------------------------------------------------
/// 線分とポリゴンの当たり判定
/// [in] point1  線分の始点
/// [in] point2  線分の終点
/// [in] polygon 対象のポリゴン
/// [out] bool   当たっている場合はtrueそうでない場合はfalseを返す
// ------------------------------------------------------------------------------------------
bool Collision::HitLineVSPolygon(glm::vec3 point1, glm::vec3 point2, Polygon polygon){
	// 線分と平面が交差しなければポリゴンとも交差しない
	if(!HitLineVSPlane(point1, point2, polygon.vertex[0], polygon.normal)) return false;

	// ポリゴンと線分の交差点
	glm::vec3 crossPoint = CrossPoint(point1, point2, polygon);

	// ポリゴンの各辺とclossPointからできる三角形の法線
	glm::vec3 n1 = glm::normalize(glm::cross(polygon.vertex[1] - polygon.vertex[0], crossPoint - polygon.vertex[1]));
	glm::vec3 n2 = glm::normalize(glm::cross(polygon.vertex[2] - polygon.vertex[1], crossPoint - polygon.vertex[2]));
	glm::vec3 n3 = glm::normalize(glm::cross(polygon.vertex[0] - polygon.vertex[2], crossPoint - polygon.vertex[0]));

	// 各三角形の法線とポリゴンの法線の比較
	if(glm::dot(n1, polygon.normal) <= 0) return false;
	if(glm::dot(n2, polygon.normal) <= 0) return false;
	if(glm::dot(n3, polygon.normal) <= 0) return false;

	// 当たっている
	return true;
}



// ----------------------------------------------------------------------------------------
/// 線分とポリゴンの交点を求める
/// [in] point1  線分の始点
/// [in] point2  線分の終点
/// [in] polygon 対象のポリゴン
/// [out] vec3   線分とポリゴンの交点座標
// -----------------------------------------------------------------------------------------
glm::vec3 Collision::CrossPoint(glm::vec3 point1, glm::vec3 point2, Polygon polygon){

	// 内分比
	float d1 = glm::abs(glm::dot(polygon.normal, point1 - polygon.vertex[0])); // point1から平面までの距離
	float d2 = glm::abs(glm::dot(polygon.normal, point2 - polygon.vertex[0])); // point2から平面までの距離
	float division =  d1 / (d1 + d2);

	// ポリゴンの一つの頂点から線分へのベクトル
	glm::vec3 v1 = point1 - polygon.vertex[0];
	glm::vec3 v2 = point2 - polygon.vertex[0];

	// 線分とポリゴンの交点
	glm::vec3 a = polygon.vertex[0] + (1 - division) * v1 + division * v2;

	return a;
}


// ------------------------------------------------------------------------------------------
/// 球とポリゴンの当たり判定
/// [in] pos 球の中心座標
/// [in] r 球の半径
/// [in] polygon　対象のポリゴン
/// [out] bool 当たっている場合はtrueそうでない場合はfalseを返す
// ------------------------------------------------------------------------------------------
bool Collision::HitSphereVSPolygon(glm::vec3 pos, float r, Polygon polygon){
	// posから平面までの距離
	float len = glm::abs(glm::dot(polygon.normal, pos - polygon.vertex[0]));
	// 球と平面が交差しない、または球がポリゴンの裏側にある
	if(len > r || glm::dot(pos - polygon.vertex[0], polygon.normal) < 0) return false;

	// ポリゴンと線分の交差点
	glm::vec3 crossPoint = CrossPoint(pos, pos - polygon.normal*(r+1), polygon);

	// ポリゴンの各辺とclossPointからできる三角形の法線
	glm::vec3 n1 = glm::normalize(glm::cross(polygon.vertex[1] - polygon.vertex[0], crossPoint - polygon.vertex[1]));
	glm::vec3 n2 = glm::normalize(glm::cross(polygon.vertex[2] - polygon.vertex[1], crossPoint - polygon.vertex[2]));
	glm::vec3 n3 = glm::normalize(glm::cross(polygon.vertex[0] - polygon.vertex[2], crossPoint - polygon.vertex[0]));

	// 各三角形の法線とポリゴンの法線の比較
	if(glm::dot(n1, polygon.normal) <= 0) return false;
	if(glm::dot(n2, polygon.normal) <= 0) return false;
	if(glm::dot(n3, polygon.normal) <= 0) return false;

	// 当たっている
	return true;
}