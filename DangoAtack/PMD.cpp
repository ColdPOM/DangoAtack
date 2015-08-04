#include "PMD.h"

namespace pmd {

	PMD::PMD()
	{
	}

	PMD::~PMD(void)
	{
		delete[] vertex;
		delete[] index;
		delete[] material;
		delete[] bone;
	}


	// ----------------------------------------------------------------------------------------
	/// PMDファイルを開き読み込みます
	/// [in] fileName 開くPMDファイルのパス
	// ----------------------------------------------------------------------------------------
	void PMD::Load(const char* fileName)
	{
		float time = static_cast<float>(glfwGetTime());
		// PMDファイルを開く
		std::ifstream file(fileName,  std::ios::binary);
		// オープン失敗
		if (file.fail()){
			std::cerr << "Error: Couldn't open PMD file: " << fileName << "\n" << std::endl;
			return;
		}

		// ヘッダの読み込み
		file.read(signature, sizeof(signature));
		file.read((char*)&header, sizeof(header));
			
		// 頂点情報の読み込み
		float top, bottom, right, left, front, back;
		top = bottom = right = left = front = back = 0;
		vertex = new Vertex[header.vertexCount];
		for(int i = 0; i < header.vertexCount; i++){
			file.read((char*)&vertex[i], 38);
			if(vertex[i].position.y > top) top = vertex[i].position.y;
			if(vertex[i].position.y < bottom) bottom = vertex[i].position.y;
			if(vertex[i].position.x > left) left = vertex[i].position.x;
			if(vertex[i].position.x < right) right = vertex[i].position.x;
			if(vertex[i].position.z > front) front = vertex[i].position.z;
			if(vertex[i].position.z < back) back = vertex[i].position.z;
		}
		// サイズ計算
		size.x = left - right;
		size.y = top - bottom;
		size.z = front - back;

		// インデックスの読み込み
		file.read((char*)&indexCount, 4);
		index = new GLushort[indexCount];
		for(int i = 0; i < indexCount; i++){
			file.read((char*)&index[i], sizeof(GLushort));
		}

		// マテリアル読み込み
		file.read((char*)&materialCount, sizeof GLuint); 
		material = new Material[materialCount];
		for(int i = 0; i < materialCount; i++){
			file.read((char*)&material[i].diffuse, sizeof (GLfloat) * 3); 
			file.read((char*)&material[i].alpha, sizeof (GLfloat)); 
			file.read((char*)&material[i].specularity, sizeof (GLfloat)); 
			file.read((char*)&material[i].specularColor, sizeof (GLfloat) * 3); 
			file.read((char*)&material[i].ambient, sizeof (GLfloat) * 3); 
			file.read((char*)&material[i].toonIndex, sizeof (GLbyte)); 
			file.read((char*)&material[i].edgeFlag, sizeof (GLbyte)); 
			file.read((char*)&material[i].faceVertCount, sizeof (GLuint)); 
			file.read((char*)&material[i].textureName, sizeof (GLchar) * 20); 
		}

		// ボーン読み込み
		file.read((char*)&boneCount, sizeof GLushort);
		bone = new Bone[boneCount];
		for(int i = 0; i < boneCount; i++){
			file.read((char*)&bone[i].boneName, sizeof (GLchar) * 20);
			file.read((char*)&bone[i].parentIndex, sizeof (GLushort));
			file.read((char*)&bone[i].tailIndex, sizeof (GLushort));
			file.read((char*)&bone[i].boneType, sizeof (GLbyte));
			file.read((char*)&bone[i].IKindex, sizeof (GLushort));
			file.read((char*)&bone[i].headPos, sizeof (GLfloat) * 3);
		}


#ifdef _DEBUG
		// ファイル情報の出力
		/*time = static_cast<float>(glfwGetTime()) - time;
		std::cout << fileName << std::endl;
		std::cout << "頂点数：" << header.vertexCount << "\n";
		std::cout << "三角ポリゴン数：" << indexCount/3 << "\n";
		std::cout << "インデックス数：" << indexCount << "\n";
		std::cout << "マテリアル数：" << materialCount << "\n";
		std::cout << "ボーン数：" << boneCount << "\n";
		std::cout << "読み込み時間：" << time << "秒\n" << std::endl;
		*/
#endif

		// ファイルを閉じる
		file.close();

	}

}