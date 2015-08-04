#pragma once
#include "Common.h"
#include "Shader.h"

// --------------------------------------------------------------
/// �f�o�b�O�p�̊֐����܂Ƃ߂��N���X
/// �g�p����ۂ͍ŏ���Init()�ŏ���������K�v������܂�
// --------------------------------------------------------------
class DebugGL
{
public:
	DebugGL(void);
	~DebugGL(void);

	void Init();     // ����������

	// vec2�̕ϐ��ɃR�����g�����ďo��
	static inline void printVec2(const char* comment, glm::vec2 value){
		printf("%s (%f, %f)\n", comment, value.x, value.y);
	}

	// vec3�̕ϐ��ɃR�����g�����ďo��
	static inline void printVec3(const char* comment, glm::vec3 value){
		printf("%s (%f, %f, %f)\n", comment, value.x, value.y, value.z);
	}

	void DrawLine(glm::vec3 point1, glm::vec3 point2, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f)); // ���̕`��
	void DrawAxis();   // XYZ����\�� 
	void DrawSphereCol(glm::vec3 pos, float r, glm::vec3 rot = glm::vec3(0.0f,0.0f,0.0f)); // ���̓����蔻��͈̔͂̕\��



private:
	Shader shader;
	GLuint vertexbuffer;

	GLuint vertexLocation;
	GLuint colorLocation;

};

