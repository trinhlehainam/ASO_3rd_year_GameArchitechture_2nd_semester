#include <math.h>
#include "DxLib.h"
#include "AsoUtility.h"
#include "Unit.h"
#include "Camera.h"

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Init()
{

	// カメラの初期設定
	mPos = VGet(0.0f, HEIGHT, -DIS_TARGET2CAMERA);

	mAngles = VGet(0.0f, 0.0f, 0.0f);
	mAngles.x = AsoUtility::Deg2Rad(30.0f);

}

void Camera::Update()
{


	float movePow = 5.0f;

	// 無効に
	//// 垂直にカメラ上移動
	//if (CheckHitKey(KEY_INPUT_N))
	//{
	//	mPos.y -= movePow;
	//}

	//// 垂直にカメラ下移動
	//if (CheckHitKey(KEY_INPUT_M))
	//{
	//	mPos.y += movePow;
	//}


	// カメラ回転
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		// 右回転
		mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		// 左回転
		mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	// 無効に
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	// 上回転
	//	mAngles.x += AsoUtility::Deg2Rad(1.0f);
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	// 下回転
	//	mAngles.x += AsoUtility::Deg2Rad(-1.0f);
	//}

}

void Camera::SetBeforeDraw(void)
{

	if (mUnit == nullptr)
	{

		// カメラセット
		SetCameraPositionAndAngle(
			mPos,
			mAngles.x,
			mAngles.y,
			0.0f
		);
	}
	else
	{

		float dirX;
		float dirZ;
		VECTOR dir;
		VECTOR movePow;

		// 注視点の移動
		//-------------------------------------

		// カメラ角度(rad)から、カメラの向き(Vec)を取得
		dirX = sin(mAngles.y);
		dirZ = cos(mAngles.y);

		// 単位ベクトルに変換
		dir = VNorm({ dirX, 0.0f, dirZ });

		// カメラの向きと移動量から移動ベクトルを取得
		movePow = VScale(dir, DIS_TARGET2UNIT);

		// ユニットからカメラの向きに対して、
		// 一定距離離れた場所を注視点とする
		VECTOR unitPos = mUnit->GetPos();
		mTargetPos = VAdd(unitPos, movePow);
		mTargetPos.y = 0.0f;
		//-------------------------------------

		// カメラの移動
		//-------------------------------------

		// カメラ角度(rad)から、カメラの反対向き(Vec)を取得
		float revRad = AsoUtility::Deg2Rad(180.0f);
		dirX = sin(mAngles.y + revRad);
		dirZ = cos(mAngles.y + revRad);

		// 単位ベクトルに変換
		dir = VNorm({ dirX, 0.0f, dirZ });

		// カメラの反対向きと移動量から移動ベクトルを取得
		movePow = VScale(dir, DIS_TARGET2CAMERA);

		// 注視点からカメラの反対向きに対して、
		// 一定距離離れた場所をカメラ位置とする
		mPos = VAdd(mTargetPos, movePow);

		// 高さは固定
		mPos.y = HEIGHT;
		//-------------------------------------

		// カメラの設定
		SetCameraPositionAndTargetAndUpVec(
			mPos,
			mTargetPos,
			{ 0.0f, 1.0f, 0.0f }
		);

	}

}

void Camera::Draw()
{
}

void Camera::Release(void)
{
}

void Camera::SetUnit(Unit* unit)
{
	mUnit = unit;
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetAngles(void)
{
	return mAngles;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}
