#include "Coin.h"
#include "AsoUtility.h"

Coin::Coin(SceneManager* manager):mSceneMng(manager)
{
}

void Coin::Init(void)
{
	mModelId = MV1LoadModel("Model/Coin.mv1");
	mSize = 15.0f;
	mScale = { mSize, mSize, mSize };
	mPos = { 0.0f, 50.0f, 0.0f };
	mAngles = { 0.0f, 0.0f ,0.0f };

	float localRadX = AsoUtility::Deg2RadF(-90.0f);
	float localRadY = AsoUtility::Deg2RadF(180.0f);
	float localRadZ = 0.0f;
	mAnglesLocal = { localRadX, localRadY, localRadZ };

	mMatRotLocal = MGetIdent();
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.x));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.y));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.z));

	Quaternion qx = Quaternion::AngleAxis(localRadX, { 1.0f, 0.0f, 0.0f });
	Quaternion qy = Quaternion::AngleAxis(localRadY, { 0.0f, 1.0f, 0.0f });
	Quaternion qz = Quaternion::AngleAxis(localRadZ, { 0.0f, 0.0f, 1.0f });

	mQuaRotLocal = mQuaRotLocal.Mult(qy);
	mQuaRotLocal = mQuaRotLocal.Mult(qx);
	mQuaRotLocal = mQuaRotLocal.Mult(qz);

	mType = TYPE::QUATERNION;
}

void Coin::Update(void)
{
	mAngles.x = AsoUtility::Deg2RadF(0.0f);
	mAngles.y += AsoUtility::Deg2RadF(1.0f);
	mAngles.z += AsoUtility::Deg2RadF(0.0f);

	switch (mType) {
	case TYPE::VECTOR:
		SetModelVector();
		break;
	case TYPE::MATRIX:
		SetModelMatrix();
		break;
	case TYPE::QUATERNION:
		SetModelQuaternion();
		break;
	}
}

void Coin::Draw(void)
{
	DrawDirection();
	MV1DrawModel(mModelId);
}

void Coin::DrawDirection(void)
{
	MATRIX mat = MGetIdent();

	switch (mType) {
	case TYPE::VECTOR:
		break;
	case TYPE::MATRIX:
		mat = mMatRot;
		break;
	case TYPE::QUATERNION:
		mat = mMatRot;
		break;
	}

	float lineLength = 30.0f;
	VECTOR foward = VNorm(VTransform({ 0.0f, 0.0f, 1.0f }, mat));
	VECTOR baseZ = VAdd(mPos, VScale(foward, lineLength));
	VECTOR targetZ = VAdd(mPos, VScale(foward, -lineLength));

	VECTOR up = VNorm(VTransform({ 0.0f, 1.0f, 0.0f }, mat));
	VECTOR baseY = VAdd(mPos, VScale(up, lineLength));
	VECTOR targetY = VAdd(mPos, VScale(up, -lineLength));

	VECTOR right = VNorm(VTransform({ 1.0f, 0.0f, 0.0f }, mat));
	VECTOR baseX = VAdd(mPos, VScale(right, lineLength));
	VECTOR targetX = VAdd(mPos, VScale(right, -lineLength));

	DrawSphere3D(baseZ, 2.0f, 64, 0x0000ff, 0x0000ff, 1);
	DrawLine3D(baseZ, targetZ, 0x0000ff);
	DrawSphere3D(baseY, 2.0f, 64, 0x00ff00, 0x00ff00, 1);
	DrawLine3D(baseY, targetY, 0x00ff00);
	DrawSphere3D(baseX, 2.0f, 64, 0xff0000, 0xff0000, 1);
	DrawLine3D(baseX, targetX, 0xff0000);
}

void Coin::Release(void)
{
	MV1DeleteModel(mModelId);
}

void Coin::SetModelVector(void)
{
	VECTOR angle = VAdd(mAngles, mAnglesLocal);
	MV1SetRotationXYZ(mModelId, angle);
	MV1SetPosition(mModelId, mPos);
	MV1SetScale(mModelId, mScale);
}

void Coin::SetModelMatrix(void)
{
	mMatRotLocal = MGetIdent();
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.x));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.y));
	mMatRotLocal = MMult(mMatRotLocal, MGetRotX(mAnglesLocal.z));
	
	mMatRot = MGetIdent();
	mMatRot = MMult(mMatRot, mMatRotLocal);
	mMatRot = MMult(mMatRot, MGetRotX(mAngles.x));
	mMatRot = MMult(mMatRot, MGetRotY(mAngles.y));
	mMatRot = MMult(mMatRot, MGetRotZ(mAngles.z));

	mMatTranslate = MGetTranslate(mPos);

	mMatScale = MGetScale(mScale);
	
	MATRIX mat = MGetIdent();
	mat = MMult(mat, mMatScale);
	mat = MMult(mat, mMatRot);
	mat = MMult(mat, mMatTranslate);

	MV1SetMatrix(mModelId, mat);
}

void Coin::SetModelQuaternion(void)
{
	mMatRotLocal = MGetIdent();
	
	// Rotation
	Quaternion tmpQ = Quaternion::Euler(mAngles.x, mAngles.y, mAngles.z);
	mMatRot = tmpQ.ToMatrix();
	tmpQ.Mult(mQuaRotLocal);

	mMatTranslate = MGetTranslate(mPos);

	mMatScale = MGetScale(mScale);
	
	MATRIX mat = MGetIdent();
	mat = MMult(mat, mMatScale);
	mat = MMult(mat, tmpQ.ToMatrix());
	mat = MMult(mat, mMatTranslate);

	MV1SetMatrix(mModelId, mat);
}
