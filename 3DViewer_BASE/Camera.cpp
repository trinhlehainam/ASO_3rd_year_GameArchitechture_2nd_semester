#include "Camera.h"
#include "AsoUtility.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	mPos = { 0.0f, 200.0f, -500.0f };
	mTargetPos = { 0.0f ,0.0f, 0.0f };
	mAngle = {
		AsoUtility::Deg2RadF(30.0f), 0.0f, 0.0f
	};
	mUpVec = { 0.0f, 1.0f, 0.0f };
	mClipNear = 0.0f;
	mClipFar = 1500.0f;
	mHeight = 200.0f;
	mDistanceToTarget = 500.0f;

	// Camera
	SetCameraNearFar(mClipNear, mClipFar);

	SetCameraPositionAndAngle(
		mPos, mAngle.x, mAngle.y, mAngle.z
	);
}

void Camera::Update()
{
	SetCameraPositionAndAngle(
		mPos, mAngle.x, mAngle.y, mAngle.z
	);
}

VECTOR Camera::GetAngle() const
{
	return mAngle;
}
