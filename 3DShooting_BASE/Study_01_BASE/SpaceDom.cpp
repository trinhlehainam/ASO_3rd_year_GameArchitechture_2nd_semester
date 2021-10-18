#include "SpaceDom.h"
#include "AsoUtility.h"

SpaceDom::SpaceDom(SceneManager* manager, Transform* playerTransform):
	mSceneMng(manager),
	mPlayerTranform(playerTransform)
{
}

void SpaceDom::Init(void)
{
	mTransform.SetModel(MV1LoadModel("Model/SkyDome/SkyDome.mv1"));
	float scale = 1.0f;
	mTransform.scale = { scale, scale, scale };
	mTransform.quaRot = Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f),0.0f });
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = { 0.0f,0.0f,0.0f };

	mTransform.Update();
}

void SpaceDom::Update(void)
{
	mTransform.pos = mPlayerTranform->pos;
}

void SpaceDom::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void SpaceDom::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
}

void SpaceDom::ChangeStage(STATE state)
{
}
