#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Camera.h"
#include "DemoScene.h"

DemoScene::DemoScene(SceneManager* manager) : SceneBase(manager)
{
}

void DemoScene::Init(void)
{

}

void DemoScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

}

void DemoScene::Draw(void)
{
}

void DemoScene::Release(void)
{
}
