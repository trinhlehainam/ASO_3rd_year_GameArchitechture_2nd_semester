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

	mShadowImg = LoadGraph("Data/Image/Shadow.png");

	mIsJump = false;
	mJumpStep = 0.0f;
	mJumpPow = AsoUtility::VECTOR_ZERO;

	mCapsule = new Capsule(&mTransform);
	mCapsule->SetRelativePosTop({ 0.0f, 110.0f, 0.0f });
	mCapsule->SetRelativePosDown({ 0.0f, 30.0f, 0.0f });
	mCapsule->SetRadius(20.0f);

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

	ProcessJump();

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

	DrawShadow();

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

	// Jump Info
	DrawFormatString(20, 80, black, "ジャンプ力 ： (%0.2f, %0.2f, %0.2f)",
		mJumpPow.x, mJumpPow.y, mJumpPow.z
	);

	DrawLine3D(mGravHitUp, mGravHitDown, 0x000000);

	DrawLine3D(mTransform.pos, VAdd(mTransform.pos, mJumpPow), 0x000000);

	mCapsule->Draw();
}

void Player::DrawShadow(void)
{
	constexpr float PLAYER_SHADOW_HEIGHT = 300.0f;
	constexpr float PLAYER_SHADOW_SIZE = 30.0f;
	int i, j;
	MV1_COLL_RESULT_POLY_DIM HitResDim;
	MV1_COLL_RESULT_POLY* HitRes;
	VERTEX3D Vertex[3];
	VECTOR SlideVec;
	int ModelHandle;

	// ライティングを無効にする
	SetUseLighting(FALSE);

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// テクスチャアドレスモードを CLAMP にする( テクスチャの端より先は端のドットが延々続く )
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);

	// 影を落とすモデルの数だけ繰り返し
	for (const auto& c : mColliders) {

		ModelHandle = c->mModelId;

		// プレイヤーの直下に存在する地面のポリゴンを取得
		HitResDim = MV1CollCheck_Capsule(ModelHandle, -1, mTransform.pos, VAdd(mTransform.pos, VGet(0.0f, -PLAYER_SHADOW_HEIGHT, 0.0f)), PLAYER_SHADOW_SIZE);

		// 頂点データで変化が無い部分をセット
		Vertex[0].dif = GetColorU8(255, 255, 255, 255);
		Vertex[0].spc = GetColorU8(0, 0, 0, 0);
		Vertex[0].su = 0.0f;
		Vertex[0].sv = 0.0f;
		Vertex[1] = Vertex[0];
		Vertex[2] = Vertex[0];

		// 球の直下に存在するポリゴンの数だけ繰り返し
		HitRes = HitResDim.Dim;
		for (i = 0; i < HitResDim.HitNum; i++, HitRes++)
		{
			// ポリゴンの座標は地面ポリゴンの座標
			Vertex[0].pos = HitRes->Position[0];
			Vertex[1].pos = HitRes->Position[1];
			Vertex[2].pos = HitRes->Position[2];

			// ちょっと持ち上げて重ならないようにする
			SlideVec = VScale(HitRes->Normal, 0.5f);
			Vertex[0].pos = VAdd(Vertex[0].pos, SlideVec);
			Vertex[1].pos = VAdd(Vertex[1].pos, SlideVec);
			Vertex[2].pos = VAdd(Vertex[2].pos, SlideVec);

			// ポリゴンの不透明度を設定する
			Vertex[0].dif.a = 0;
			Vertex[1].dif.a = 0;
			Vertex[2].dif.a = 0;
			if (HitRes->Position[0].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[0].dif.a = 128 * (1.0f - fabs(HitRes->Position[0].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			if (HitRes->Position[1].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[1].dif.a = 128 * (1.0f - fabs(HitRes->Position[1].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			if (HitRes->Position[2].y > mTransform.pos.y - PLAYER_SHADOW_HEIGHT)
				Vertex[2].dif.a = 128 * (1.0f - fabs(HitRes->Position[2].y - mTransform.pos.y) / PLAYER_SHADOW_HEIGHT);

			// ＵＶ値は地面ポリゴンとプレイヤーの相対座標から割り出す
			Vertex[0].u = (HitRes->Position[0].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[0].v = (HitRes->Position[0].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[1].u = (HitRes->Position[1].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[1].v = (HitRes->Position[1].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[2].u = (HitRes->Position[2].x - mTransform.pos.x) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;
			Vertex[2].v = (HitRes->Position[2].z - mTransform.pos.z) / (PLAYER_SHADOW_SIZE * 2.0f) + 0.5f;

			// 影ポリゴンを描画
			DrawPolygon3D(Vertex, 1, mShadowImg, TRUE);
		}

		// 検出した地面ポリゴン情報の後始末
		MV1CollResultPolyDimTerminate(HitResDim);
	}

	// ライティングを有効にする
	SetUseLighting(TRUE);

	// Ｚバッファを無効にする
	SetUseZBuffer3D(FALSE);
}

void Player::Release(void)
{
	DeleteGraph(mShadowImg);
	delete mCapsule;
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

	mJumpPow = VAdd(mJumpPow, gravVec);

	if (VDot(mJumpPow, mGravityManager->GetDirGravity()) > 0.0f) {
		auto gravity = VScale(mGravityManager->GetDirGravity(), mGravityManager->GetPower());
		mJumpPow = gravity;
	}
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

		if (!mIsJump) {

		}

		SetGoalRotate(rotRad);
	}
	else {
		if (!mIsJump && IsLandingEnd())
			mAnimationController->Play(int(ANIM_TYPE::IDLE));
	}
}

void Player::ProcessJump(void)
{
	if (CheckHitKey(KEY_INPUT_Z)) {
		mAnimationController->Play((int)ANIM_TYPE::JUMP, false, 13.0f, 25.0f);
		mAnimationController->SetEndLoop(23.0f, 25.0f, 5.0f);

		mJumpStep -= mSceneManager->GetDeltaTime();
		if (mJumpStep > 0.0f)
			mJumpPow = VScale(mGravityManager->GetDirUpGravity(), POW_JUMP);
		mIsJump = true;
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

void Player::CollisionCapsule(void)
{
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
			mTransform.pos = VAdd(hit.HitPosition, VScale(gravUpDir, 2.0f));

			mJumpPow = AsoUtility::VECTOR_ZERO;
			mJumpStep = TIME_JUMP;
			if (mIsJump) {
				mAnimationController->Play((int)ANIM_TYPE::JUMP, false, 29.0f, 45.0f, false, true);
			}
			mIsJump = false;
		}
	}
}

bool Player::IsLandingEnd(void)
{
	bool ret = true;

	if (mAnimationController->GetPlayType() != (int)ANIM_TYPE::JUMP)
		return ret;

	if (mAnimationController->IsEnd())
		return ret;

	return false;
}
