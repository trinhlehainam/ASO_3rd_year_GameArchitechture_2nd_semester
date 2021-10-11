#include "Unit.h"
#include "SceneManager.h"
#include "AsoUtility.h"
#include "Camera.h"

Unit::Unit(SceneManager* manager)
{
	mSceneMng = manager;
}

void Unit::Init(void)
{
	mModelId = MV1LoadModel("Model/Human.mv1");
	mPos = { 0.0f,0.0f, 0.0f };
	mAngle = { 0.0f, 0.0f, 0.0f };
	mAngleLocal = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f };
	mRotateSpeed = 5.0f; 

	MV1SetPosition(mModelId, mPos);

	VECTOR angle = mAngle;
	angle.x += mAngleLocal.x;
	angle.y += mAngleLocal.y;
	angle.z += mAngleLocal.z;
	MV1SetRotationXYZ(mModelId, angle);

	mAnimWalk = MV1AttachAnim(mModelId, 1);

	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModelId, mAnimWalk);
	mStepAnim = 0.0f;
	mAnimSpeed = 20.0f;

	MV1SetAttachAnimTime(mModelId, mAnimWalk, mStepAnim);
}

void Unit::Update(void)
{
	float deltaTime = mSceneMng->GetDeltaTime();

	mStepAnim += mAnimSpeed * deltaTime;
	if (mStepAnim > mTimeTotalAnimWalk)
		mStepAnim = 0.0f;
	MV1SetAttachAnimTime(mModelId, mAnimWalk, mStepAnim);

	bool isHitMove = false;
	float rotRad = 0.0f;
	float moveSpeed = 100.0f;

	if (CheckHitKey(KEY_INPUT_D))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(90.0f);
	}

	if (CheckHitKey(KEY_INPUT_A))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(-90.0f);
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(0.0f);
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2RadF(180.0f);
	}

	if (isHitMove)
	{
		auto camera = mSceneMng->GetCamera();
		auto cameraAngle = camera->GetAngle();

		mPos.x += sinf(cameraAngle.y + rotRad) * deltaTime * moveSpeed;
		mPos.z += cosf(cameraAngle.y + rotRad) * deltaTime * moveSpeed;

		const float kRotaSpeed_rad = AsoUtility::Deg2RadF(mRotateSpeed);
		float radUnitAngleY = mAngle.y;
		float radMoveAngleY = cameraAngle.y + rotRad;
		radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);

		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);
		float diff = radMoveAngleY - radUnitAngleY;

		if (abs(diff) <= kRotaSpeed_rad + 0.01f)
			mAngle.y = radMoveAngleY;
		else
			mAngle.y += aroundDir * kRotaSpeed_rad;

		mAngle.y = AsoUtility::RadIn2PI(mAngle.y);
	}

	VECTOR angle = mAngle;
	angle.x += mAngleLocal.x;
	angle.y += mAngleLocal.y;
	angle.z += mAngleLocal.z;
	MV1SetRotationXYZ(mModelId, angle);

	MV1SetPosition(mModelId, mPos);
}

void Unit::Draw(void)
{
	MV1DrawModel(mModelId);
}

void Unit::Release(void)
{
	MV1DeleteModel(mModelId);
}

VECTOR Unit::GetPos() const
{
	return mPos;
}

VECTOR Unit::GetAngle() const
{
	return mAngle;
}
