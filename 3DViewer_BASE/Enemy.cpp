#include "Enemy.h"
#include "AsoUtility.h"
#include "Unit.h"

Enemy::Enemy(SceneManager* manager, Unit* unit):mSceneMng(manager), mUnit(unit)
{
}

void Enemy::Init(void)
{
	mModelId = MV1LoadModel("Model/Human.mv1");
	mPos = { 200.0f, 0.0f, 400.0f };
	mAngle = { 0.0f, AsoUtility::Deg2RadF(42.0f), 0.0f };
	mAngleLocal = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f };

	mViewRange = 300.0f;
	mViewAngle = AsoUtility::Deg2RadF(60.0f);

	MV1SetPosition(mModelId, mPos);

	VECTOR angle = mAngle;
	angle.x += mAngleLocal.x;
	angle.y += mAngleLocal.y;
	angle.z += mAngleLocal.z;
	MV1SetRotationXYZ(mModelId, angle);
}

void Enemy::Update(void)
{
	mIsNotice = false;

	auto playerPos = mUnit->GetPos();
	auto diff = VSub(playerPos, mPos);
	float distance = VDot(diff, diff);

	if (distance < (mViewRange * mViewRange))
	{
		float rad = atan2f(diff.x, diff.z);
		float diffAngle = rad - mAngle.y;
		float viewDeg = AsoUtility::DegIn360(AsoUtility::Rad2DegF(diffAngle));
		float angle = AsoUtility::DegIn360(AsoUtility::Rad2DegF(mAngle.y));
		if ((viewDeg > 360.0f - 30.0f && viewDeg < 360.0f) || 
			(viewDeg < 30.0f && viewDeg > 0.0f))
			mIsNotice = true;
	}
}

void Enemy::Draw(void)
{
	if (mIsNotice)
		MV1SetMaterialDifColor(mModelId, 0, GetColorF(1.0f, 0.0f, 0.0f, 1.0f));
	else
		MV1SetMaterialDifColor(mModelId, 0, GetColorF(1.0f, 1.0f, 1.0f, 1.0f));

	MV1DrawModel(mModelId);

	float x1 = sinf(mAngle.y);
	float z1 = cosf(mAngle.y);

	VECTOR pos1 = mPos;
	pos1.x += x1 * mViewRange;
	pos1.z += z1 * mViewRange;

	float x2 = sinf(mAngle.y + mViewAngle/2.0f);
	float z2 = cosf(mAngle.y + mViewAngle/2.0f);

	VECTOR pos2 = mPos;
	pos2.x += x2 * mViewRange;
	pos2.z += z2 * mViewRange;

	float x3 = sinf(mAngle.y - mViewAngle/2.0f);
	float z3 = cosf(mAngle.y - mViewAngle/2.0f);

	VECTOR pos3 = mPos;
	pos3.x += x3 * mViewRange;
	pos3.z += z3 * mViewRange;

	VECTOR pos0 = mPos;

	pos0.y = pos1.y = pos2.y = pos3.y = 2.0f;
	DrawTriangle3D(pos0, pos1, pos2, 0xaaaa00, 1);
	DrawTriangle3D(pos0, pos3, pos1, 0xaaaa00, 1);
	
	DrawLine3D(pos0, pos1, 0x000000);
	DrawLine3D(pos0, pos2, 0x000000);
	DrawLine3D(pos0, pos3, 0x000000);
}

void Enemy::Release(void)
{
	MV1DeleteModel(mModelId);
}

VECTOR Enemy::GetPos() const
{
	return mPos;
}

VECTOR Enemy::GetAngle() const
{
	return mAngle;
}
