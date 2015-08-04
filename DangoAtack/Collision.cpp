#include "Collision.h"


// ------------------------------------------------------------------------------
/// �~���ǂ����̓����蔻��
/// [in] pos1 �~��1�̒��S���W
/// [in] r1   �~��1�̔��a
/// [in] h1   �~��1�̍���
/// [in] pos2 �~��2�̒��S���W
/// [in] r2   �~��2�̔��a
/// [in] h2   �~��2�̍���
/// [out] bool �~���ǂ������������Ă����true�����łȂ����false��Ԃ�
// ------------------------------------------------------------------------------
bool Collision::HitCylinder(glm::vec3 pos1, float r1, float h1, glm::vec3 pos2, float r2, float h2){
	// �������ד�����\�������邩���ׂ�
	if(pos1.y > pos2.y + h2) return false;
	if(pos1.y + h1 < pos2.y) return false;
	
	// �^�ォ�猩���~�̓����蔻��œ������Ă��Ȃ����true�~���ǂ����͓������Ă��Ȃ�
	if(glm::length(glm::vec2(pos1.x, pos1.z) - glm::vec2(pos2.x, pos2.z)) > r1 + r2) return false;

	return true;
}

// ------------------------------------------------------------------------------
/// ���ǂ����̓����蔻��
/// [in] pos1 ��1�̒��S���W
/// [in] r1   ��1�̔��a
/// [in] pos2 ��2�̒��S���W
/// [in] r2   ��2�̔��a
/// [out] bool ���ǂ������������Ă����true�����łȂ����false��Ԃ�
// ------------------------------------------------------------------------------
bool Collision::HitSphere(glm::vec3 pos1, float r1, glm::vec3 pos2, float r2){
	if(glm::length(pos1 - pos2) <= r1 + r2) return true;
	
	return false;
}


// --------------------------------------------------------------------------------------
/// �{�b�N�X���m�̓����蔻��AABB
/// �I�u�W�F�N�g�̒��S�͒�ʂ̒��S�Ƃ���
/// [in] pos1  �{�b�N�X1�̍��W
/// [in] size1 �{�b�N�X1�̃T�C�Y 
/// [in] pos2  �{�b�N�X2�̍��W
/// [in] size2 �{�b�N�X2�̃T�C�Y
/// [out] bool �������Ă���ꍇ��true�����łȂ��ꍇ��false��Ԃ�
// ---------------------------------------------------------------------------------------
bool Collision::HitAABB(glm::vec3 pos1, glm::vec3 size1, glm::vec3 pos2, glm::vec3 size2){
	// ������Ȃ��P�[�X
	if(pos1.y > pos2.y + size2.y) false;
	if(pos1.y + size1.y < pos2.y) false;
	if(pos1.x + size1.x/2 < pos2.x - size2.x/2) false;
	if(pos1.x - size1.x/2 > pos2.x + size2.x/2) false;
	if(pos1.z + size1.z/2 < pos2.z - size2.z/2) false;
	if(pos1.z - size2.z/2 > pos2.z + size2.z/2) false;

	// �S�Ă̓�����Ȃ��P�[�X�ɊY�����Ȃ��ꍇ�͓������Ă���
	return true;
}


// -----------------------------------------------------------------------------------------
/// �����ƕ��ʂ̓����蔻��
/// [in] point1 �����̎n�_
/// [in] point2 �����̏I�_
/// [in] planePos ���ʂ�
/// [out] bool �������Ă���ꍇ��true�����łȂ��ꍇ��false��Ԃ�
// -----------------------------------------------------------------------------------------
bool Collision::HitLineVSPlane(glm::vec3 point1, glm::vec3 point2, glm::vec3 planePos, glm::vec3 normal){
	// �����̕Е��̓_���ʂ̕\���ɂ�������Е��������ɂ���Ƃ��������Ă���
	if(glm::dot(point1 - planePos, normal) * glm::dot(point2 - planePos, normal) <= 0) return true;

	// �������Ă��Ȃ�
	return false;
}


// ------------------------------------------------------------------------------------------
/// �����ƃ|���S���̓����蔻��
/// [in] point1  �����̎n�_
/// [in] point2  �����̏I�_
/// [in] polygon �Ώۂ̃|���S��
/// [out] bool   �������Ă���ꍇ��true�����łȂ��ꍇ��false��Ԃ�
// ------------------------------------------------------------------------------------------
bool Collision::HitLineVSPolygon(glm::vec3 point1, glm::vec3 point2, Polygon polygon){
	// �����ƕ��ʂ��������Ȃ���΃|���S���Ƃ��������Ȃ�
	if(!HitLineVSPlane(point1, point2, polygon.vertex[0], polygon.normal)) return false;

	// �|���S���Ɛ����̌����_
	glm::vec3 crossPoint = CrossPoint(point1, point2, polygon);

	// �|���S���̊e�ӂ�clossPoint����ł���O�p�`�̖@��
	glm::vec3 n1 = glm::normalize(glm::cross(polygon.vertex[1] - polygon.vertex[0], crossPoint - polygon.vertex[1]));
	glm::vec3 n2 = glm::normalize(glm::cross(polygon.vertex[2] - polygon.vertex[1], crossPoint - polygon.vertex[2]));
	glm::vec3 n3 = glm::normalize(glm::cross(polygon.vertex[0] - polygon.vertex[2], crossPoint - polygon.vertex[0]));

	// �e�O�p�`�̖@���ƃ|���S���̖@���̔�r
	if(glm::dot(n1, polygon.normal) <= 0) return false;
	if(glm::dot(n2, polygon.normal) <= 0) return false;
	if(glm::dot(n3, polygon.normal) <= 0) return false;

	// �������Ă���
	return true;
}



// ----------------------------------------------------------------------------------------
/// �����ƃ|���S���̌�_�����߂�
/// [in] point1  �����̎n�_
/// [in] point2  �����̏I�_
/// [in] polygon �Ώۂ̃|���S��
/// [out] vec3   �����ƃ|���S���̌�_���W
// -----------------------------------------------------------------------------------------
glm::vec3 Collision::CrossPoint(glm::vec3 point1, glm::vec3 point2, Polygon polygon){

	// ������
	float d1 = glm::abs(glm::dot(polygon.normal, point1 - polygon.vertex[0])); // point1���畽�ʂ܂ł̋���
	float d2 = glm::abs(glm::dot(polygon.normal, point2 - polygon.vertex[0])); // point2���畽�ʂ܂ł̋���
	float division =  d1 / (d1 + d2);

	// �|���S���̈�̒��_��������ւ̃x�N�g��
	glm::vec3 v1 = point1 - polygon.vertex[0];
	glm::vec3 v2 = point2 - polygon.vertex[0];

	// �����ƃ|���S���̌�_
	glm::vec3 a = polygon.vertex[0] + (1 - division) * v1 + division * v2;

	return a;
}


// ------------------------------------------------------------------------------------------
/// ���ƃ|���S���̓����蔻��
/// [in] pos ���̒��S���W
/// [in] r ���̔��a
/// [in] polygon�@�Ώۂ̃|���S��
/// [out] bool �������Ă���ꍇ��true�����łȂ��ꍇ��false��Ԃ�
// ------------------------------------------------------------------------------------------
bool Collision::HitSphereVSPolygon(glm::vec3 pos, float r, Polygon polygon){
	// pos���畽�ʂ܂ł̋���
	float len = glm::abs(glm::dot(polygon.normal, pos - polygon.vertex[0]));
	// ���ƕ��ʂ��������Ȃ��A�܂��͋����|���S���̗����ɂ���
	if(len > r || glm::dot(pos - polygon.vertex[0], polygon.normal) < 0) return false;

	// �|���S���Ɛ����̌����_
	glm::vec3 crossPoint = CrossPoint(pos, pos - polygon.normal*(r+1), polygon);

	// �|���S���̊e�ӂ�clossPoint����ł���O�p�`�̖@��
	glm::vec3 n1 = glm::normalize(glm::cross(polygon.vertex[1] - polygon.vertex[0], crossPoint - polygon.vertex[1]));
	glm::vec3 n2 = glm::normalize(glm::cross(polygon.vertex[2] - polygon.vertex[1], crossPoint - polygon.vertex[2]));
	glm::vec3 n3 = glm::normalize(glm::cross(polygon.vertex[0] - polygon.vertex[2], crossPoint - polygon.vertex[0]));

	// �e�O�p�`�̖@���ƃ|���S���̖@���̔�r
	if(glm::dot(n1, polygon.normal) <= 0) return false;
	if(glm::dot(n2, polygon.normal) <= 0) return false;
	if(glm::dot(n3, polygon.normal) <= 0) return false;

	// �������Ă���
	return true;
}