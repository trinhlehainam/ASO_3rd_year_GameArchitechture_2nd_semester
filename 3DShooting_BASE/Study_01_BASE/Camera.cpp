#include "DxLib.h"
#include "GameCommon.h"
#include "Camera.h"
#include "AsoUtility.h"

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
}

Camera::~Camera()
{
}

void Camera::Init()
{
	ChangeMode(MODE::FREE);
	SetDefault();
}

void Camera::SetDefault(void)
{

	// カメラの初期設定
	mPos = DEFAULT_CAMERA_POS;
	mTargetPos = VAdd(mPos, RELATIVE_TARGET_POS);
	mCameraUp = { 0.0f, 1.0f, 0.0f };

	// カメラはX軸に傾いているが、この傾いた状態を傾き無しとする
	// mQuaRotは回転計算用で、
	// あくまで軸となるのは、カメラ座標と注視点とする
	mQuaRot = Quaternion();

}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{

	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(30.0f, 15000.0f);

	switch (mMode) {
	case MODE::FREE:
		SetBeforeDrawFree();
		break;
	case MODE::FIXED_POINT:
		SetBeforeDrawFixed();
		break;
	}

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		mPos,
		mTargetPos,
		mCameraUp
	);

}

void Camera::SetBeforeDrawFree(void)
{
	VECTOR moveDir = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_W)) { moveDir = AsoUtility::DIR_F; }
	if (CheckHitKey(KEY_INPUT_S)) { moveDir = AsoUtility::DIR_B; }
	if (CheckHitKey(KEY_INPUT_A)) { moveDir = AsoUtility::DIR_L; }
	if (CheckHitKey(KEY_INPUT_D)) { moveDir = AsoUtility::DIR_R; }
	
	VECTOR axisDeg = AsoUtility::VECTOR_ZERO;
	if (CheckHitKey(KEY_INPUT_UP)) { axisDeg.x += 1.0f; }
	if (CheckHitKey(KEY_INPUT_DOWN)) { axisDeg.x += -1.0f; }
	if (CheckHitKey(KEY_INPUT_LEFT)) { axisDeg.y += -1.0f; }
	if (CheckHitKey(KEY_INPUT_RIGHT)) { axisDeg.y += 1.0f; }

	if (!AsoUtility::EqualsVZero(axisDeg)) {
		// Calculate Rotation
		VECTOR axisRad;
		axisRad.x = AsoUtility::Deg2RadF(axisDeg.x);
		axisRad.y = AsoUtility::Deg2RadF(axisDeg.y);
		axisRad.z = AsoUtility::Deg2RadF(axisDeg.z);

		Quaternion axis = Quaternion::Euler(axisRad);
		mQuaRot.Mult(axis);

		VECTOR localPos = mQuaRot.PosAxis(RELATIVE_TARGET_POS);
		mTargetPos = VAdd(mPos, localPos);

		mCameraUp = mQuaRot.GetUp();
		//
	}

	if (!AsoUtility::EqualsVZero(moveDir)) {

		// Calculate Translate
		const float moveSpeed = 10.0f;

		VECTOR moveVec = VNorm(VTransform(moveDir, mQuaRot.ToMatrix()));
		moveVec = VScale(moveVec, moveSpeed);
		//

		mPos = VAdd(mPos, moveVec);
		mTargetPos = VAdd(mTargetPos, mPos);
	}
}

void Camera::SetBeforeDrawFixed(void)
{
}

void Camera::ChangeMode(MODE mode)
{
	mMode = mode;

	switch (mMode) {
	case MODE::FREE:
		SetBeforeDrawFree();
		break;
	case MODE::FIXED_POINT:
		SetBeforeDrawFixed();
		break;
	}
}

void Camera::Draw()
{
}

void Camera::DrawDebug(void)
{
}

void Camera::DrawUI(void)
{

	// 操作説明
	int x = 200;
	int y = 10;
	int addY = 40;
	DrawString(
		SCREEN_SIZE_X - x, y, "　【操作】", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　旋回：↑↓←→", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　加速：Ｂ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　　　　発弾：Ｎ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　シーン遷移：Ｓｐａｃｅ", 0xffffff);
	y += addY;
	DrawString(
		SCREEN_SIZE_X - x, y, "　1500m以上離れると", 0xffffff);
	y += 20;
	DrawString(
		SCREEN_SIZE_X - x, y, "　ゲームオーバー", 0xffffff);

}

void Camera::Release(void)
{
}

VECTOR Camera::GetPos(void)
{
	return mPos;
}

VECTOR Camera::GetTargetPos(void)
{
	return mTargetPos;
}

VECTOR Camera::GetDir(void)
{
	return VNorm(VSub(mTargetPos, mPos));
}
