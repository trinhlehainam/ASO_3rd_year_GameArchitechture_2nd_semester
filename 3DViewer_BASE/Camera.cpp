#include "Camera.h"
#include "AsoUtility.h"
#include "Unit.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	mHeight = 200.0f;
	mDistanceToTarget = 500.0f;

	mPos = { 0.0f, mHeight, mDistanceToTarget };
	mTargetPos = { 0.0f ,0.0f, 0.0f };
	mAngle = {
		AsoUtility::Deg2RadF(30.0f), 0.0f, 0.0f
	};
	mUpVec = { 0.0f, 1.0f, 0.0f };
	mClipNear = 0.0f;
	mClipFar = 1500.0f;

	// Camera
	SetCameraNearFar(mClipNear, mClipFar);
	
	if (mUnit == nullptr)
	{
		SetCameraPositionAndAngle(
			mPos, mAngle.x, mAngle.y, mAngle.z
		);
	}
	else
	{
		mTargetPos = mUnit->GetPos();
		SetCameraPositionAndTargetAndUpVec(
			mPos,
			mTargetPos,
			mUpVec
		);
	}
}

void Camera::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		mAngle.y += AsoUtility::Deg2RadF(-1.0f);
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		mAngle.y += AsoUtility::Deg2RadF(1.0f);
	}

	if (mUnit == nullptr)
	{
		SetCameraPositionAndAngle(
			mPos, mAngle.x, mAngle.y, mAngle.z
		);
	}
	else
	{
		mTargetPos = mUnit->GetPos();

		float revRad = AsoUtility::Deg2RadF(180.0f);
		float dirX = sinf(mAngle.y + revRad);
		float dirZ = cosf(mAngle.y + revRad);

		VECTOR dir = VNorm({ dirX, 0.0f, dirZ });
		VECTOR movePow = VScale(dir, mDistanceToTarget);
		
		movePow.y += mHeight;
		mPos = VAdd(mTargetPos, movePow);

		SetCameraPositionAndTargetAndUpVec(
			mPos,
			mTargetPos,
			mUpVec
		);
	}
}

void Camera::SetUnit(Unit* unit)
{
	mUnit = unit;
}

VECTOR Camera::GetAngle() const
{
	return mAngle;
}

VECTOR Camera::GetTargetPos() const
{
	return VECTOR();
}
