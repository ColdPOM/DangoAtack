#include "Shader.h"


Shader::Shader(void)
{
}


Shader::~Shader(void)
{
	glDeleteProgram(shaderProgram);
}


// --------------------------------------------------------------------------------
/// シェーダーを開いて読み込みます
/// [in] shader 格納先のシェーダーオブジェクト
/// [in] fileName 読み込むシェーダーファイルのパス
// --------------------------------------------------------------------------------
void Shader::LoadShaderSource(GLuint shader, const char* fileName){

	// オープン失敗
	std::ifstream file(fileName,  std::ios::binary);
	if	(file.fail()){
		std::cerr << "Error: Couldn't open source file: " << fileName << std::endl;
		return;
	}
		
	file.seekg(0, SEEK_END);
	const GLsizei size(static_cast<GLsizei>(file.tellg()));
		
	char* buf = (char*)malloc(size);
	file.seekg(0, SEEK_SET);
	file.read(buf, size);

	// 読み込み失敗
	if	(file.bad()) {
		std::cerr	<<	"Error:	Couldn't read souce	file: "	<<	fileName << std::endl;
		free(buf);
		return;
	}
		
	glShaderSource(shader, 1, (const GLchar**) &buf, &size);
	free(buf);
		
	file.close();
}


// ----------------------------------------------------------------------------------
/// コンパイルエラー表示
/// シェーダのコンパイルエラー時エラーダイアログを表示します
/// [in] shader エラーチェックしたいシェーダーオブジェクト
// ----------------------------------------------------------------------------------
void Shader::DisplayCompileError(GLuint shader){

	GLint compiled;
	int size;
	int len;
	char* status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
	if(compiled == GL_FALSE){
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
		if(size > 0){
			status = (char*) malloc(size);
			glGetShaderInfoLog(shader, size, &len, status);
			std::cerr << "Compile error !\n" << status << std::endl;
			free(status);
		}
	}
}

//----------------------------------------------------------------------------------
/// リンクエラー表示
/// シェーダプログラムのリンクエラー時エラーダイアログを表示します
/// [in] program エラーチェックしたいシェーダプログラム
void Shader::DisplayLinkError(GLuint program){

	GLint linked;
	int size;
	int len;
	char* status;

	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if(linked == GL_FALSE){
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &size);
		if(size > 0) {
			status = (char*) malloc(size);
			glGetProgramInfoLog(program, size, &len, status);
			std::cerr << "Link error !" << status << std::endl;
			free(status);
		}
	}

}

// ---------------------------------------------------------------------------------
/// ロード&コンパイル
/// シェーダーを読み込みコンパイルしアタッチする
/// [in] fileName 読み込むシェーダファイルのフルパス
/// [in] type シェーダーのタイプ
// ---------------------------------------------------------------------------------
void Shader::LoadandCompile(const char* fileName, GLenum type){
	//シェーダー読み込み
	GLuint shaderObj = glCreateShader(type);
	LoadShaderSource(shaderObj, fileName);

	// シェーダーをコンパイル
	glCompileShader(shaderObj);
    DisplayCompileError(shaderObj);

	// シェーダーのアタッチ
	glAttachShader(shaderProgram, shaderObj);

	// シェーダーオブジェクトの削除
	glDeleteShader(shaderObj);
}

// ---------------------------------------------------------------------------------
/// シェーダーのリンク
// ---------------------------------------------------------------------------------
void Shader::Link(){
	glLinkProgram(shaderProgram);
   	DisplayLinkError(shaderProgram);
}


