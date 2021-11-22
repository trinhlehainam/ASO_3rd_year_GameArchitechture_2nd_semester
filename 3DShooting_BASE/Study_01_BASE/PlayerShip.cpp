#include "PlayerShip.h"
#include <algorithm>
#include "AsoUtility.h"
#include "ParticleGenerator.h"
#include "SpriteAnimator.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "SpeechBalloon.h"
#include "PlayerShot.h"

PlayerShip::PlayerShip(SceneManager* manager): mSceneMng(manager)
{
}

void PlayerShip::Init(void)
{
	transform.SetModel(MV1LoadModel("Model/PlayerShip/PlayerShip.mv1"));
	float scale = 3.0f;
	transform.scale = { scale, scale, scale };
	transform.quaRot = Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f),0.0f });
	transform.quaRotLocal = Quaternion();
	transform.pos = { 0.0f,0.0f,0.0f };

	transform.Update();
	mParticleGen = new ParticleGenerator(mSceneMng, VECTOR({ 0.0f, 0.0f, 0.0f }), 20.0f);

	mExplosion = new SpriteAnimator(mSceneMng, ResourceManager::SRC::SHIP_EXPLOSION, 10.0f, 5.0f);

	mSpeechBalloon = new SpeechBalloon(mSceneMng, SpeechBalloon::TYPE::SPEECH, &transform);
	mSpeechBalloon->SetRelativePos({ 0.0f, 5.0f, 5.0f });
	mSpeechBalloon->SetText("Catch me");
	mState = STATE::RUN;

	mShotCooldown = SHOT_INTERVAL;
}

void PlayerShip::Update(void)
{
	switch (mState)
	{
	case PlayerShip::STATE::RUN:
		UpdateRun();
		break;
	case PlayerShip::STATE::EXPLOSE:
		UpdateExplosion();
		break;
	case PlayerShip::STATE::DESTROY:
		UpdateDestroy();
		break;
	default:
		break;
	}

	for (const auto& shot : mShots)
		shot->Update();
	
	if (mShots.size() > 0)
		DeleteShot();
}

void PlayerShip::UpdateRun(void)
{
	ProcessTurn();
	ProcessShot();

	VECTOR dir = transform.GetForward();

	transform.pos = VAdd(transform.pos, VScale(dir, SPEED_MOVE));

	transform.Update();
	mParticleGen->Update();

}

void PlayerShip::UpdateExplosion(void)
{
	mExplosion->Update();
	if (mExplosion->IsEnd()) {
		mState = STATE::DESTROY;
	}
}

void PlayerShip::UpdateDestroy(void)
{
}

void PlayerShip::Draw(void)
{
	switch (mState)
	{
	case PlayerShip::STATE::RUN:
		MV1DrawModel(transform.modelId);
		mParticleGen->Draw();
		break;
	case PlayerShip::STATE::EXPLOSE:
		mExplosion->Draw();
		break;
	default:
		break;
	}
	for (const auto& shot : mShots) {
		shot->Draw();
	}
	DrawSphere3D(transform.pos, COLLISION_RADIUS, 10, 0xffffff, 0xffffff, false);
}

void PlayerShip::Release(void)
{
	MV1DeleteModel(transform.modelId);

	mParticleGen->Release();
	delete mParticleGen;

	mExplosion->Release();
	delete mExplosion;

	mSpeechBalloon->Release();
	delete mSpeechBalloon;
}

void PlayerShip::Destroy()
{
	if (mState == STATE::EXPLOSE) return;
	mState = STATE::EXPLOSE;
	mExplosion->Create(transform.pos);
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

void PlayerShip::ProcessShot(void)
{
	mShotCooldown -= mSceneMng->GetDeltaTime();
	if (mShotCooldown <= 0.0f) {
		mShotCooldown = SHOT_INTERVAL;
		if (CheckHitKey(KEY_INPUT_N)) {
			auto shot = std::make_shared<PlayerShot>(mSceneMng, &transform);
			shot->Create(transform.pos, transform.GetForward());
			mShots.push_back(std::move(shot));
		}
	}
}

void PlayerShip::DeleteShot(void)
{
	//auto deactiveShots = std::remove_if(mShots.begin(), mShots.end(), [](std::shared_ptr<PlayerShot> shot) {
	//	return !shot->IsAlive();
	//	});
	//mShots.erase(deactiveShots);
}

void PlayerShip::Turn(float deg, VECTOR axis)
{
	float rad = AsoUtility::Deg2RadF(deg);
	Quaternion tmpQ = Quaternion::AngleAxis(rad, axis);
	transform.quaRot = transform.quaRot.Mult(tmpQ);
}

bool PlayerShip::IsDestroy() const
{
	return mState == STATE::DESTROY;
}

SpeechBalloon* PlayerShip::GetSpeechBalloon()
{
	return mSpeechBalloon;
}
