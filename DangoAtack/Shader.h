#pragma once
#include "Common.h"

// ----------------------------------------------------
/// シェーダーを扱うクラス
// ----------------------------------------------------
class Shader
{
public:
	Shader(void);
	~Shader(void);

	inline void Create() { shaderProgram = glCreateProgram(); } // シェーダプログラムの生成
	void LoadandCompile(const char* fileNam, GLenum type);  // シェーダーのロードとコンパイルそしてアタッチ
	void Link(); // シェーダーのリンク
	inline GLuint getShader(){ return shaderProgram; }   // シェーダープログラムを返す

	// シェーダーを使用する際にbegin()とend()で囲む
	inline void begin() { glUseProgram(shaderProgram) ;} // シェーダーを有効にする
	inline void end() { glUseProgram(0); }				 // シェーダーを無効にする

	// attribute変数のロケーションを返す
	inline GLuint getAttribLocation(const char* variableName) { return glGetAttribLocation(shaderProgram, variableName); }

	// Uniform変数にint型の値を送る
	inline void Uniform1i(const char* variableName, const int value) { glUniform1i(glGetUniformLocation(shaderProgram, variableName), value); }
	// Uniform変数にfloat型の値を送る
	inline void Uniform1f(const char* variableName, const float value) { glUniform1f(glGetUniformLocation(shaderProgram, variableName), value); }
	// Uniform変数にglm::vec2型の値を送る
	inline void Unifor2fv(const char* variableName, const glm::vec2 &vec) { glUniform2fv(glGetUniformLocation(shaderProgram, variableName), 1, &vec[0]); }
	// Uniform変数にglm::vec4型の値を送る
	inline void Unifor4fv(const char* variableName, const glm::vec4 &vec) { glUniform4fv(glGetUniformLocation(shaderProgram, variableName), 1, &vec[0]); }
	// Uniform変数にglm::mat4型の値を送る
	inline void UniformMatrix4fv(const char* variableName, const glm::mat4 &matrix) { glUniformMatrix4fv(glGetUniformLocation(shaderProgram, variableName), 1, GL_FALSE, &matrix[0][0]); }



private:
	GLuint shaderProgram; // シェーダプログラム

	void LoadShaderSource(GLuint shader, const char* fileName);   // シェーダーの読み込み
	void DisplayCompileError(GLuint shader);					  // シェーダーのコンパイルエラー処理
	void DisplayLinkError(GLuint program);					      // シェーダーのリンクエラー処理

};

