#include "Model.h"


Model::Model() : loadFlag(false)
{
}

Model::~Model(void)
{
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteTextures(pmdfile.getMaterialCount(), texID);
	delete[] texID;
	delete[] polygonList;
}

// -----------------------------------------------------------------------------------------------------
/// 読み込み処理
/// [in] fileName 読み込むモデルの名前
/// [in] path ファイルまでのパス
/// [in] mode 0:通常読み込み　1:ボーンのみ読み込み
// -----------------------------------------------------------------------------------------------------
void Model::Load(const char* fileName, const char* path){

	mPos = glm::vec3(0.0f, 0.0f, 0.0f);
	mRotate = glm::vec3(0.0f, 0.0f, 0.0f);
	mScale = glm::vec3(1.0f, 1.0f, 1.0f);

	// PMDファイル読み込み
	std::string path_name = path;
	path_name += "/";
	path_name += fileName;
	pmdfile.Load(path_name.c_str());
	mModelSize = pmdfile.getSize();

	shader.Create();

	// ポリゴンの取得
	polygonCount = pmdfile.getPlygonCount();
	polygonList = new Polygon[polygonCount];
	for(int i = 0; i < polygonCount; i++){
		// 三頂点の座標
		polygonList[i].vertex[0] = pmdfile.getVertex()[pmdfile.getIndex()[i*3]].position;
		polygonList[i].vertex[1] = pmdfile.getVertex()[pmdfile.getIndex()[i*3+1]].position;
		polygonList[i].vertex[2] = pmdfile.getVertex()[pmdfile.getIndex()[i*3+2]].position;

		// 法線の計算
		polygonList[i].normal = glm::normalize(
								glm::cross(polygonList[i].vertex[1] - polygonList[i].vertex[0] , polygonList[i].vertex[2] - polygonList[i].vertex[0]));
	}

	// シェーダーの読み込み
	shader.LoadandCompile("shader/Model.vert", GL_VERTEX_SHADER);
	shader.LoadandCompile("shader/Model.frag", GL_FRAGMENT_SHADER);
	shader.Link();

	//　attribute変数の場所を取得
	GLuint vertexLocation = shader.getAttribLocation("Vertex");
	GLuint normalLocation = shader.getAttribLocation("Normal");
	GLuint uvLocation = shader.getAttribLocation("UV");
	
	// 頂点バッファの生成
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof ((*pmdfile.getVertex())) * pmdfile.getHeader().vertexCount, pmdfile.getVertex(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// インデックスバッファの生成
	GLuint indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof((*pmdfile.getIndex()))*pmdfile.getIndexCount(), pmdfile.getIndex(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// VAOの生成
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// 頂点バッファを登録
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof (pmd::Vertex), (GLvoid*)(0));
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof (pmd::Vertex), (GLvoid*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof (pmd::Vertex), (GLvoid*)(sizeof(GLfloat) * 6));
	glEnableVertexAttribArray(vertexLocation);
	glEnableVertexAttribArray(normalLocation);
	glEnableVertexAttribArray(uvLocation);

	// インデックスバッファを登録
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);

	// テクスチャの読み込み
	dds::DDS texture;
	texID = new GLuint[pmdfile.getMaterialCount()];
	for(int i = 0; i < pmdfile.getMaterialCount(); i++){
		std::string tex_path = path;
		tex_path += "/";
		tex_path += pmdfile.getMaterial()[i].textureName;
		texID[i] = texture.Load(tex_path.c_str());
	}

	shader.begin();
	shader.Uniform1i("Texture", 0);
	shader.end();


	// ボーン読み込み 
	/*GLfloat* boneVertex = new GLfloat[3*2*pmdfile.getBoneCount()];
	for(int i = 0; i < pmdfile.getBoneCount(); i++){
		// ヘッド座標
		boneVertex[i*6] = pmdfile.getBone()[i].headPos[0];
		boneVertex[i*6+1] = pmdfile.getBone()[i].headPos[1];
		boneVertex[i*6+2] = pmdfile.getBone()[i].headPos[2];

		// テイル座標
		boneVertex[i*6+3] = pmdfile.getBone()[pmdfile.getBone()[i].tailIndex].headPos[0];
		boneVertex[i*6+4] = pmdfile.getBone()[pmdfile.getBone()[i].tailIndex].headPos[1];
		boneVertex[i*6+5] = pmdfile.getBone()[pmdfile.getBone()[i].tailIndex].headPos[2];
	}*/

	loadFlag = true;
}



#define BUFFER_OFFSET(bytes) ((GLubyte *)NULL + (bytes))
// -------------------------------------------------------------------------------------------------------------
/// モデルの描画を行います
// -------------------------------------------------------------------------------------------------------------
void Model::Draw(){
	ambientColor = glm::vec4(pmdfile.getMaterial()->ambient[0], pmdfile.getMaterial()->ambient[1], pmdfile.getMaterial()->ambient[2], 1.0);
	diffuseColor = glm::vec4(pmdfile.getMaterial()->diffuse[0], pmdfile.getMaterial()->diffuse[1], pmdfile.getMaterial()->diffuse[2], 1.0);
	rotateMatrix = glm::rotate(glm::radians(mRotate.z), glm::vec3(0,0,1)) * glm::rotate(glm::radians(mRotate.y), glm::vec3(0,1,0))
							* glm::rotate(glm::radians(mRotate.x), glm::vec3(1,0,0)); 
	modelMatrix = glm::translate(mPos) * rotateMatrix * glm::scale(mScale);
	viewMatrix = glm::lookAt(camPos, lookAt, upper);
	projectionMatrix = glm::perspective(perspective, aspect, NEAR_CLIP, FAR_CLIP);
	pvmMatrix = projectionMatrix * viewMatrix * modelMatrix;

	shader.begin();
	glBindVertexArray(vertexArray);

	// ユニフォーム変数へデータを送る
	shader.Uniform1f("time" , glfwGetTime());
	shader.Unifor4fv("ambientColor", ambientColor);
	shader.Unifor4fv("diffuseColor", diffuseColor);
	shader.UniformMatrix4fv("modelMatrix", modelMatrix);
	shader.UniformMatrix4fv("pvmMatrix", pvmMatrix);

	// マテリアルごとに描画を行う
	GLuint beginIndex = 0; 
	for(int i = 0; i < pmdfile.getMaterialCount(); i++){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID[i]);

		glDrawElements(GL_TRIANGLES, pmdfile.getMaterial()[i].faceVertCount, GL_UNSIGNED_SHORT, BUFFER_OFFSET(sizeof((*pmdfile.getIndex())) * beginIndex));
		glBindTexture(GL_TEXTURE_2D, 0);

		beginIndex += pmdfile.getMaterial()[i].faceVertCount; // 各マテリアルの開始位置を記録
	}

	glBindVertexArray(0);
	shader.end();
}
