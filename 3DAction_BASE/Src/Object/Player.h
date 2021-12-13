#pragma once
#include <DxLib.h>
#include "Common/Transform.h"
class SceneManager;
class ResourceManager;
class GravityManager;
class AnimationController;
class Capsule;
class Collider;

class Player
{

public:
	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_RUN = 10.0f;
	static constexpr float TIME_ROT = 1.0f;

	// 状態
	enum class STATE
	{
		NONE,
		PLAY,
		WARP_RESERVE,
		WARP_MOVE,
		DEAD,
		VICTORY,
		END
	};

	// アニメーション種別
	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		JUMP,
		WARP_PAUSE,
		FLY,
		FALLING,
		VICTORY
	};

	Player(SceneManager* manager);
	void Init(void);
	void InitAnimation(void);
	void Update(void);
	void UpdatePlay(void);
	void Draw(void);
	void DrawDebug(void);
	void Release(void);

	Transform* GetTransform(void);

	void CalcGravity(void);
	void AddCollider(Collider* collider);
	void ClearCollider(void);

private:

	SceneManager* mSceneManager;
	ResourceManager* mResourceManager;
	GravityManager* mGravityManager;

	Transform mTransform;

	// アニメーション
	AnimationController* mAnimationController;

	// 状態
	STATE mState;

	// Movement
	float mSpeed;
	VECTOR mMoveDir;
	VECTOR mMovePow;

	// Rotation
	Quaternion mPlayerRotY;
	Quaternion mGoalQuaRotY;
	float mStepRotTime;

	//
	VECTOR mJumpPow;
	
	std::vector<Collider*> mColliders;

	VECTOR mGravHitDown;
	VECTOR mGravHitUp;

	// 状態遷移
	void ChangeState(STATE state);

	void ProcessMove(void);

	void SetGoalRotate(double rotRad);
	void Rotate(void);

	void Collision(void);
	void CollisionGravity(void);
};

