#include "PlayerShip.h"
#include "AsoUtility.h"
#include "ParticleGenerator.h"

PlayerShip::PlayerShip(SceneManager* manager): mSceneMng(manager)
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
	mParticleGen = new ParticleGenerator(mSceneMng, VECTOR({ 0.0f, 0.0f, 0.0f }), 20.0f);
}

void PlayerShip::Update(void)
{
	ProcessTurn();

	VECTOR dir = mTransform.GetForward();

	mTransform.pos = VAdd(mTransform.pos, VScale(dir, SPEED_MOVE));

	mTransform.Update();

	mParticleGen->Update();
}

void PlayerShip::Draw(void)
{
	MV1DrawModel(mTransform.modelId);

	mParticleGen->Draw();
}

void PlayerShip::Release(void)
{
	MV1DeleteModel(mTransform.modelId);

	mParticleGen->Release();
	delete mParticleGen;
}

void PlayerShip::ProcessTurn(void)
{
	if (CheckHitKey(KEY_INPUT_RIGHT))
		Turn(SPEED_ROT_DEG_Y, AsoUtility::AXIS_Y);
	if (CheckHitKey(KEY_INPUT_LEFT))
		Turn(-SPEED_ROT_DEG_Y, AsoUtility::AXIS_Y);
	if (CheckHitKey(KEY_INPUT_UP))
		Turn(-SPEED_ROT_DEG_X, AsoUtility::AXIS_X);
	if (CheckHitKey(KEY_INPUT_DOWN))
		Turn(SPEED_ROT_DEG_X, AsoUtility::AXIS_X);
}

void PlayerShip::Turn(float deg, VECTOR axis)
{
	float rad = AsoUtility::Deg2RadF(deg);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	mTransform.quaRot = mTransform.quaRot.Mult(tmpQ);
}
