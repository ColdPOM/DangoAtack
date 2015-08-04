#pragma once
#include "Common.h"
#include "GameObject.h"
#include "Mouse.h"
#include "Sprite2D.h"
#include "Sound.h"

class Player : public GameObject
{
public:
	Player(void);
	~Player(void);

	enum STATE { NEUTRAL, SIT, JUMP, AIM, ATACK}; //　プレイヤーの状態
	enum FACE { NOMAL, SMILE };             //  プレイヤーの表情

	void Init(Mouse *mouse); // 初期化
	void Update();           // 更新
	void Draw();             // 描画

	// アクション
	void Move(const glm::vec2 &mousePos);   // 移動
	void Click();  // 画面がクリックされたときの処理
	void Jump();   // ジャンプ
	void Land();   // 着地
	void Aim(const glm::vec2 &pullVec);    // 攻撃方向さだめ
	void Atack(glm::vec2 pullVec);         // 攻撃
	void Damage(const glm::vec3 &vec);     // ダメージ処理

	// 状態の変更
	inline void ChangeState(STATE state) { mState = state; }

	// ゲッター
	inline int getState() { return mState; }
	inline bool getGameOver() { return GameOver; }

	// ボス戦フラグのセット
	inline void setBossFlag(bool flag) { BossBattle = flag; }



private:
	Mouse* mMouse; // マウスへのハンドル 

	Sound mJumpSE;
	Sound mAtackSE;

	bool BossBattle; // ボス戦フラグ
	bool GameOver;   // ゲームオーバーフラグ

	Sprite2D mHeartTex;  // HP用テクスチャ
	int mHitPoint;       // 敵のHP
	glm::vec3 mKeepVec;  // ブレーキ前の移動ベクトル保持用
	int mKeepTime;       // mKeepVecを保持しておける時間
	glm::vec3 mAimCenter;  // エイム時の回転の中心
	glm::vec3 mRestartPos; // 復活ポイント
	bool mFlash;     // 点滅するかどうか
	int mFlashCount; // 点滅のタイミングカウント
	int mLandCount;  // 復活ポイント取得のタイミングを計るための変数

	bool mScaleMotion;   // モーション時拡大するか縮小するか
	float mMotionSpeed;  // モーション速度

	int mState;      // プレイヤーの状態
	int mFace;       // 表情
};

