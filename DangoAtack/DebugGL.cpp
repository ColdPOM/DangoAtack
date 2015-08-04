#include "DebugGL.h"


DebugGL::DebugGL(void)
{
}


DebugGL::~DebugGL(void)
{
	glDeleteBuffers(1, &vertexbuffer);
}


// ------------------------------------------------------------------------------------------
/// ���������s���܂�
// ------------------------------------------------------------------------------------------
void DebugGL::Init(){
	shader.Create();
	shader.LoadandCompile("shader/Line.vert", GL_VERTEX_SHADER);
	shader.LoadandCompile("shader/Line.frag", GL_FRAGMENT_SHADER);
	shader.Link();

	// VBO�̐���
	glGenBuffers(1, &vertexbuffer);

	//�@attribute�ϐ��̏ꏊ���擾
	vertexLocation = shader.getAttribLocation("Vertex");
	colorLocation = shader.getAttribLocation("Color");
}


// -------------------------------------------------------------------------------------------------
/// ���̕`��
/// [in] point1 �����̎n�_
/// [in] point2 �����̏I�_
// -------------------------------------------------------------------------------------------------
void DebugGL::DrawLine(glm::vec3 point1, glm::vec3 point2, glm::vec3 color){

	// ���_���W�ƃJ���[
	GLfloat vertexes[12] = {
		point1.x, point1.y, point1.z, color.r, color.g, color.b,  
		point2.x, point2.y, point2.z, color.r, color.g, color.b
	};

	// ���_�o�b�t�@�Ƀf�[�^�𑗂�
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (GLfloat) * 12, vertexes, GL_STATIC_DRAW);

	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat)*6, (GLvoid*)(0));
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat)*6, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(vertexLocation);
	glEnableVertexAttribArray(colorLocation);

	glm::mat4 viewMatrix = glm::lookAt(camPos, lookAt, upper);
	glm::mat4 projectionMatrix = glm::perspective(perspective, aspect, NEAR_CLIP, FAR_CLIP);
	glm::mat4 pvmMatrix = projectionMatrix * viewMatrix;

	shader.begin();

	shader.UniformMatrix4fv("pvmMatrix", pvmMatrix);
	glDrawArrays(GL_LINES, 0, 2);
	shader.end();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// -------------------------------------------------------------------------------------------------
/// XYZ����\�����܂�
// -------------------------------------------------------------------------------------------------
void DebugGL::DrawAxis(){
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X��
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y��
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z��
}


// �� ���ݔ��ɔ�����ŏd�����������Ă��邽�ߗv�C��
// -------------------------------------------------------------------------------------------------
/// ���̓����蔻��͈̔͂�\��
/// �����蔻��̊m�F���Ȃǂɕ֗�
/// [in] pos ���̒��S���W���W
/// [in] r   ���̔��a
/// [in] rot ��]��
// -------------------------------------------------------------------------------------------------
void DebugGL::DrawSphereCol(glm::vec3 pos, float r, glm::vec3 rot){
	glm::vec3 point[20];

	for(int i = 0; i < 20; i++){
		point[i] = glm::rotateZ(glm::vec3(r, 0.0f, 0.0f), i*glm::pi<float>()/10);

		point[i] = glm::rotateX(point[i], rot.x * glm::pi<float>() / 180);
		point[i] = glm::rotateY(point[i], rot.y * glm::pi<float>() / 180);
		point[i] = glm::rotateZ(point[i], rot.z * glm::pi<float>() / 180);
		point[i] += pos;

		if(i != 0)DrawLine(point[i-1], point[i]);
	}
	DrawLine(point[19], point[0]);

	for(int i = 0; i < 20; i++){
		point[i] = glm::rotateX(glm::vec3(0.0f, 0.0f, r), i*glm::pi<float>()/10);
		point[i] = glm::rotateX(point[i], rot.x * glm::pi<float>() / 180);
		point[i] = glm::rotateY(point[i], rot.y * glm::pi<float>() / 180);
		point[i] = glm::rotateZ(point[i], rot.z * glm::pi<float>() / 180);
		point[i] += pos;
		if(i != 0)DrawLine(point[i-1], point[i]);
	}
	DrawLine(point[19], point[0]);

	for(int i = 0; i < 20; i++){
		point[i] = glm::rotateY(glm::vec3(0.0f, 0.0f, r), i*glm::pi<float>()/10);
		point[i] = glm::rotateX(point[i], rot.x * glm::pi<float>() / 180);
		point[i] = glm::rotateY(point[i], rot.y * glm::pi<float>() / 180);
		point[i] = glm::rotateZ(point[i], rot.z * glm::pi<float>() / 180);
		point[i] += pos;
		if(i != 0)DrawLine(point[i-1], point[i]);
	}
	DrawLine(point[19], point[0]);
}
