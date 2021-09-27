#pragma once
#include <DxLib.h>

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	VECTOR GetAngle() const;
private:
	VECTOR mPos;
	VECTOR mAngle;
	VECTOR mTargetPos;
	VECTOR mUpVec;

	// Height between camera and plane
	float mHeight;
	float mDistanceToTarget;

	float mFov;
	float mClipNear;
	float mClipFar;
};
