#include "DebugGL.h"


DebugGL::DebugGL(void)
{
}


DebugGL::~DebugGL(void)
{
	glDeleteBuffers(1, &vertexbuffer);
}


// ------------------------------------------------------------------------------------------
/// 初期化を行います
// ------------------------------------------------------------------------------------------
void DebugGL::Init(){
	shader.Create();
	shader.LoadandCompile("shader/Line.vert", GL_VERTEX_SHADER);
	shader.LoadandCompile("shader/Line.frag", GL_FRAGMENT_SHADER);
	shader.Link();

	// VBOの生成
	glGenBuffers(1, &vertexbuffer);

	//　attribute変数の場所を取得
	vertexLocation = shader.getAttribLocation("Vertex");
	colorLocation = shader.getAttribLocation("Color");
}


// -------------------------------------------------------------------------------------------------
/// 線の描画
/// [in] point1 線分の始点
/// [in] point2 線分の終点
// -------------------------------------------------------------------------------------------------
void DebugGL::DrawLine(glm::vec3 point1, glm::vec3 point2, glm::vec3 color){

	// 頂点座標とカラー
	GLfloat vertexes[12] = {
		point1.x, point1.y, point1.z, color.r, color.g, color.b,  
		point2.x, point2.y, point2.z, color.r, color.g, color.b
	};

	// 頂点バッファにデータを送る
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
/// XYZ軸を表示します
// -------------------------------------------------------------------------------------------------
void DebugGL::DrawAxis(){
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(50.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X軸
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 50.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // Y軸
	DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 50.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // Z軸
}


// ※ 現在非常に非効率で重い処理をしているため要修正
// -------------------------------------------------------------------------------------------------
/// 球の当たり判定の範囲を表示
/// 当たり判定の確認時などに便利
/// [in] pos 球の中心座標座標
/// [in] r   球の半径
/// [in] rot 回転率
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
