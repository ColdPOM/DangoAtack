#pragma once
#include "Common.h"

namespace pmd{
	struct Header{
		GLfloat version;        // �o�[�W����
		GLchar name[20];        // ���O
		GLchar comment[256];    // �R�����g
		GLuint vertexCount;		// ���_��
	};

	// ���_���
	struct Vertex {
		glm::vec3 position;    // ���_���W
		glm::vec3 normal;      // �@���x�N�g��
		glm::vec2 uv;          // UV;
		GLushort boneNom[2];   // �e�����󂯂�{�[���̔ԍ�
		GLbyte boneWeight;     // �E�F�C�g
		GLbyte edgeFlag;       // 0:���� 1:�L��
	};

	// �ގ����
	struct Material	{
		GLfloat diffuse[3];          // �g�U����
		GLfloat alpha;               // �����x
		GLfloat specularity;         // ����̋���	
		GLfloat specularColor[3];	 // ����F
		GLfloat ambient[3];          // ����
		GLbyte	toonIndex;			 // �g�D�[���}�b�s���O�̃C���f�b�N�X
		GLbyte edgeFlag;             // �֊s��
		GLuint faceVertCount;	     // �ΏۃC���f�b�N�X��
		GLchar textureName[20];      // �e�N�X�`����
	};

	// �{�[�����
	struct Bone	{
		GLchar boneName[20];     // �{�[���̖��O
		GLushort parentIndex;    // �e�{�[���̃C���f�b�N�X
		GLushort tailIndex;      // tail�ʒu�̃{�[���C���f�b�N�X
		GLbyte boneType;         // �{�[���̎�� 0:��] 1:��]�ƈړ� 2:IK 3:�s�� 4:IK�e���� 5:��]�e���� 6:IK�ڑ��� 7:��\��
		GLushort IKindex;        // IK�{�[���C���̃f�b�N�X
		GLfloat headPos[3];      // �{�[���̍��W
	};




	//-----------------------------------------------------
	/// PMD�t�@�C���̓ǂݍ��݂��s���N���X
	/// �ǂݍ��ލۂɂ̓A���C�������g�ɒ���
	// ----------------------------------------------------
	class PMD
	{
	public:
		PMD(void);
		~PMD(void);

		void Load(const char* fileName); // �ǂݍ���

		// �Q�b�^�[
		inline Header getHeader() { return header; }                  // �w�b�_�[��Ԃ�
		inline Vertex* getVertex() { return vertex; }                 // ���_���X�g�̐擪�|�C���^��Ԃ�
		inline GLuint getPlygonCount() { return indexCount/3; }       // �O�p�|���S���̐���Ԃ�
		inline uint32_t getIndexCount() { return indexCount; }        // �C���f�b�N�X����Ԃ�
		inline GLushort* getIndex() { return index; }				  // �C���f�b�N�X���X�g�̐擪�|�C���^��Ԃ�
		inline GLuint getMaterialCount() { return materialCount; }    // ���}�e���A������Ԃ�
		inline Material* getMaterial() { return material; }		      // �}�e���A�����X�g�̐擪�|�C���^��Ԃ�
		inline GLushort getBoneCount() { return boneCount; }          // �{�[���̐���Ԃ�
		inline Bone* getBone() { return bone; }                       // �{�[�����X�g�̐擪�|�C���^��Ԃ�
		inline glm::vec3 getSize() { return size; }                   // ���f���̃T�C�Y��Ԃ�



		private:
		char signature[3]; // �V�O�l�`���["Pmd"

		Header header;          // �w�b�_
		Vertex* vertex;         // ���_���X�g
		GLuint indexCount;      // ���C���f�b�N�X��
		GLushort* index;        // �C���f�b�N�X���X�g
		GLuint materialCount;   // �}�e���A����
		Material* material;     // �}�e���A�����X�g
		GLushort boneCount;     // �{�[����
		Bone* bone;             // �{�[�����X�g
		glm::vec3 size;         // ���f���̑傫��
	};

}

