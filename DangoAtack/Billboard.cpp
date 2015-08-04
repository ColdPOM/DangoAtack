#include "Billboard.h"


Billboard::Billboard(void)
{
}


Billboard::~Billboard(void)
{
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteTextures(1, &texID);
}


// -----------------------------------------------------------------------
/// ���[�h
// -----------------------------------------------------------------------
void Billboard::Load(const char* fileName, const char* path){
	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotate = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);

	// ���_���
	const GLfloat vertexAndUV[] = {
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 1.0f
	};

	// �C���f�b�N�X
	const GLushort indeixes[] = {
		0, 1, 2,
		0, 2, 3
	};


	shader.Create();

	// �V�F�[�_�[�̓ǂݍ���
	shader.LoadandCompile("shader/Billboard.vert", GL_VERTEX_SHADER);
	shader.LoadandCompile("shader/Billboard.frag", GL_FRAGMENT_SHADER);
	shader.Link();

	//�@attribute�ϐ��̏ꏊ���擾
	GLuint vertexLocation = shader.getAttribLocation("Vertex");
	GLuint uvLocation = shader.getAttribLocation("UV");
	
	// ���_�o�b�t�@�̐���
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertexAndUV), vertexAndUV, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// �C���f�b�N�X�o�b�t�@�̐���
	GLuint indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeixes), indeixes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// VAO�̐���
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// ���_�o�b�t�@��o�^
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid*)(0));
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(vertexLocation);
	glEnableVertexAttribArray(uvLocation);

	// �C���f�b�N�X�o�b�t�@��o�^
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);

	// �e�N�X�`���̓ǂݍ���
	dds::DDS texture;
	std::string tex_path = path;
	tex_path += "/";
	tex_path += fileName;
	texID = texture.Load(tex_path.c_str());

	shader.begin();
	shader.Uniform1i("Texture", 0);
	shader.end();
}

// -----------------------------------------------------------------------
/// �v���~�e�B�u�̕`��
// -----------------------------------------------------------------------
void Billboard::Draw(){
	rotateMatrix = glm::rotate(glm::radians(mRotate.z), glm::vec3(0,0,1)) * glm::rotate(glm::radians(mRotate.y), glm::vec3(0,1,0))
							* glm::rotate(glm::radians(mRotate.x), glm::vec3(1,0,0)); 
	modelMatrix = glm::translate(mPos) * rotateMatrix * glm::scale(mScale);
	viewMatrix = glm::lookAt(camPos, lookAt, upper);
	projectionMatrix = glm::perspective(perspective, aspect, NEAR_CLIP, FAR_CLIP);
	pvmMatrix = projectionMatrix * viewMatrix * modelMatrix;

	shader.begin();
	glBindVertexArray(vertexArray);

	// ���j�t�H�[���ϐ��փf�[�^�𑗂�
	shader.UniformMatrix4fv("modelMatrix", modelMatrix);
	shader.UniformMatrix4fv("pvmMatrix", pvmMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	shader.end();
}


// -----------------------------------------------------------------------
/// �r���{�[�h�̕`��
// -----------------------------------------------------------------------
void Billboard::DrawBill(){
	// ������ς���
	float r;
	glm::vec3 vec = camPos - mPos;
	glm::vec2 v = glm::vec2(0, 1);

	// Y���̉�]
	r = glm::acos(glm::dot(v, glm::normalize(glm::vec2(vec.x, vec.z)))) * 180 / glm::pi<float>();
	if(vec.x < 0) r = -r;
	mRotate.y = r;

	// X���̉�]
	float f = glm::length(glm::vec2(vec.x, vec.z));
	r = glm::acos(glm::dot(v, glm::normalize(glm::vec2(vec.y, f)))) * 180 / glm::pi<float>();
	if(vec.y < 0) r = -r;
	mRotate.x = -r;


	Draw();
}


// -----------------------------------------------------------------------
/// Y���r���{�[�h�̕`��
// -----------------------------------------------------------------------
void Billboard::DrawBillY(){
	// ������ς���
	float r;
	glm::vec3 vec = camPos - mPos;
	r = glm::acos(glm::dot(glm::vec2(0, 1), glm::normalize(glm::vec2(vec.x, vec.z)))) * 180 / glm::pi<float>();
	if(vec.x < 0) r = -r;
	mRotate.y = r;

	Draw();
}
