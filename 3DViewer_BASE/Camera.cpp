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
	mCameraToPlayer = 500.0f;
	mPlayerToTarget = 300.0f;

	mPos = { 0.0f, mHeight, mCameraToPlayer };
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

		float dirX = sinf(mAngle.y);
		float dirZ = cosf(mAngle.y);

		VECTOR dir = VNorm({ dirX, 0.0f, dirZ });
		VECTOR movePow = VScale(dir, mPlayerToTarget);
		
		movePow.y += mHeight;
		mTargetPos = VAdd(mTargetPos, movePow);
		mTargetPos.y = 0.0f;

		float revRad = AsoUtility::Deg2RadF(180.0f);
		dirX = sinf(mAngle.y + revRad);
		dirZ = cosf(mAngle.y + revRad);

		dir = VNorm({ dirX, 0.0f, dirZ });
		movePow = VScale(dir, mCameraToPlayer);
		
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

VECTOR Camera::GetPos() const
{
	return mPos;
}

VECTOR Camera::GetAngle() const
{
	return mAngle;
}

VECTOR Camera::GetTargetPos() const
{
	return VECTOR();
}
