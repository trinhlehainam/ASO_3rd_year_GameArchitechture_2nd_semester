#include "BossShip.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "Transform.h"
#include "AsoUtility.h"
#include "EventShot.h"
#include "Camera.h"
#include "Turret.h"

BossShip::BossShip(SceneManager* manager, Transform* player):mSceneMng(manager), mPlayer(player)
{
}

void BossShip::Init(void)
{
	mTransform = new Transform(MV1LoadModel("Model/BossShip/BossShip.mv1"));
	mTransform->pos = { 0.0f, 0.0f, 4000.0f };
	mTransform->scale = { 2.0f, 2.0f, 2.0f };
	mTransform->quaRot = Quaternion::Euler({
		AsoUtility::Deg2RadF(20.0f),
		AsoUtility::Deg2RadF(210.0f),
		AsoUtility::Deg2RadF(20.0f)
		}
	);
	mTransform->quaRotLocal = Quaternion::Euler({
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
		}
	);

	mTransform->Update();
	mEventShot = new EventShot(mSceneMng, mTransform);
	SceneManager::SCENE_ID id = mSceneMng->GetmSceneID();

	switch (id)
	{
	case SceneManager::SCENE_ID::EVENT:
		mState = STATE::EVENT;
		break;
	case SceneManager::SCENE_ID::BATTLE:
		MV1SetupCollInfo(mTransform->modelId);
		mState = STATE::BATTLE;
		break;
	default:
		break;
	}
	// ‘O•û
	MakeTurret(
		{ 4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(-18.0f) });
	MakeTurret(
		{ -4.5f, 5.5f, 7.8f },
		{ 0.0f, 0.0f, AsoUtility::Deg2RadF(18.0f) });

	// ‰¡
	MakeTurret(
		{ 4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(90.0f), 0.0f });
	MakeTurret(
		{ -4.5f, 5.5f, 0.0f },
		{ AsoUtility::Deg2RadF(20.0f), AsoUtility::Deg2RadF(-90.0f), 0.0f });

	// Œã•û
	MakeTurret(
		{ 3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(18.0f) });
	MakeTurret(
		{ -3.5f, 5.0f, -17.8f },
		{ 0.0f, AsoUtility::Deg2RadF(180.0f), AsoUtility::Deg2RadF(-18.0f) });
}

void BossShip::Update(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
	{
		VECTOR dir = mTransform->GetForward();
		mTransform->pos = VAdd(mTransform->pos, VScale(dir, SPEED_MOVE));
		mEventShot->Update();

		if (!mEventShot->IsAlive()) {
			mStepEvent -= mSceneMng->GetDeltaTime();
			if (mStepEvent < 0.0f)
			{
				mSceneMng->ChangeScene(SceneManager::SCENE_ID::BATTLE, true);
			}
		}

		UpdateTurret();
	}
		break;
	case BossShip::STATE::BATTLE:
	{
		VECTOR dir = mTransform->GetForward();
		mTransform->pos = VAdd(mTransform->pos, VScale(dir, SPEED_MOVE));

		float speed = 0.05f * mSceneMng->GetDeltaTime();
		Quaternion axis = Quaternion::AngleAxis(speed, AsoUtility::AXIS_Y);
		mTransform->quaRot = mTransform->quaRot.Mult(axis);

		// Update Collider
		MV1RefreshCollInfo(mTransform->modelId);

		UpdateTurret();
	}
		break;
	case BossShip::STATE::DESTROY:
		break;
	case BossShip::STATE::END:
		break;
	default:
		break;
	}

	mTransform->Update();
}

void BossShip::UpdateTurret(void)
{
	for (auto turret : mTurrets)
		turret->Update();
}

void BossShip::Draw(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
		MV1DrawModel(mTransform->modelId);
		mEventShot->Draw();
		DrawTurret();
		break;
	case BossShip::STATE::BATTLE:
		MV1DrawModel(mTransform->modelId);
		DrawTurret();
		break;
	case BossShip::STATE::DESTROY:
		break;
	case BossShip::STATE::END:
		break;
	default:
		break;
	}
}

void BossShip::DrawTurret(void)
{
	for (auto turret : mTurrets)
		turret->Draw();
}

void BossShip::Release(void)
{
	MV1DeleteModel(mTransform->modelId);

	mEventShot->Release();
	delete mEventShot;

	for (auto turret : mTurrets) {
		turret->Release();
		delete turret;
	}

	mTurrets.clear();
}

Transform* BossShip::GetTransform()
{
	return mTransform;
}

void BossShip::ChangeState(STATE state)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
	{
		mStepEvent = TIME_EVENT;
		mEventShot = new EventShot(mSceneMng, mTransform);

		VECTOR dir = VNorm(VSub(mSceneMng->GetCamera()->GetPos(), mTransform->pos));
		mEventShot->Create(mTransform->pos, dir);

	}
		break;
	case BossShip::STATE::BATTLE:
		break;
	case BossShip::STATE::DESTROY:
		break;
	case BossShip::STATE::END:
		break;
	default:
		break;
	}
}

void BossShip::MakeTurret(VECTOR localPos, VECTOR localAddAxis)
{
	Turret* turret = new Turret(mSceneMng, mPlayer, mTransform, localPos, localAddAxis);
	mTurrets.push_back(turret);
}
