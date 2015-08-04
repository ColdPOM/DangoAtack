#pragma once
#include "Collision.h"
#include "Shader.h"
#include "DDS.h"

// ----------------------------------------------------------------
/// �r���{�[�h�������N���X
/// �ʏ�̃r���{�[�h��Y����]�̃r���{�[�h���g�p�ł��܂�
// ----------------------------------------------------------------

class Billboard
{
private:
	Shader shader;		   // �V�F�[�_
	GLuint vertexArray;    // �o�[�e�b�N�X�A���C�I�u�W�F�N�g
	GLuint texID;		   // �e�N�X�`���[��ID

	glm::vec3 mPos;		// ���W
	glm::vec3 mRotate;  // ��]��
	glm::vec3 mScale;   // �g�嗦

	// �V�F�[�_�[�ɑ���f�[�^
	glm::mat4 rotateMatrix;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 pvmMatrix;

	// �v���~�e�B�u�̕`��
	void Draw();

public:
	Billboard(void);
	~Billboard(void);

	void Load(const char* fileName, const char* path);   // �ǂݍ���
	void DrawBill();  // �ʏ�̃r���{�[�h�`��
	void DrawBillY(); // Y���r���{�[�h�̕`��

	// �Z�b�^�[
	inline void setScale(const float scale) { mScale = glm::vec3(scale, scale, 1.0f); }
	inline void setScale(const glm::vec2& scale) { mScale = glm::vec3(scale.x, scale.y, 1.0f); }
	inline void setPos(const glm::vec3& pos) { mPos = pos; }
	inline void Move(const glm::vec3& vec) { mPos += vec; }

	// �Q�b�^�[
	inline glm::vec3 getPos() { return mPos; }
	inline glm::vec2 getSize() { return glm::vec2(mScale.x, mScale.y); }
	inline glm::mat4 getModelMatrix() { return modelMatrix; }
	inline glm::mat4 getPVM() { return pvmMatrix; }
};

