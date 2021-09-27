#include "Unit.h"

Unit::Unit(SceneManager* manager)
{
	mSceneMng = manager;
}

void Unit::Init(void)
{
	mModelID = MV1LoadModel("Model/Human.mv1");
	mPos = { 0.0f,0.0f, 0.0f };

	MV1SetPosition(mModelID, mPos);
}

void Unit::Update(void)
{
}

void Unit::Draw(void)
{
	MV1DrawModel(mModelID);
}

void Unit::Release(void)
{
	MV1DeleteModel(mModelID);
}
