#pragma once
#include "Common.h"

namespace pmd{
	struct Header{
		GLfloat version;        // バージョン
		GLchar name[20];        // 名前
		GLchar comment[256];    // コメント
		GLuint vertexCount;		// 頂点数
	};

	// 頂点情報
	struct Vertex {
		glm::vec3 position;    // 頂点座標
		glm::vec3 normal;      // 法線ベクトル
		glm::vec2 uv;          // UV;
		GLushort boneNom[2];   // 影響を受けるボーンの番号
		GLbyte boneWeight;     // ウェイト
		GLbyte edgeFlag;       // 0:無効 1:有効
	};

	// 材質情報
	struct Material	{
		GLfloat diffuse[3];          // 拡散反射
		GLfloat alpha;               // 透明度
		GLfloat specularity;         // 光沢の強さ	
		GLfloat specularColor[3];	 // 光沢色
		GLfloat ambient[3];          // 環境光
		GLbyte	toonIndex;			 // トゥーンマッピングのインデックス
		GLbyte edgeFlag;             // 輪郭線
		GLuint faceVertCount;	     // 対象インデックス数
		GLchar textureName[20];      // テクスチャ名
	};

	// ボーン情報
	struct Bone	{
		GLchar boneName[20];     // ボーンの名前
		GLushort parentIndex;    // 親ボーンのインデックス
		GLushort tailIndex;      // tail位置のボーンインデックス
		GLbyte boneType;         // ボーンの種類 0:回転 1:回転と移動 2:IK 3:不明 4:IK影響下 5:回転影響下 6:IK接続先 7:非表示
		GLushort IKindex;        // IKボーンインのデックス
		GLfloat headPos[3];      // ボーンの座標
	};




	//-----------------------------------------------------
	/// PMDファイルの読み込みを行うクラス
	/// 読み込む際にはアラインメントに注意
	// ----------------------------------------------------
	class PMD
	{
	public:
		PMD(void);
		~PMD(void);

		void Load(const char* fileName); // 読み込み

		// ゲッター
		inline Header getHeader() { return header; }                  // ヘッダーを返す
		inline Vertex* getVertex() { return vertex; }                 // 頂点リストの先頭ポインタを返す
		inline GLuint getPlygonCount() { return indexCount/3; }       // 三角ポリゴンの数を返す
		inline uint32_t getIndexCount() { return indexCount; }        // インデックス数を返す
		inline GLushort* getIndex() { return index; }				  // インデックスリストの先頭ポインタを返す
		inline GLuint getMaterialCount() { return materialCount; }    // 総マテリアル数を返す
		inline Material* getMaterial() { return material; }		      // マテリアルリストの先頭ポインタを返す
		inline GLushort getBoneCount() { return boneCount; }          // ボーンの数を返す
		inline Bone* getBone() { return bone; }                       // ボーンリストの先頭ポインタを返す
		inline glm::vec3 getSize() { return size; }                   // モデルのサイズを返す



		private:
		char signature[3]; // シグネチャー"Pmd"

		Header header;          // ヘッダ
		Vertex* vertex;         // 頂点リスト
		GLuint indexCount;      // 総インデックス数
		GLushort* index;        // インデックスリスト
		GLuint materialCount;   // マテリアル数
		Material* material;     // マテリアルリスト
		GLushort boneCount;     // ボーン数
		Bone* bone;             // ボーンリスト
		glm::vec3 size;         // モデルの大きさ
	};

}

