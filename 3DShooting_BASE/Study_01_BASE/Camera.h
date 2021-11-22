#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"

class SceneManager;
class Transform;

class Camera
{

public:
	enum class MODE {
		NONE,
		FREE,
		FIXED_POINT,
		FOLLOW,
		FOLLOW_STRING,
		SHAKE
	};

	// カメラの初期座標
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };
	
	static constexpr VECTOR RELATIVE_CAMERA_FOLLOW = { 0.0, 25.0F, -80.0F };

	static constexpr VECTOR RELATIVE_CAMERA_SPRING = { 0.0, 25.0F, -80.0F };

	// カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };

	// Camera shake
	static constexpr float TIME_SHAKE = 2.0f;

	static constexpr float WIDTH_SHAKE = 3.0f;

	static constexpr float SPEED_SHAKE = 30.0f;
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixed(void);
	void SetBeforeDrawFollow(void);
	void SetBeforeDrawFollowSrping(void);
	void SetBeforeDrawShake(void);

	void ChangeMode(MODE mode);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

	void SetTargetTransform(Transform* targetTransform);

private:
	MODE mMode;

	SceneManager* mSceneManager;
	Transform* mObjectTransform;

	// カメラの位置
	VECTOR mPos;

	// カメラ角度
	Quaternion mQuaRot;

	// 注視点
	VECTOR mTargetPos;

	// カメラの上方向
	VECTOR mCameraUp;
	
	VECTOR mVelocity;

	// Shake
	float mStepShake;
	VECTOR mDefaultPos;
	VECTOR mShakeDir;
};

