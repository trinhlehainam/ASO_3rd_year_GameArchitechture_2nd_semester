#include "BossShip.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "Transform.h"
#include "AsoUtility.h"
#include "EventShot.h"
#include "Camera.h"

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
	mTransform->quaRot = Quaternion::Euler({
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
		mState = STATE::BATTLE;
		break;
	default:
		break;
	}
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
	}
		break;
	case BossShip::STATE::BATTLE:
	{
		VECTOR dir = mTransform->GetForward();
		mTransform->pos = VAdd(mTransform->pos, VScale(dir, SPEED_MOVE));
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

void BossShip::Draw(void)
{
	switch (mState)
	{
	case BossShip::STATE::EVENT:
		MV1DrawModel(mTransform->modelId);
		mEventShot->Draw();
		break;
	case BossShip::STATE::BATTLE:
		MV1DrawModel(mTransform->modelId);
		break;
	case BossShip::STATE::DESTROY:
		break;
	case BossShip::STATE::END:
		break;
	default:
		break;
	}
}

void BossShip::Release(void)
{
	MV1DeleteModel(mTransform->modelId);

	mEventShot->Release();
	delete mEventShot;
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
