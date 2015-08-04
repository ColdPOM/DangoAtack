#include "Sprite2D.h"

// --------------------------------------------------------
/// コンストラクタ
// --------------------------------------------------------
Sprite2D::Sprite2D(void):
	mPos(glm::vec2(0.0f, 0.0f)),
	mRotate(0),
	mScale(glm::vec2(1.0f, 1.0f)),
	mAlpha(1.0f)
{
}


Sprite2D::~Sprite2D(void)
{
	glDeleteVertexArrays(1, &vertexArray);
	glDeleteTextures(1, &texID);
}


// --------------------------------------------------------------
/// 読み込み
/// [in] fileName ファイルのパスと名前
// --------------------------------------------------------------
void Sprite2D::Load(const char* fileName){

	// テクスチャの読み込み
	dds::DDS texture;
	texID = texture.Load(fileName);

	mTexSize.x = texture.getWidth();
	mTexSize.y = texture.getHeight();

	// ウィンドウサイズと画像サイズの比率
	glm::vec2 size = glm::vec2(texture.getWidth() / static_cast<float>(WIN_W), texture.getHeight() / static_cast<float>(WIN_H));

	// 頂点情報
	const GLfloat vertexAndUV[] = {
		size.x, size.y, 0.0f, 1.0f, 0.0f,
		-size.x, size.y, 0.0f, 0.0f, 0.0f,
		-size.x, -size.y, 0.0f, 0.0f, 1.0f,
		size.x, -size.y, 0.0f, 1.0f, 1.0f
	};

	// インデックス
	const GLushort indeixes[] = {
		0, 1, 2,
		0, 2, 3
	};


	shader.Create();

	// シェーダーの読み込み
	shader.LoadandCompile("shader/Sprite2D.vert", GL_VERTEX_SHADER);
	shader.LoadandCompile("shader/Sprite2D.frag", GL_FRAGMENT_SHADER);
	shader.Link();

	//　attribute変数の場所を取得
	GLuint vertexLocation = shader.getAttribLocation("Vertex");
	GLuint uvLocation = shader.getAttribLocation("UV");
	
	// 頂点バッファの生成
	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof (vertexAndUV), vertexAndUV, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// インデックスバッファの生成
	GLuint indexbuffer;
	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeixes), indeixes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// VAOの生成
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	// 頂点バッファを登録
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid*)(0));
	glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, sizeof (GLfloat) * 5, (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(vertexLocation);
	glEnableVertexAttribArray(uvLocation);

	// インデックスバッファを登録
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glBindVertexArray(0);
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);

	// テクスチャを送る
	shader.begin();
	shader.Uniform1i("Texture", 0);
	shader.end();
}


// -------------------------------------------------------------
/// 描画
// -------------------------------------------------------------
void Sprite2D::Draw(){
	glm::vec3 drawPos;
	drawPos.x = -1.0f + mTexSize.x / static_cast<float>(WIN_W) + mPos.x  / static_cast<float>(WIN_W) * 2.0f; 
	drawPos.y = 1.0f - mTexSize.y / static_cast<float>(WIN_H) - mPos.y / static_cast<float>(WIN_H) * 2.0f;

	rotateMatrix = glm::rotate(glm::radians(mRotate), glm::vec3(0.0f,0.0f,1.0f));
	modelMatrix = glm::translate(glm::vec3(drawPos.x, drawPos.y, 0.0f)) * rotateMatrix * glm::scale(glm::vec3(mScale.x, mScale.y, 1.0f));

	shader.begin();
	glBindVertexArray(vertexArray);

	// ユニフォーム変数へデータを送る
	shader.UniformMatrix4fv("modelMatrix", modelMatrix);
	shader.Uniform1f("Alpha", mAlpha);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	shader.end();
}


// -------------------------------------------------------------
/// 座標指定と透明度指定描画
/// [in] pX 描画先のX座標
/// [in] pY 描画先のY座標
/// [in] alpha 透明度,指定しなければ現在の透明度で描画される
// -------------------------------------------------------------
void Sprite2D::Draw(float pX, float pY, float alpha){
	mPos = glm::vec2(pX, pY);
	if(alpha >= 0.0)mAlpha = alpha;
	glm::vec3 drawPos;
	drawPos.x = -1.0f + mTexSize.x / static_cast<float>(WIN_W) + mPos.x  / static_cast<float>(WIN_W) * 2.0f; 
	drawPos.y = 1.0f - mTexSize.y / static_cast<float>(WIN_H) - mPos.y / static_cast<float>(WIN_H) * 2.0f;

	rotateMatrix = glm::rotate(glm::radians(mRotate), glm::vec3(0.0f,0.0f,1.0f));
	modelMatrix = glm::translate(glm::vec3(drawPos.x, drawPos.y, 0.0f)) * rotateMatrix * glm::scale(glm::vec3(mScale.x, mScale.y, 1.0f));

	shader.begin();
	glBindVertexArray(vertexArray);

	// ユニフォーム変数へデータを送る
	shader.UniformMatrix4fv("modelMatrix", modelMatrix);
	shader.Uniform1f("Alpha", mAlpha);
	glDisable(GL_DEPTH_TEST);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	shader.end();
}
