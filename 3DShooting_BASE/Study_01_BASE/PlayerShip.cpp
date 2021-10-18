#include "PlayerShip.h"
#include "AsoUtility.h"

PlayerShip::PlayerShip(SceneManager* manager)
{
}

void PlayerShip::Init(void)
{
	mTransform.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));
	float scale = 3.0f;
	mTransform.scale = { scale, scale, scale };
	mTransform.quaRot = Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f),0.0f });
	mTransform.quaRotLocal = Quaternion();
	mTransform.pos = { 0.0f,0.0f,0.0f };

	mTransform.Update();
}

void PlayerShip::Update(void)
{
	constexpr float speed = 1.0f;

	VECTOR dir = mTransform.GetForward();

	mTransform.pos = VAdd(mTransform.pos, VScale(dir, speed));

	mTransform.Update();
}

void PlayerShip::Draw(void)
{
	MV1DrawModel(mTransform.modelId);
}

void PlayerShip::Release(void)
{
	MV1DeleteModel(mTransform.modelId);
}
