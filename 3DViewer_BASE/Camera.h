#pragma once
#include <DxLib.h>
class Unit;

class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();

	void SetUnit(Unit* unit);

	VECTOR GetAngle() const;
	VECTOR GetTargetPos() const;
private:
	Unit* mUnit;

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
