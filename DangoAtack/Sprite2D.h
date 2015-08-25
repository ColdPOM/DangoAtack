#pragma once
#include "Common.h"
#include "Shader.h"
#include "DDS.h"

// ----------------------------------------------------------------------
/// 2D�e�N�X�`���[�������N���X
/// �e�N�X�`���[�̍��W�̓E�B���h�E���W�Ŏw�肷��
/// ���W�̓E�B���h�E�̍�������_�Ƃ��鍶����W�n(GLFW�̃X�N���[�����W�ɍ��킹�邽��)
// ----------------------------------------------------------------------

class Sprite2D
{
public:
	Sprite2D(void);
	~Sprite2D(void);

	void Load(const char* fileName);   // �ǂݍ���
	void Draw();   // �`��
	void Draw(float pX, float pY, float alpha = -1.0f); // ���W�Ɠ����x�w��`��

	// �Z�b�^�[
	inline void setScale(const float scale) { mScale = glm::vec2(scale, scale); }
	inline void setScale(const float w, const float h) { mScale = glm::vec2(w, h); }
	inline void setScale(const glm::vec2 scale) { mScale = scale; }
	inline void setPos(const glm::vec2& pos) { mPos = pos; }
	inline void setPos(const float x, const float y) { mPos = glm::vec2(x, y); }
	inline void Move(const float x, const float y) { mPos += glm::vec2(x,y); }   // �w�肵���x�N�g�����ړ�������
	inline void setRotate(const float rot) { mRotate = rot; }
	inline void setAlpha(float alpha) { mAlpha= alpha; }

	// �Q�b�^�[
	inline glm::vec2 getPos() { return mPos; }
	inline float getRotate() { return mRotate; }
	inline glm::vec2 getTexSize() { return mTexSize; } 
	inline float getWidth() { return mTexSize.x; }
	inline float getHeight() { return mTexSize.y; }
	inline float getAlpha() { return mAlpha; }

private:
	Shader shader;		   // �V�F�[�_
	GLuint vertexArray;    // �o�[�e�b�N�X�A���C�I�u�W�F�N�g
	GLuint texID;		   // �e�N�X�`���[��ID

	glm::vec2 mPos;		// ���W
	float mRotate;      // ��]��
	glm::vec2 mScale;   // �g�嗦
	glm::vec2 mTexSize; // �e�N�X�`���[�̃T�C�Y
	float mAlpha;       // �����x
	glm::vec2 mReducedScale; // �}�`�̑傫���Œ�p

	// �V�F�[�_�[�ɑ���f�[�^
	glm::mat4 rotateMatrix;
	glm::mat4 modelMatrix;
};

