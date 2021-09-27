#include <chrono>
#include "DxLib.h"
#include "Fader.h"
#include "TitleScene.h"
#include "Camera.h"
#include "MiniCamera.h"
#include "AsoUtility.h"
#include "SceneManager.h"

void SceneManager::Init()
{

	mSceneID = SCENE_ID::TITLE;
	mWaitSceneID = SCENE_ID::NONE;

	mFader = new Fader();
	mFader->Init();

	mScene = new TitleScene(this);
	mScene->Init();

	mCamera = new Camera();

	mMiniCamera = new MiniCamera(mCamera);
	mMiniCamera->Init();

	mIsSceneChanging = false;

	// デルタタイム
	mTickCount = std::chrono::system_clock::now();
	
	Init3D();
}

void SceneManager::Init3D(void)
{
	// ZBuffer
	SetUseZBuffer3D(true);

	// ZBuffer
	SetWriteZBuffer3D(true);

	// BackCulling
	SetUseBackCulling(true);

	// Camera
	SetCameraNearFar(0.0f, 1500.0f);

	// Light
	ChangeLightTypeDir({0.3f, -0.7f, 0.8f});

	// Background
	SetBackgroundColor(0, 139, 139);
}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// デルタタイム
	auto tickCount = std::chrono::system_clock::now();
	mDeltaTime = std::chrono::duration_cast<std::chrono::nanoseconds>(tickCount - mTickCount).count() / 1000000000.0f;
	mTickCount = tickCount;

	mFader->Update();
	if (mIsSceneChanging)
	{
		Fader::FADE_STATE fState = mFader->GetState();
		switch (fState)
		{
		case Fader::FADE_STATE::FADE_IN:
			if (mFader->IsEnd())
			{
				mFader->SetFade(Fader::FADE_STATE::NONE);
				mIsSceneChanging = false;
			}
			break;
		case Fader::FADE_STATE::FADE_OUT:
			if (mFader->IsEnd())
			{
				DoChangeScene();
				mFader->SetFade(Fader::FADE_STATE::FADE_IN);
			}
			break;
		default:
			break;
		}
	}
	else 
	{
		mScene->Update();
	}

	// ミニカメラ
	mMiniCamera->Update();
	mMiniCamera->DrawScreen();

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// Camera Set up
	VECTOR cameraPos = { 0.0f, 200.0f, -500.0f };
	VECTOR cameraAngle = {
		AsoUtility::Deg2RadF(30.0f), 0.0f, 0.0f
	};

	SetCameraPositionAndAngle(
		cameraPos, cameraAngle.x, cameraAngle.y, cameraAngle.z
	);

	// 画面を初期化
	ClearDrawScreen();

	// 描画
	mScene->Draw();

	// ミニカメラ
	//mMiniCamera->Draw();

	mFader->Draw();

}

void SceneManager::Release(void)
{

	mScene->Release();
	delete mScene;

}

void SceneManager::ChangeScene(SCENE_ID nextId, bool isFading)
{
	mWaitSceneID = nextId;

	if (isFading)
	{
		mFader->SetFade(Fader::FADE_STATE::FADE_OUT);
		mIsSceneChanging = true;
	}
	else 
	{
		DoChangeScene();
	}

}

float SceneManager::GetDeltaTime(void)
{
	return mDeltaTime;
}

void SceneManager::DoChangeScene(void)
{
	mScene->Release();

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new TitleScene(this);
		break;
	default:
		break;
	}

	mScene->Init();

	mWaitSceneID = SCENE_ID::NONE;

}
