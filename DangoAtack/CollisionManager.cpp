#include "CollisionManager.h"


CollisionManager::CollisionManager(void)
{
	mHitSE.LoadSE("sound/hit.wav");
}


CollisionManager::~CollisionManager(void)
{
}


// -----------------------------------------------------------------------------
/// �v���C���[�ƓG�̓����蔻��
/// [in] player �v���C���[�I�u�W�F�N�g�ւ̎Q��
/// [in] EM �G�z��ւ̎Q��
// -----------------------------------------------------------------------------
void CollisionManager::PlayerVSEnemy(Player &player, EnemyManager &EM){
	if(player.getGameOver()) return;
	std::vector<Enemy*>* enemys = EM.getActiveList();

	for(int i = 0; i < EM.getActiveList()->size(); i++){
		if(enemys->at(i)->IsCol() && 
			Collision::HitSphere(player.getCenter(), player.getSize().x/2, enemys->at(i)->getCenter(), enemys->at(i)->getSize().x/2)){
			
			// �G�̍U���̕����D���Ȏ�
			if(player.IsCol() && enemys->at(i)->getIsBarrier()){
				player.Damage(enemys->at(i)->getFront());
				continue;
			}

			// �A�^�b�N�q�b�g��
			else if(player.getState() == Player::STATE::ATACK && glm::length(player.getMoveVec()) >= 0.2){
				enemys->at(i)->Damage();

				// �q�b�g�X�g�b�v
				float stopTime = glm::length(player.getMoveVec()) * 7; // �A�^�b�N���������X�g�b�v���Ԃ������B
				enemys->at(i)->Stop(stopTime);
				player.Stop(stopTime);
				mHitSE.PlaySE();
			}

			// �����o��
			else {
				// �G���猩���v���C���[�̕���
				glm::vec3 vec = glm::normalize(player.getPos() - enemys->at(i)->getPos());
				player.setMoveVec(glm::vec3(vec.x, player.getMoveVec().y+0.15f, vec.z) * 0.5f);
			}
		}
	}
}

// ------------------------------------------------------------------------------
/// �G�ƓG�̓����蔻��
/// [in] EM �G�z��ւ̎Q��
// ------------------------------------------------------------------------------
void CollisionManager::EnemyVSEnemy(EnemyManager &EM){
	std::vector<Enemy*>* enemys = EM.getActiveList();

	for(int i = 0; i < EM.getActiveList()->size() -1; i++){
		for(int j = i + 1; j < EM.getActiveList()->size(); j++){
			// ���ݒׂ��̏㏸���͓����蔻����s��Ȃ�
			if(enemys->at(i)->getState() == Enemy::STATE::ATACK && enemys->at(j)->getState() == Enemy::STATE::ATACK &&
				!enemys->at(i)->getIsLand() && !enemys->at(j)->getIsLand()) continue;
			if(Collision::HitSphere(enemys->at(i)->getCenter(), enemys->at(i)->getOriginalSize().x/2, enemys->at(j)->getCenter(), enemys->at(j)->getOriginalSize().x/2)){
				// �Gj����Gi�̕���
				glm::vec3 vec = glm::normalize(enemys->at(i)->getPos() - enemys->at(j)->getPos());
				// �G�I�u�W�F�N�g�̔��a�̍��v
				float r = enemys->at(i)->getOriginalSize().x / 2 + enemys->at(j)->getOriginalSize().x / 2;
				// �Gi�̍��W���L�^
				glm::vec3 pos1 = enemys->at(i)->getPos();
				enemys->at(i)->setPos(enemys->at(j)->getPos() + vec*r);
				enemys->at(j)->setPos(pos1 - vec*r);
				
			}
		}
	}
}


// -------------------------------------------------------------------------------
/// �v���C���[�ƃX�e�[�W�̓����蔻��
// -------------------------------------------------------------------------------
void CollisionManager::PlayerVSStage(Player &player, Stage &stage){
	// �{�X�펞�̏�����
	bool land = false; // ���n�t���O
	for(int i = 0; i < stage.getLand()->getPolygonCount(); i++){
		// �ǂƂ̔���
		if(BossBattle && Collision::HitSphereVSPolygon(player.getCenter(), player.getSize().x/2, stage.getLand()->getPolygons()[i]) &&
				glm::dot(stage.getLand()->getPolygons()[i].normal, glm::vec3(0.0f, 1.0f, 0.0f)) <= 0.1f){
			// �߂荞�݋
			float f = player.getSize().x/2 - glm::abs(glm::dot(stage.getLand()->getPolygons()[i].normal, player.getCenter() - stage.getLand()->getPolygons()[i].vertex[0]));
			player.setPos(player.getPos() + stage.getLand()->getPolygons()[i].normal * f);
		}

		// ���Ƃ̔���
		if(Collision::HitLineVSPolygon(player.getPos(), player.getTop(), stage.getLand()->getPolygons()[i])){
			player.setPos(Collision::CrossPoint(player.getPos(), player.getTop(), stage.getLand()->getPolygons()[i]));
			player.Land();
			land = true;
		}
	}
	if(BossBattle) {
		player.setLand(land);
		return;
	}


	// �؂Ƃ̓����蔻��
	for(int i = 0; i < stage.getTreeCount(); i++){
		if(Collision::HitCylinder(player.getPos(), player.getSize().x/2, player.getSize().y, stage.getTreePos()[i], 1.0f, stage.getTreeHeight())){
			
			// ������������
			if(glm::length(player.getMoveVec()) >= 0.9f){
				player.ChangeState(Player::STATE::JUMP);
				glm::vec3 vec = glm::normalize(-player.getMoveVec()); // ���˕Ԃ����
 				player.setLand(false);
				player.setPos(player.getPos() -player.getMoveVec() + glm::vec3(0.0f, 0.1f, 0.0f));
				player.setRotate(glm::vec3(20.0f, player.getRotate().y, player.getRotate().z));
				player.setScale(1.0f);
				player.setMoveVec(glm::vec3(vec.x*0.1f, 0.2f, vec.z*0.1f));
			}
			
			else{
				// �߂荞�݋
				float f = player.getSize().x/2 + 1.0f - glm::length(player.getPos() - stage.getTreePos()[i]);
				player.setPos(player.getPos() + glm::normalize(player.getPos() - stage.getTreePos()[i]) * f);
			}
		}
	}

	for(int i = 0; i < stage.getGround()->getPolygonCount(); i++){
		// �ǂƂ̔���
		if(Collision::HitSphereVSPolygon(player.getCenter(), player.getSize().x/2, stage.getGround()->getPolygons()[i]) &&
				glm::dot(stage.getGround()->getPolygons()[i].normal, glm::vec3(0.0f, 1.0f, 0.0f)) <= 0.1f){
			// �߂荞�݋
			float f = player.getSize().x/2 - glm::abs(glm::dot(stage.getGround()->getPolygons()[i].normal, player.getCenter() - stage.getGround()->getPolygons()[i].vertex[0]));
			player.setPos(player.getPos() + stage.getGround()->getPolygons()[i].normal * f);
		}

		// ���Ƃ̔���
		if(Collision::HitLineVSPolygon(player.getPos(), player.getTop(), stage.getGround()->getPolygons()[i])){
			player.setPos(Collision::CrossPoint(player.getPos(), player.getTop(), stage.getGround()->getPolygons()[i]));
			player.Land();

			land = true;
		}
	}
	player.setLand(land);
}


// -------------------------------------------------------------------------------
/// �G�ƃX�e�[�W�̓����蔻��
void CollisionManager::EnemysVSStage(EnemyManager &EM, Stage &stage){
	std::vector<Enemy*>* enemys = EM.getActiveList();

	for(int i = 0; i < EM.getActiveList()->size(); i++){
		bool land = false;
		// -- �{�X�펞 --
		for(int j = 0; j < stage.getLand()->getPolygonCount(); j++){
			if(Collision::HitLineVSPolygon(enemys->at(i)->getPos(), enemys->at(i)->getTop(), stage.getLand()->getPolygons()[j])){
				enemys->at(i)->setPos(Collision::CrossPoint(enemys->at(i)->getPos(), enemys->at(i)->getTop(), stage.getLand()->getPolygons()[j]));
				enemys->at(i)->Land();

				land = true;
			}
		}
		if(BossBattle){
			enemys->at(i)->setLand(land);
			continue;
		}
		

		// -- �ʏ펞 --
		// �؂Ƃ̓����蔻��
		for(int j = 0; j < stage.getTreeCount(); j++){
			if(Collision::HitCylinder(enemys->at(i)->getPos(), enemys->at(i)->getSize().x/2, enemys->at(i)->getSize().y, stage.getTreePos()[j], 1.0f, stage.getTreeHeight())){
				float f = enemys->at(i)->getSize().x/2 + 1.0f - glm::length(enemys->at(i)->getPos() - stage.getTreePos()[j]);
				enemys->at(i)->setPos(enemys->at(i)->getPos() + glm::normalize(enemys->at(i)->getPos() - stage.getTreePos()[j]) * f);
			
			}
		}
		
		// ���Ƃ̓����蔻��
		for(int j = 0; j < stage.getGround()->getPolygonCount(); j++){
			if(Collision::HitLineVSPolygon(enemys->at(i)->getPos(), enemys->at(i)->getTop(), stage.getGround()->getPolygons()[j])){
				enemys->at(i)->setPos(Collision::CrossPoint(enemys->at(i)->getPos(), enemys->at(i)->getTop(), stage.getGround()->getPolygons()[j]));
				enemys->at(i)->Land();

				land = true;
			}
		}
		enemys->at(i)->setLand(land);
	}
}


// -------------------------------------------------------------------------------------
/// �e�ƃv���C���[�̓����蔻��
// [in] player �v���C���[�ւ̎Q��
// [in] SM �V���b�g�}�l�[�W���[�̃n���h��
void CollisionManager::PlayerVSShot(Player &player, ShotManager* SM){
	if(SM->getActiveList().empty()) return;  // ������݂��Ă��Ȃ���Ώ��������Ȃ�

	Shot* shots = SM->getActiveList().front();

	for(int i = 0; i < SM->getActiveList().size(); i++){
		if(Collision::HitSphere(player.getCenter(), player.getSize().x/2, shots[i].getPos(), 0.3f)){
			
			if(player.IsCol())player.Damage(shots[i].getFront());
			shots[i].Fin();
			break;
		}
	}
}