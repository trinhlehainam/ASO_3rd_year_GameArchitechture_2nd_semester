#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "Stage.h"
#include "SpaceDom.h"
#include "PlayerShip.h"
#include "RockManager.h"

GameScene::GameScene(SceneManager* manager) :
	SceneBase(manager),
	mStage(std::make_shared<Stage>(mSceneManager)),
	mPlayerShip(std::make_shared<PlayerShip>(mSceneManager)),
	mSpaceDom(std::make_shared<SpaceDom>(mSceneManager, &mPlayerShip->transform)),
	mRockMng(std::make_shared<RockManager>(mSceneManager, &mPlayerShip->transform))
{
}

void GameScene::Init(void)
{
	mStage->Init();
	mSpaceDom->Init();
	mPlayerShip->Init();
	mRockMng->Init();

	auto camera = mSceneManager->GetCamera();
	camera->SetTargetTransform(&mPlayerShip->transform);
	camera->ChangeMode(Camera::MODE::FOLLOW);
}

void GameScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}

	auto info = MV1CollCheck_Sphere(
		mStage->GetModelDungeonID(), -1,
		mPlayerShip->transform.pos, mPlayerShip->COLLISION_RADIUS
	);

	if (info.HitNum > 0) {
		if (!mPlayerShip->IsDestroy()) {
			mPlayerShip->Destroy();
		}
		else {
			
		}
	}
	
	mStage->Update();
	mSpaceDom->Update();
	mPlayerShip->Update();
	mRockMng->Update();
}

void GameScene::Draw(void)
{
	mStage->DrawGrid();
	mSpaceDom->Draw();
	mStage->Draw();
	mPlayerShip->Draw();
	mRockMng->Draw();
}

void GameScene::Release(void)
{
	mStage->Release();
	mSpaceDom->Release();
	mPlayerShip->Release();
	mRockMng->Release();
}
