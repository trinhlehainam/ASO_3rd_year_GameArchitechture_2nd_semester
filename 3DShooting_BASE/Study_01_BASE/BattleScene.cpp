#include "BattleScene.h"

#include "KeyCheck.h"
#include "SceneManager.h"
#include "RockManager.h"
#include "Camera.h"

#include "PlayerShip.h"
#include "BossShip.h"
#include "SpaceDom.h"

BattleScene::BattleScene(SceneManager* manager):SceneBase(manager)
{
}

void BattleScene::Init(void)
{
	mPlayerShip = new PlayerShip(mSceneManager);
	mPlayerShip->Init();
	mBossShip = new BossShip(mSceneManager, &mPlayerShip->transform);
	mBossShip->Init();
	mSpaceDom = new SpaceDom(mSceneManager, &mPlayerShip->transform);
	mSpaceDom->Init();
	mRockMng = new RockManager(mSceneManager, &mPlayerShip->transform);
	mRockMng->Init();

	auto camera = mSceneManager->GetCamera();
	camera->SetTargetTransform(&mPlayerShip->transform);
	camera->ChangeMode(Camera::MODE::FOLLOW);
}

void BattleScene::Update(void)
{
	auto info = MV1CollCheck_Sphere(
		mBossShip->GetTransform()->modelId, -1,
		mPlayerShip->transform.pos, mPlayerShip->COLLISION_RADIUS
	);

	if (info.HitNum > 0) {
		if (!mPlayerShip->IsDestroy()) {
			mPlayerShip->Destroy();
		}
		else {
			mSceneManager->ChangeScene(SceneManager::SCENE_ID::TITLE, true);
		}
	}
	
	MV1CollResultPolyDimTerminate(info);

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::GAME, true);
	}

	mPlayerShip->Update();
	mBossShip->Update();
	mSpaceDom->Update();
	mRockMng->Update();
}

void BattleScene::Draw(void)
{
	mSpaceDom->Draw();
	mRockMng->Draw();
	mBossShip->Draw();
	mPlayerShip->Draw();
}

void BattleScene::Release(void)
{
	mPlayerShip->Release();
	mBossShip->Release();
	mSpaceDom->Release();
	mRockMng->Release();

	delete mPlayerShip;
	delete mBossShip;
	delete mSpaceDom;
	delete mRockMng;
}
