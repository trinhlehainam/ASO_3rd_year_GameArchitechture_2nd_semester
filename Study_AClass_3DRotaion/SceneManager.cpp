#include <chrono>
#include "DxLib.h"
#include "Fader.h"
#include "DemoScene.h"
#include "Camera.h"
#include "SceneManager.h"

void SceneManager::Init()
{

	mSceneID = SCENE_ID::TITLE;
	mWaitSceneID = SCENE_ID::NONE;

	mFader = new Fader();
	mFader->Init();

	mCamera = new Camera(this);
	mCamera->Init();

	mScene = new DemoScene(this);
	mScene->Init();

	mIsSceneChanging = false;

	// �f���^�^�C��
	mTickCount = std::chrono::system_clock::now();

	// 3D�p�̐ݒ�
	Init3D();

}

void SceneManager::Init3D(void)
{

	// Z�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(true);

	// Z�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(true);

	// �o�b�N�J�����O��L���ɂ���
	SetUseBackCulling(true);

	// �N���b�v������ݒ肷��
	SetCameraNearFar(0.0f, 1500.0f);

	// ���C�g�̐ݒ�
	ChangeLightTypeDir({ 0.0f, -1.0f, 0.0f });
	SetUseLighting(false);

	// �w�i�F�ݒ�
	SetBackgroundColor(0, 139, 139);

	// �J�����ݒ�
	// ������Ԃł͎��_�̈ʒu���A 
	// x = 320.0f, y = 240.0f, z = (��ʂ̃T�C�Y�ɂ���ĕω�)
	// �����_�̈ʒu�́A
	// x = 320.0f, y = 240.0f, z = 1.0f�A
	// �J�����̏������
	// x = 0.0f, y = 1.0f, z = 0.0f
	// �܂��ʂ̂w�x���ʏ�̒��S�ɋ��Ăy���̃v���X����������悤�ȃJ�����ɂȂ��Ă��܂��B
	//SetCameraPositionAndAngle(
	//	{ 0.0f, 200, -500.0f },
	//	30.0f * (DX_PI_F / 180.0f), 0.0f, 0.0f
	//);

}

void SceneManager::Update(void)
{

	if (mScene == nullptr)
	{
		return;
	}

	// �f���^�^�C��
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

	// �J�����X�V�X�e�b�v
	mCamera->Update();

	// �`���O���t�B�b�N�̈�̎w��
	// (�R�c�`��Ŏg�p����J�����̐ݒ�Ȃǂ����Z�b�g�����)
	SetDrawScreen(DX_SCREEN_BACK);

	// ��ʂ�������
	ClearDrawScreen();

	// �J�����ݒ�
	mCamera->SetBeforeDraw();

	// �`��
	mScene->Draw();
	mCamera->Draw();

	mFader->Draw();
}

void SceneManager::Release(void)
{

	mScene->Release();
	delete mScene;

	mCamera->Release();
	delete mCamera;

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
	//return mDeltaTime;
	return 0.016f;
}

Camera* SceneManager::GetCamera(void)
{
	return mCamera;
}

void SceneManager::DoChangeScene(void)
{
	mScene->Release();

	mSceneID = mWaitSceneID;

	switch (mSceneID)
	{
	case SCENE_ID::TITLE:
		mScene = new DemoScene(this);
		break;
	default:
		break;
	}

	mScene->Init();

	mWaitSceneID = SCENE_ID::NONE;

}



