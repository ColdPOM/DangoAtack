#include "Stage.h"


Stage::Stage(void):mTreeCount(15)
{
}


Stage::~Stage(void)
{
	delete[] mTreePos;
}

// --------------------------------------------------------
/// 初期化
// --------------------------------------------------------
void Stage::Init(){
	mGround.Load("floor.pmd", "model/stage");
	mLand.Load("land.pmd", "model/stage");
	mSky.Load("sky.pmd", "model/stage");
	mTree.Load("tree.pmd", "model/stage");

	BossBattle = false;

	// 木の座標指定
	mTreePos = new glm::vec3[mTreeCount];
	mTreePos[0] = glm::vec3(20.0f, 0.0f, 100.0f);
	mTreePos[1] = glm::vec3(30.0f, 0.0f, 110.0f);
	mTreePos[2] = glm::vec3(35.0f, 0.0f, 85.0f);
	mTreePos[3] = glm::vec3(-25.0f, 0.0f, 100.0f);
	mTreePos[4] = glm::vec3(-30.0f, 0.0f, 80.0f);

	mTreePos[5] = glm::vec3(22.0f, 0.0f, 180.0f);

	mTreePos[6] = glm::vec3(-50.0f, 0.0f, 300.0f);
	mTreePos[7] = glm::vec3(-70.0f, 0.0f, 310.0f);
	mTreePos[8] = glm::vec3(-65.0f, 0.0f, 285.0f);
	mTreePos[9] = glm::vec3(55.0f, 0.0f, 300.0f);
	mTreePos[10] = glm::vec3(90.0f, 0.0f, 280.0f);
	mTreePos[11] = glm::vec3(80.0f, 0.0f, 400.0f);
	mTreePos[12] = glm::vec3(85.0f, 0.0f, 350.0f);
	mTreePos[13] = glm::vec3(-75.0f, 0.0f, 350.0f);
	mTreePos[14] = glm::vec3(-45.0f, 0.0f, 380.0f);
}


// --------------------------------------------------------
/// 更新
// --------------------------------------------------------
void Stage::Update(){
	// 空の回転
	mSky.setRotate(mSky.getRotate() + glm::vec3(0.0f, 0.01f, 0.0f));
}


// ---------------------------------------------------------
/// 描画
// ---------------------------------------------------------
void Stage::Draw(){
	mLand.Draw();
	if(!BossBattle)mGround.Draw();
	mSky.Draw();

	for(int i = 0; i < mTreeCount; i++){
		mTree.setPos(mTreePos[i]);
		mTree.Draw();
	}
}