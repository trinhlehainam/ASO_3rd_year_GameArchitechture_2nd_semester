#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Unit.h"

Unit::Unit(SceneManager* manager)
{
	mSceneManager = manager;
}

void Unit::Init(void)
{

	mModel = MV1LoadModel("Model/Human.mv1");
	mPos = { 0.0f, 0.0f, 0.0f };
	mAngles = { 0.0f, 0.0f, 0.0f };
	mAnglesLocal = { 0.0f, (float)AsoUtility::Deg2Rad(180.0f), 0.0f };

	MV1SetPosition(mModel, mPos);

	// 再生するアニメーションの設定
	mAnimWalk = MV1AttachAnim(mModel, 1);

	// アニメーション総時間の取得
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModel, mAnimWalk);
	mStepAnim = 0.0f;

	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);

}

void Unit::Update(void)
{

	// 経過時間の取得
	float deltaTime = mSceneManager->GetDeltaTime();
	
	// 新しいアニメーション再生時間をセット
	mStepAnim += (deltaTime * SPEED_ANIM);
	if (mStepAnim > mTimeTotalAnimWalk)
	{
		mStepAnim = 0.0f;
	}
	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);


	// 移動量
	float movePow = 5.0f;

	// カメラ角度を取得
	VECTOR cameraAngles = mSceneManager->GetCamera()->GetAngles();

	// 操作キー判定
	bool isHitMove = false;

	// 回転したい角度
	float rotRad = 0;

	// カメラ方向に前進したい
	if (CheckHitKey(KEY_INPUT_W))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(0);
	}


	// カメラ方向から後退したい
	if (CheckHitKey(KEY_INPUT_S))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(180);
	}


	// カメラ方向から右側へ移動したい
	if (CheckHitKey(KEY_INPUT_D))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(90);
	}


	// カメラ方向から左側へ移動したい
	if (CheckHitKey(KEY_INPUT_A))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(-90);
	}
	

	if (isHitMove){

		// 移動処理
		mPos.x += sinf(cameraAngles.y + rotRad) * movePow;
		mPos.z += cosf(cameraAngles.y + rotRad) * movePow;

		// パターン①　deg計算
		//------------------------------------------------------------------------------
		//// 回転処理
		//float degUnitAngleY = AsoUtility::Rad2Deg(mAngles.y);
		//float degMoveAngleY = AsoUtility::Rad2Deg(cameraAngles.y + rotRad);
		//degMoveAngleY = AsoUtility::DegIn360(degMoveAngleY);

		//// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
		//float aroundDir = AsoUtility::DirNearAroundDeg(degUnitAngleY, degMoveAngleY);

		//// ブルブルしないように角度差を埋める
		//float diff = degMoveAngleY - degUnitAngleY;
		//if (abs(diff) <= (SPEED_ROT + 0.5f))
		//{
		//	mAngles.y = AsoUtility::Deg2Rad(degMoveAngleY);
		//}
		//else
		//{
		//	mAngles.y += AsoUtility::Deg2Rad(SPEED_ROT * aroundDir);
		//}
		//mAngles.y = AsoUtility::RadIn2PI(mAngles.y);
		//------------------------------------------------------------------------------

		// パターン②　rad計算
		//------------------------------------------------------------------------------
		// 回転処理
		float radUnitAngleY = mAngles.y;
		float radMoveAngleY = cameraAngles.y + rotRad;
		radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);

		// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

		// ブルブルしないように角度差を埋める
		float diff = radMoveAngleY - radUnitAngleY;
		if (abs(diff) <= (SPEED_ROT_RAD + 0.01f))
		{
			mAngles.y = radMoveAngleY;
		}
		else
		{
			mAngles.y += (SPEED_ROT_RAD * aroundDir);
		}
		mAngles.y = AsoUtility::RadIn2PI(mAngles.y);
		//------------------------------------------------------------------------------

	}

	// モデルの移動
	MV1SetPosition(mModel, mPos);

	// モデルの回転
	VECTOR angles = mAngles;
	angles.x += mAnglesLocal.x;
	angles.y += mAnglesLocal.y;
	angles.z += mAnglesLocal.z;
	MV1SetRotationXYZ(mModel, angles);

}

void Unit::Draw(void)
{
	MV1DrawModel(mModel);
}

void Unit::Release(void)
{
	MV1DeleteModel(mModel);
}

VECTOR Unit::GetPos(void)
{
	return mPos;
}

VECTOR Unit::GetAngles(void)
{
	return mAngles;
}
