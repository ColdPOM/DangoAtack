#pragma once
#include "Common.h"

class Collision
{
public :
	// �~���ǂ����̓����蔻��
	static bool HitCylinder(glm::vec3 pos1, float r1, float h1, glm::vec3 pos2, float r2, float h2);

	// ���ǂ����̓����蔻��
	static bool HitSphere(glm::vec3 pos1, float r1, glm::vec3 pos2, float r2);

	// AABB�����蔻��
	static bool HitAABB(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2);

	// �����ƕ��ʂ̓����蔻��
	static bool HitLineVSPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 planePos, glm::vec3 normal);

	// �����ƃ|���S���̓����蔻��
	static bool HitLineVSPolygon(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// �����ƃ|���S���̌�_�����߂�
	static glm::vec3 CrossPoint(glm::vec3 point1, glm::vec3 point2, Polygon polygon);

	// ���ƃ|���S���̓����蔻��
	static bool HitSphereVSPolygon(glm::vec3 pos, float r, Polygon polygon);
};

