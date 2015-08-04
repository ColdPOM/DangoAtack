#pragma once
#include "Common.h"
#include "PMD.h"
#include "Shader.h"
#include "DDS.h"

// --------------------------------------------------------
/// 3D���f���������N���X
// --------------------------------------------------------
class Model
{
public:
	Model();
	~Model(void);

	void Load(const char* fileName, const char* path);   // �ǂݍ���
	void Draw();   // �`��

	// �Z�b�^�[
	inline void setPos(const glm::vec3& pos) { mPos = pos; }
	inline void setPos(float x, float y, float z) { mPos.x = x; mPos.y = y; mPos.z = z; }
	inline void setScale(const float scale) { mScale = glm::vec3(scale, scale, scale); }
	inline void setScale(const glm::vec3& scale) { mScale = scale; }
	inline void setRotate(const glm::vec3& rot) { mRotate = rot; }
	inline void Move(const glm::vec3& vec) { mPos += vec; }

	// �Q�b�^�[
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
	pmd::PMD pmdfile;      // PMD���f���f�[�^
	Shader shader;		   // �V�F�[�_
	GLuint vertexArray;    // �o�[�e�b�N�X�A���C�I�u�W�F�N�g
	GLuint* texID;		   // �e�N�X�`���[��ID
	Polygon* polygonList;  // �|���S���̈ꗗ 
	GLuint polygonCount;   // �|���S���̐�
	

	bool loadFlag;  // ���f���̃��[�h�����t���O

	glm::vec3 mPos;		// ���W
	glm::vec3 mRotate;  // ��]��
	glm::vec3 mScale;   // �g�嗦

	glm::vec3 mModelSize; // ���f���̃T�C�Y

	// �V�F�[�_�[�ɑ���f�[�^
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::mat4 rotateMatrix;

	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 pvmMatrix;
};

