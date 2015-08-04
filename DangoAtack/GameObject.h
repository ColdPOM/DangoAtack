#pragma once
#include "Common.h"
#include "Model.h"

class GameObject
{
protected:
	Model model; // モデルデータ

	glm::vec3 mPos;    // 座標
	glm::vec3 mScale;  // 拡大率
	glm::vec3 mRotate; // 回転率

	bool mIs;            // 生存フラグ
	glm::vec3 mFront;    // 前方ベクトル
	glm::vec3 mMoveVec;  // オブジェクトの動きを表すベクトル
	float mSpeed;        // 移動スピード
	bool mLand;          // 着地フラグ
	bool mVisible;       // 可視

	bool mStopFlag;  // ヒットストップフラグ
	int mStopCount;  // ヒットストップカウント

	bool mIsCol;        // 当たり判定可能かどうか
	int mInvaildCount;  // 無敵時間カウント

public:
	GameObject(void);
	virtual ~GameObject(void);

	virtual void Init();   // 初期化
	virtual void Update(); // 更新
	virtual void Draw();   // 描画

	// ヒットストップ
	/// [in] stopTime ヒットストップの長さ(フレーム数)
	inline void Stop(float stopTime) { mStopFlag = true; mStopCount = stopTime; }

	// 無敵化
	/// [in] invaildTime 無敵時間の長さ(秒)
	inline void InvaildCol(float invaildTime) { mIsCol = false; mInvaildCount = FPS * invaildTime; }

	// ゲッター
	inline glm::vec3 getPos() { return mPos; }		  // ポジションの取得
	inline glm::vec3 getScale() { return mScale; }	  // 拡大率の取得
	inline glm::vec3 getRotate() { return mRotate; }  // 回転率の取得
	inline bool getIs() { return mIs; };			  // 生存フラグの取得			
	inline glm::vec3 getFront() { return mFront; }	   // 前方ベクトルの取得
	inline glm::vec3 getMoveVec() { return mMoveVec; } // 移動ベクトルの取得
	inline bool getIsLand() { return mLand; }          // 地面に居るかどうか判定
	inline glm::vec3 getCenter() { 
		float y = mPos.y + model.getSize().y/2; 
		return glm::vec3(mPos.x, y, mPos.z);}							   // オブジェクトの中心の取得
	inline glm::vec3 getSize() { return model.getSize(); }				   // 拡大率を考慮したモデルの大きさ取得
	inline glm::vec3 getOriginalSize() { return model.getOriginalSize(); } // モデルの元の大きさ取得 
	inline bool IsCol() { return  mIsCol; }								   // 当たり判定が有効かどうか
	inline glm::vec3 getTop() { return mPos + glm::vec3(0.0f, getSize().y, 0.0f); } // オブジェクトの頭座標
	inline bool getVisible() { return mVisible; };                         // 可視かどうか取得

	// セッター
	inline void setPos(glm::vec3 pos) { mPos = pos; }	// ポジションの設定
	inline void setPos(float x, float y, float z) { mPos.x = x; mPos.y = y; mPos.z = z; }	// ポジションの設定
	inline void setScale(float scale) { mScale.x = scale; mScale.y = scale; mScale.z = scale; } // 拡大率の設定(XYZ軸ごとの大きさ指定
	inline void setScale(glm::vec3 scale) { mScale = scale; }  // 拡大率の設定(モデル全体の大きさ)
	inline void setMoveVec(glm::vec3 vec) { mMoveVec = vec; }  // 移動ベクトルを設定
	inline void setRotate(glm::vec3 rot) { mRotate = rot; }
	inline void setLand(bool land) { mLand = land; }
	inline void setVisible(bool visble) { mVisible = visble; }
};

