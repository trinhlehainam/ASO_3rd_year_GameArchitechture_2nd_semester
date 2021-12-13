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

	// モデルの基本設定
	mTransform.SetModel(mResourceManager->LoadModelDuplicate(
		ResourceManager::SRC::PLAYER));
	mTransform.scl = AsoUtility::VECTOR_ONE;
	mTransform.pos = { 0.0f, -30.0f, 0.0f };
	mTransform.quaRot = Quaternion();
	mTransform.quaRotLocal = 
		Quaternion::Euler({ 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f });
	mTransform.Update();

	// アニメーションの設定
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

	CalcGravity();

	Collision();

	Rotate();
	mTransform.quaRot = mGravityManager->GetTransform()->quaRot;
	mTransform.quaRot = mTransform.quaRot.Mult(mPlayerRotY);
}

void Player::Draw(void)
{

	// モデルの描画
	MV1DrawModel(mTransform.modelId);

	// デバッグ用描画
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

	// キャラ基本情報
	//-------------------------------------------------------
	// キャラ座標
	v = mTransform.pos;
	DrawFormatString(20, 60, black, "キャラ座標 ： (%0.2f, %0.2f, %0.2f)",
		v.x, v.y, v.z
	);
	//-------------------------------------------------------
	DrawLine3D(mGravHitUp, mGravHitDown, 0x000000);

}

void Player::Release(void)
{
}

Transform* Player::GetTransform(void)
{
	return &mTransform;
}

void Player::CalcGravity(void)
{
	VECTOR gravDir = mGravityManager->GetDirGravity();

	float gravPower = mGravityManager->GetPower();

	VECTOR gravVec = VScale(gravDir, gravPower);

	mJumpPow = gravVec;
}

void Player::AddCollider(Collider* collider)
{
	mColliders.push_back(collider);
}

void Player::ClearCollider(void)
{
	mColliders.clear();
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
	double rotRad = 0.0;
	if (CheckHitKey(KEY_INPUT_W)) {
		mMoveDir = VAdd(mMoveDir, cameraRot.GetForward());
		rotRad = AsoUtility::Deg2RadD(0.0);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		mMoveDir = VAdd(mMoveDir, cameraRot.GetBack());
		rotRad = AsoUtility::Deg2RadD(180.0);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		mMoveDir = VAdd(mMoveDir, cameraRot.GetLeft());
		rotRad = AsoUtility::Deg2RadD(270.0);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		mMoveDir = VAdd(mMoveDir, cameraRot.GetRight());
		rotRad = AsoUtility::Deg2RadD(90.0);
	}

	if (!AsoUtility::EqualsVZero(mMoveDir)) {
		bool isLShift = CheckHitKey(KEY_INPUT_LSHIFT);
		mAnimationController->Play(int(isLShift ? ANIM_TYPE::FAST_RUN: ANIM_TYPE::RUN));
		mSpeed = isLShift ? SPEED_RUN : SPEED_MOVE;
		mMoveDir = VNorm(mMoveDir);

		SetGoalRotate(rotRad);
	}
	else {
		mAnimationController->Play(int(ANIM_TYPE::IDLE));
	}
}

void Player::SetGoalRotate(double rotRad)
{
	Quaternion cameraRot = mSceneManager->GetCamera()->GetQuaRotOutX();
	Quaternion axis = Quaternion::AngleAxis(cameraRot.y + rotRad, AsoUtility::AXIS_Y);
	double angleDiff_deg = Quaternion::Angle(axis, mGoalQuaRotY);
	mStepRotTime = 0;
	mGoalQuaRotY = axis;
}

void Player::Rotate(void)
{
	mStepRotTime -= mSceneManager->GetDeltaTime();
	double t = (TIME_ROT - mStepRotTime) / TIME_ROT;
	mPlayerRotY = Quaternion::Slerp(mPlayerRotY, mGoalQuaRotY, t);
}

void Player::Collision(void)
{
	VECTOR vel = VScale(mMoveDir, mSpeed);
	mTransform.pos = VAdd(mTransform.pos, vel);

	CollisionGravity();
	mTransform.pos = VAdd(mTransform.pos, mJumpPow);
}

void Player::CollisionGravity(void)
{
	VECTOR currentPos = mTransform.pos;
	VECTOR gravUpDir = mGravityManager->GetDirUpGravity();
	VECTOR gravDir = mGravityManager->GetDirGravity();
	float length = 10.0f;
	mGravHitUp = VAdd(currentPos, VScale(gravUpDir, length));
	mGravHitDown = VAdd(currentPos, VScale(gravDir, length));

	for (auto c : mColliders) {
		auto hit = MV1CollCheck_Line(c->mModelId, -1, mGravHitUp, mGravHitDown);

		if (hit.HitFlag > 0) {
			mTransform.pos = VAdd(mTransform.pos, VScale(gravUpDir, 2.0f));
			mJumpPow = AsoUtility::VECTOR_ZERO;
		}
	}
}
