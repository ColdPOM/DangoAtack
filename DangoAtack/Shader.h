#pragma once
#include "Common.h"

// ----------------------------------------------------
/// �V�F�[�_�[�������N���X
// ----------------------------------------------------
class Shader
{
public:
	Shader(void);
	~Shader(void);

	inline void Create() { shaderProgram = glCreateProgram(); } // �V�F�[�_�v���O�����̐���
	void LoadandCompile(const char* fileNam, GLenum type);  // �V�F�[�_�[�̃��[�h�ƃR���p�C�������ăA�^�b�`
	void Link(); // �V�F�[�_�[�̃����N
	inline GLuint getShader(){ return shaderProgram; }   // �V�F�[�_�[�v���O������Ԃ�

	// �V�F�[�_�[���g�p����ۂ�begin()��end()�ň͂�
	inline void begin() { glUseProgram(shaderProgram) ;} // �V�F�[�_�[��L���ɂ���
	inline void end() { glUseProgram(0); }				 // �V�F�[�_�[�𖳌��ɂ���

	// attribute�ϐ��̃��P�[�V������Ԃ�
	inline GLuint getAttribLocation(const char* variableName) { return glGetAttribLocation(shaderProgram, variableName); }

	// Uniform�ϐ���int�^�̒l�𑗂�
	inline void Uniform1i(const char* variableName, const int value) { glUniform1i(glGetUniformLocation(shaderProgram, variableName), value); }
	// Uniform�ϐ���float�^�̒l�𑗂�
	inline void Uniform1f(const char* variableName, const float value) { glUniform1f(glGetUniformLocation(shaderProgram, variableName), value); }
	// Uniform�ϐ���glm::vec2�^�̒l�𑗂�
	inline void Unifor2fv(const char* variableName, const glm::vec2 &vec) { glUniform2fv(glGetUniformLocation(shaderProgram, variableName), 1, &vec[0]); }
	// Uniform�ϐ���glm::vec4�^�̒l�𑗂�
	inline void Unifor4fv(const char* variableName, const glm::vec4 &vec) { glUniform4fv(glGetUniformLocation(shaderProgram, variableName), 1, &vec[0]); }
	// Uniform�ϐ���glm::mat4�^�̒l�𑗂�
	inline void UniformMatrix4fv(const char* variableName, const glm::mat4 &matrix) { glUniformMatrix4fv(glGetUniformLocation(shaderProgram, variableName), 1, GL_FALSE, &matrix[0][0]); }



private:
	GLuint shaderProgram; // �V�F�[�_�v���O����

	void LoadShaderSource(GLuint shader, const char* fileName);   // �V�F�[�_�[�̓ǂݍ���
	void DisplayCompileError(GLuint shader);					  // �V�F�[�_�[�̃R���p�C���G���[����
	void DisplayLinkError(GLuint program);					      // �V�F�[�_�[�̃����N�G���[����

};

