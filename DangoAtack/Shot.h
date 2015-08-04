#pragma once
#include "Common.h"
#include "GameObject.h"
#include "ShotManager.h"
#include "Billboard.h"

class ShotManager;

class Shot
{
private:
	Billboard mBillboad; // 描画する弾
	ShotManager* mShotManager; // 自分を管理するマネージャー
	GameObject* mTarget;     // 目標とするオブジェクト
	const float mLifeTime;   // 生存時間
	float mLifeCount;        // 発射されてからの時間

	glm::vec3 mPos;    // 座標
	float mScale;      // 拡大率

	bool mIs;            // 生存フラグ
	glm::vec3 mFront;    // 前方ベクトル
	glm::vec3 mMoveVec;  // オブジェクトの動きを表すベクトル
	float mSpeed;        // 移動スピード
	bool mVisible;       // 可視
	float mDistance;     // カメラからの距離

public:
	Shot(void);
	~Shot(void);

	void Init(ShotManager* SM);    // 初期化
	void Update();  // 更新
	void Draw(); // 描画

	void Trigger(const glm::vec3 &pos, GameObject* target); // 弾発射
	void Fin(); // 消滅

	// 自身をショットマネージャーのアクティブリストに追加する
	void pushActiveList();

	// 自身をショットマネージャーのアクティブリストから除外する
	void eraseMySelf();

	// ゲッター
	inline glm::vec3 getPos() { return mPos; }		  // ポジションの取得
	inline float getScale() { return mScale; }	      // 拡大率の取得
	inline bool getIs() { return mIs; };			  // 生存フラグの取得			
	inline glm::vec3 getFront() { return mFront; }	   // 前方ベクトルの取得
	inline glm::vec3 getMoveVec() { return mMoveVec; } // 移動ベクトルの取得
	inline bool getVisible() { return mVisible; }    // 可視かどうか取得
	inline float getDistance() { return mDistance; }

	// セッター
	inline void setPos(glm::vec3 pos) { mPos = pos; }	  // ポジションの設定
	inline void setScale(float scale) { mScale = scale; } // 拡大率の設定(XYZ軸ごとの大きさ指定
	inline void setMoveVec(glm::vec3 vec) { mMoveVec = vec; }  // 移動ベクトルを設定
	inline void setVisible(bool visble) { mVisible = visble; } // 可視化
};

