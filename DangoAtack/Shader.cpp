#include "Shader.h"


Shader::Shader(void)
{
}


Shader::~Shader(void)
{
	glDeleteProgram(shaderProgram);
}


// --------------------------------------------------------------------------------
/// �V�F�[�_�[���J���ēǂݍ��݂܂�
/// [in] shader �i�[��̃V�F�[�_�[�I�u�W�F�N�g
/// [in] fileName �ǂݍ��ރV�F�[�_�[�t�@�C���̃p�X
// --------------------------------------------------------------------------------
void Shader::LoadShaderSource(GLuint shader, const char* fileName){

	// �I�[�v�����s
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

	// �ǂݍ��ݎ��s
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
/// �R���p�C���G���[�\��
/// �V�F�[�_�̃R���p�C���G���[���G���[�_�C�A���O��\�����܂�
/// [in] shader �G���[�`�F�b�N�������V�F�[�_�[�I�u�W�F�N�g
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
/// �����N�G���[�\��
/// �V�F�[�_�v���O�����̃����N�G���[���G���[�_�C�A���O��\�����܂�
/// [in] program �G���[�`�F�b�N�������V�F�[�_�v���O����
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
/// ���[�h&�R���p�C��
/// �V�F�[�_�[��ǂݍ��݃R���p�C�����A�^�b�`����
/// [in] fileName �ǂݍ��ރV�F�[�_�t�@�C���̃t���p�X
/// [in] type �V�F�[�_�[�̃^�C�v
// ---------------------------------------------------------------------------------
void Shader::LoadandCompile(const char* fileName, GLenum type){
	//�V�F�[�_�[�ǂݍ���
	GLuint shaderObj = glCreateShader(type);
	LoadShaderSource(shaderObj, fileName);

	// �V�F�[�_�[���R���p�C��
	glCompileShader(shaderObj);
    DisplayCompileError(shaderObj);

	// �V�F�[�_�[�̃A�^�b�`
	glAttachShader(shaderProgram, shaderObj);

	// �V�F�[�_�[�I�u�W�F�N�g�̍폜
	glDeleteShader(shaderObj);
}

// ---------------------------------------------------------------------------------
/// �V�F�[�_�[�̃����N
// ---------------------------------------------------------------------------------
void Shader::Link(){
	glLinkProgram(shaderProgram);
   	DisplayLinkError(shaderProgram);
}


