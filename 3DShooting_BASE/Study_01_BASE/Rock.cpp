#include "Rock.h"
#include "AsoUtility.h"

Rock::Rock(void)
{
}

void Rock::Init(int modelID, VECTOR pos, VECTOR angle, VECTOR scale)
{
	mTransform.SetModel(modeilID);
	mTransform.pos = pos;
	mTransform.quaRot = Quaternion::Euler(angle);
	mTransform.quaRotLocal = Quaternion();
	mTransform.scale = scale;
	mTransform.Update();
}

void Rock::Update(void)
{
}

void Rock::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void Rock::Release(void)
{
}
