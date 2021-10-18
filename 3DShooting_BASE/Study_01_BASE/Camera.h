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

	// �J�����̏������W
	static constexpr VECTOR DEFAULT_CAMERA_POS = { 0.0f, 100.0f, -500.0f };


	// �J�����ʒu�ƒ����_�Ƃ̑��΍��W
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

	// �J�����̈ʒu
	VECTOR mPos;

	// �J�����p�x
	Quaternion mQuaRot;

	// �����_
	VECTOR mTargetPos;

	// �J�����̏����
	VECTOR mCameraUp;

};

