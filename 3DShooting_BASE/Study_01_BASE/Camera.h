#pragma once
#include <vector>
#include "DxLib.h"
#include "Quaternion.h"
class SceneManager;

class Camera
{

public:
	enum class MODE {
		NONE,
		FREE,
		FIXED_POINT
	};

	// カメラの初期座標
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };


	// カメラ位置と注視点との相対座標
	static constexpr VECTOR RELATIVE_TARGET_POS = { 0.0f, -100.0f, 500.0f };
	
	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void SetDefault(void);

	void Update(void);

	void SetBeforeDraw(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFixed(void);

	void ChangeMode(MODE mode);

	void Draw(void);
	void DrawDebug(void);
	void DrawUI(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetTargetPos(void);
	VECTOR GetDir(void);

private:
	MODE mMode;

	SceneManager* mSceneManager;

	// カメラの位置
	VECTOR mPos;

	// カメラ角度
	Quaternion mQuaRot;

	// 注視点
	VECTOR mTargetPos;

	// カメラの上方向
	VECTOR mCameraUp;

};

