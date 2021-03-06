#pragma once
#include "Common.h"

class Collision
{
public :
	// 円柱どうしの当たり判定
	static bool HitCylinder(glm::vec3 pos1, float r1, float h1, glm::vec3 pos2, float r2, float h2);

	// 球どうしの当たり判定
	static bool HitSphere(glm::vec3 pos1, float r1, glm::vec3 pos2, float r2);

	// AABB当たり判定
	static bool HitAABB(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2);

	// 線分と平面の当たり判定
	static bool HitLineVSPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 planePos, glm::vec3 normal);

	// 線分とポリゴンの当たり判定
	static bool HitLineVSPolygon(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// 線分とポリゴンの交点を求める
	static glm::vec3 CrossPoint(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// 球とポリゴンの当たり判定
	static bool HitSphereVSPolygon(glm::vec3 pos, float r, Polygon polygon);
};

