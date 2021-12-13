#include <string>
#include "../Utility/AsoUtility.h"
#include "../Manager/SceneManager.h"
#include "../Manager/ResourceManager.h"
#include "../Manager/GravityManager.h"
#include "../Manager/Camera.h"
#include "Common/AnimationController.h"
#include "Common/Capsule.h"
#include "Common/Collider.h"
#include "Common/SpeechBalloon.h"
#include "Planet.h"
#include "Player.h"

Player::Player(SceneManager* manager)
{
	mSceneManager = manager;
	mResourceManager = manager->GetResourceManager();
	mGravityManager = manager->GetGravityManager();

	mAnimationController = nullptr;
	mState = STATE::NONE;
}

void Player::Init(void)
{

	// ���f���̊�{�ݒ�
	mTransform.SetModel(mResourceManager->LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	mTransform.scl = AsoUtility::VECTOR_ONE;
	mTransform.pos = { 0.0f, -30.0f, 0.0f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = 
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });
	mTransform.Update();

	// �A�j���[�V�����̐ݒ�
	InitAnimation();

	// TODO:
	ChangeState(STATE::PLAY);
}

void Player::InitAnimation(void)
{

	std::string path = "Data/Model/Player/";
	mAnimationController = new AnimationController(mSceneManager, mTransform.modelId);
	mAnimationController->Add((int)ANIM_TYPE::IDLE, path + "Idle.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::RUN, path + "Run.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::FAST_RUN, path + "FastRun.mv1", 20.0f);
	mAnimationController->Add((int)ANIM_TYPE::JUMP, path + "Jump.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::WARP_PAUSE, path + "WarpPose.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FLY, path + "Flying.mv1", 60.0f);
	mAnimationController->Add((int)ANIM_TYPE::FALLING, path + "Falling.mv1", 80.0f);
	mAnimationController->Add((int)ANIM_TYPE::VICTORY, path + "Victory.mv1", 60.0f);

	mAnimationController->Play((int)ANIM_TYPE::IDLE);

}

void Player::Update(void)
{

	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		UpdatePlay();
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

	mTransform.Update();
	mAnimationController->Update();
	
}

void Player::UpdatePlay(void)
{
	ProcessMove();

	VECTOR vel = VScale(mMoveDir, mSpeed);
	mTransform.pos = VAdd(mTransform.pos, vel);
}

void Player::Draw(void)
{

	// ���f���̕`��
	MV1DrawModel(mTransform.modelId);

	// �f�o�b�O�p�`��
	DrawDebug();

}

void Player::DrawDebug(void)
{

	int white = 0xffffff;
	int black = 0x000000;
	int red = 0xff0000;
	int green = 0x00ff00;
	int blue = 0x0000ff;
	int yellow = 0xffff00;
	int purpl = 0x800080;

	VECTOR v;

	// �L������{���
	//-------------------------------------------------------
	// �L�������W
	v = mTransform.pos;
	DrawFormatString(20, 60, black, "�L�������W �F (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);
	//-------------------------------------------------------

}

void Player::Release(void)
{
}

Transform* Player::GetTransform(void)
{
	return &mTransform;
}

void Player::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Player::STATE::NONE:
		break;
	case Player::STATE::PLAY:
		break;
	case Player::STATE::WARP_RESERVE:
		break;
	case Player::STATE::WARP_MOVE:
		break;
	case Player::STATE::DEAD:
		break;
	case Player::STATE::VICTORY:
		break;
	case Player::STATE::END:
		break;
	}

}

void Player::ProcessMove()
{
	mMoveDir = AsoUtility::VECTOR_ZERO;
	Quaternion cameraRot = mSceneManager->GetCamera()->GetQuaRotOutX();
	if (CheckHitKey(KEY_INPUT_W)) mMoveDir = VAdd(mMoveDir, cameraRot.GetForward());
	if (CheckHitKey(KEY_INPUT_S)) mMoveDir = VAdd(mMoveDir, cameraRot.GetBack());
	if (CheckHitKey(KEY_INPUT_A)) mMoveDir = VAdd(mMoveDir, cameraRot.GetLeft());
	if (CheckHitKey(KEY_INPUT_D)) mMoveDir = VAdd(mMoveDir, cameraRot.GetRight());

	if (!AsoUtility::EqualsVZero(mMoveDir)) {
		bool isLShift = CheckHitKey(KEY_INPUT_LSHIFT);
		mAnimationController->Play(int(isLShift ? ANIM_TYPE::FAST_RUN: ANIM_TYPE::RUN));
		mSpeed = isLShift ? SPEED_RUN : SPEED_MOVE;
		mMoveDir = VNorm(mMoveDir);
		mTransform.quaRot.Mult(mTransform.quaRot.LookRotation(mMoveDir));
	}
	else {
		mAnimationController->Play(int(ANIM_TYPE::IDLE));
	}
}
