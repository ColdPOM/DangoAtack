#include "EnemyManager.h"


EnemyManager::EnemyManager(void):
	mEnemyCount(75)
{
}


EnemyManager::~EnemyManager(void)
{
	delete[] mEnemys;
}


// -------------------------------------------------------------
/// ������
// -------------------------------------------------------------
void EnemyManager::Init(Player *player){
	GameClear = false;

	mPlayer = player;

	mEnemys = new Enemy[mEnemyCount]();
	int shotCount = 0; // �S�̂ŕK�v�Ȓe�̐�

	// �G�̏������Ɣz�u
	// ---- ��ڂ̓� ----
	// ���g
	SetEnemy(0, TYPE::ZAKO, -20.0f, 10.0f, 90.0f);
	SetEnemy(1, TYPE::ZAKO, -10.0f, 15.0f, 103.0f);
	SetEnemy(2, TYPE::ZAKO, 0.0f, 13.0f, 105.0f);
	SetEnemy(3, TYPE::ZAKO, 10.0f, 20.0f, 95.0f);

	// ���g
	SetEnemy(4, TYPE::ZAKO, -20.0f, 10.0f, 130.0f);
	SetEnemy(5, TYPE::FIRE, -10.0f, 15.0f, 143.0f);
	SetEnemy(6, TYPE::FIRE, 0.0f, 13.0f, 145.0f);
	SetEnemy(7, TYPE::ZAKO, 10.0f, 20.0f, 135.0f);
	SetEnemy(8, TYPE::ZAKO, 20.0f, 20.0f, 130.0f);

	// ---- ��ڂ̓� ----
	// ������O
	SetEnemy(9, TYPE::ZAKO, -10.0f, 10.0f, 260.0f);
	SetEnemy(10, TYPE::FIRE, 0.0f, 15.0f, 273.0f);
	SetEnemy(11, TYPE::FIRE, 10.0f, 13.0f, 275.0f);
	SetEnemy(12, TYPE::ZAKO, 20.0f, 20.0f, 265.0f);
	SetEnemy(13, TYPE::ZAKO, 30.0f, 20.0f, 260.0f);
	SetEnemy(14, TYPE::ZAKO, -5.0f, 20.0f, 260.0f);

	// �E��O
	SetEnemy(15, TYPE::ZAKO, -60.0f, 10.0f, 270.0f);
	SetEnemy(16, TYPE::FIRE, -50.0f, 15.0f, 283.0f);
	SetEnemy(17, TYPE::FIRE, -40.0f, 13.0f, 285.0f);
	SetEnemy(18, TYPE::ZAKO, -50.0f, 20.0f, 275.0f);
	SetEnemy(19, TYPE::ZAKO, -60.0f, 20.0f, 280.0f);
	SetEnemy(20, TYPE::ZAKO, -55.0f, 20.0f, 275.0f);

	// ����O
	SetEnemy(21, TYPE::ZAKO, 60.0f, 10.0f, 270.0f);
	SetEnemy(22, TYPE::FIRE, 50.0f, 15.0f, 283.0f);
	SetEnemy(23, TYPE::FIRE, 40.0f, 13.0f, 285.0f);
	SetEnemy(24, TYPE::ZAKO, 50.0f, 20.0f, 275.0f);
	SetEnemy(25, TYPE::ZAKO, 60.0f, 20.0f, 280.0f);
	SetEnemy(26, TYPE::ZAKO, 55.0f, 20.0f, 275.0f);

	// ��������
	SetEnemy(27, TYPE::ZAKO, -10.0f, 10.0f, 360.0f);
	SetEnemy(28, TYPE::STONE, 0.0f, 15.0f, 373.0f);
	SetEnemy(29, TYPE::FIRE, 10.0f, 13.0f, 375.0f);
	SetEnemy(30, TYPE::ZAKO, 20.0f, 20.0f, 365.0f);
	SetEnemy(31, TYPE::ZAKO, 30.0f, 20.0f, 360.0f);
	SetEnemy(32, TYPE::ZAKO, -5.0f, 20.0f, 360.0f);

	// �E��O
	SetEnemy(33, TYPE::ZAKO, -60.0f, 10.0f, 370.0f);
	SetEnemy(34, TYPE::FIRE, -50.0f, 15.0f, 383.0f);
	SetEnemy(35, TYPE::STONE, -40.0f, 13.0f, 385.0f);
	SetEnemy(36, TYPE::ZAKO, -50.0f, 20.0f, 375.0f);
	SetEnemy(37, TYPE::ZAKO, -60.0f, 20.0f, 380.0f);
	SetEnemy(38, TYPE::ZAKO, -55.0f, 20.0f, 375.0f);

	// ����O
	SetEnemy(39, TYPE::ZAKO, 60.0f, 10.0f, 370.0f);
	SetEnemy(40, TYPE::FIRE, 50.0f, 15.0f, 383.0f);
	SetEnemy(41, TYPE::STONE, 40.0f, 13.0f, 385.0f);
	SetEnemy(42, TYPE::ZAKO, 50.0f, 20.0f, 375.0f);
	SetEnemy(43, TYPE::ZAKO, 60.0f, 20.0f, 380.0f);
	SetEnemy(44, TYPE::ZAKO, 55.0f, 20.0f, 375.0f);

	// ��2�̋��̎�O
	SetEnemy(45, TYPE::STONE, 0.0f, 10.0f, 440.0f);
	SetEnemy(46, TYPE::STONE, 20.0f, 10.0f, 440.0f);

	// ��2�̋�����
	SetEnemy(47, TYPE::ZAKO, 15.0f, 10.0f, 580.0f);
	SetEnemy(48, TYPE::ZAKO, 15.0f, 15.0f, 593.0f);
	SetEnemy(49, TYPE::ZAKO, 20.0f, 13.0f, 595.0f);
	SetEnemy(50, TYPE::ZAKO, 20.0f, 20.0f, 585.0f);
	SetEnemy(51, TYPE::ZAKO, 25.0f, 20.0f, 590.0f);
	SetEnemy(52, TYPE::ZAKO, 25.0f, 20.0f, 585.0f);
	SetEnemy(53, TYPE::ZAKO, 5.0f, 10.0f, 580.0f);
	SetEnemy(54, TYPE::ZAKO, 5.0f, 15.0f, 593.0f);
	SetEnemy(55, TYPE::ZAKO, 0.0f, 13.0f, 595.0f);
	SetEnemy(56, TYPE::ZAKO, 0.0f, 20.0f, 585.0f);
	SetEnemy(57, TYPE::ZAKO, -5.0f, 20.0f, 590.0f);
	SetEnemy(58, TYPE::ZAKO, -5.0f, 20.0f, 585.0f);

	// ��2�̋��̍Ō�
	SetEnemy(59, TYPE::STONE, 15.0f, 10.0f, 690.0f);
	SetEnemy(60, TYPE::STONE, 5.0f, 10.0f, 690.0f);
	SetEnemy(61, TYPE::FIRE, 20.0f, 10.0f, 690.0f);
	SetEnemy(62, TYPE::FIRE, 0.0f, 10.0f, 690.0f);

	// ���X�g
	SetEnemy(63, TYPE::BOSS, 10.0f, 50.0f, 900.0f);
	SetEnemy(64, TYPE::STONE, 100.0f, 10.0f, 950.0f);
	SetEnemy(65, TYPE::STONE, -80.0f, 10.0f, 950.0f);
	SetEnemy(66, TYPE::FIRE, 50.0f, 10.0f, 960.0f);
	SetEnemy(67, TYPE::FIRE, -50.0f, 10.0f, 960.0f);
	SetEnemy(68, TYPE::FIRE, 10.0f, 10.0f, 960.0f);
	SetEnemy(69, TYPE::ZAKO, 20.0f, 10.0f, 950.0f);
	SetEnemy(70, TYPE::ZAKO, 25.0f, 15.0f, 973.0f);
	SetEnemy(71, TYPE::ZAKO, 30.0f, 13.0f, 960.0f);
	SetEnemy(72, TYPE::ZAKO, -20.0f, 10.0f, 950.0f);
	SetEnemy(73, TYPE::ZAKO, -25.0f, 15.0f, 973.0f);
	SetEnemy(74, TYPE::ZAKO, -30.0f, 13.0f, 960.0f);


	for(int i = 0; i < mEnemyCount; i++){
		// �K�v�e���̃J�E���g
		if(mEnemys[i].getType() == TYPE::FIRE) shotCount++;
	}

	mShotManager.Init(shotCount); // �V���b�g�}�l�[�W���[�̏�����

	// �e��K�v�Ƃ���G�ɒe������U��
	shotCount = 0;
	for(int i = 0; i < mEnemyCount; i++){
		if(mEnemys[i].getType() == TYPE::FIRE){
			mEnemys[i].setShot(&mShotManager.getShots()[shotCount]);
			shotCount++;

			// �S�e������U��I������烋�[�v�𔲂���
			if(shotCount >= mShotManager.getShotCount()) break;
		}
	}
}


// -------------------------------------------------------------
/// �X�V
// -------------------------------------------------------------
void EnemyManager::Update(){
	// �G�̃A�N�e�B�u��
	// ---- ��ڂ̓� ----
	// ���g
	if(mPlayer->getPos().z > 70) ActiveEnemy(0,3);

	// ���g
	if(mPlayer->getPos().z > 120) ActiveEnemy(4, 8);

	// ---- ��ڂ̓� ----
	// ������O
	if(glm::length(mPlayer->getPos() - glm::vec3(0.0f, 0.0f, 260)) < 30) ActiveEnemy(9, 14);

	// �E��O
	if(glm::length(mPlayer->getPos() - glm::vec3(-60.0f, 0.0f, 270)) < 30) ActiveEnemy(15, 20);

	// ����O
	if(glm::length(mPlayer->getPos() - glm::vec3(60.0f, 0.0f, 270)) < 30)	ActiveEnemy(21, 26);

	// ��������
	if(glm::length(mPlayer->getPos() - glm::vec3(0.0f, 0.0f, 350)) < 30) ActiveEnemy(27, 32);

	// �E����
	if(glm::length(mPlayer->getPos() - glm::vec3(-60.0f, 0.0f, 350)) < 30) ActiveEnemy(33, 38);

	// ������
	if(glm::length(mPlayer->getPos() - glm::vec3(60.0f, 0.0f, 350)) < 30)	ActiveEnemy(39, 44);

	// ��2�̋��̎�O
	if(mPlayer->getPos().z > 410) ActiveEnemy(45, 46);

	// ��2�̋�����
	if(mPlayer->getPos().z > 560) ActiveEnemy(47, 58);

	// ��2�̋��̍Ō�
	if(mPlayer->getPos().z > 660) ActiveEnemy(59, 62);

	// ���X�g
	if(mPlayer->getPos().z > 800) ActiveEnemy(63, 74);



	// �G�̍X�V
	for(int i = 0; i < mEnemyCount; i++){	
		mEnemys[i].Update();

		// �Q�[���N���A
		if(mEnemys[i].getType() == TYPE::BOSS && mEnemys[i].getHP() <= 0) GameClear = true;
	}

	// �V���b�g�}�l�[�W���[�̍X�V
	mShotManager.Update();
}


// --------------------------------------------------------------
/// �`��
// --------------------------------------------------------------
void EnemyManager::Draw(){
	// �G�̕`��
	for(int i = 0; i < mActiveList.size(); i++){
		mActiveList[i]->Draw();
	}

	// �G�e�̕`��
	mShotManager.Draw();
}


// -------------------------------------------------------------
/// �G��z�u����
/// [in] nom �A�N�e�B�u�ɂ������G�̔z���̔ԍ�
/// [in] type �G�̃^�C�v
/// [in] x,y,z  �ݒu������W
void EnemyManager::SetEnemy(int nom, TYPE type, float x, float y, float z){
	mEnemys[nom].setEnemy(this, mPlayer, type, x, y, z);
}


// --------------------------------------------------------------
/// �����̓G���A�N�e�B�u��
/// [in] beginNom �A�N�e�B�u�ɂ������G�̔z���̔ԍ�(�J�n�ʒu)
/// [in] endNom   �A�N�e�B�u�ɂ������G�̔z���̔ԍ�(�I���ʒu)
void EnemyManager::ActiveEnemy(int beginNom, int endNom){
	for(int i = beginNom; i <= endNom; i++){
		if(!mEnemys[i].getIs() && mEnemys[i].getHP() > 0)mEnemys[i].Active();
	}
}