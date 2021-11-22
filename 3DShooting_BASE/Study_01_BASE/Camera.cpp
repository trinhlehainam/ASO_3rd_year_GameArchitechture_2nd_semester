#include "Camera.h"

#include "DxLib.h"
#include "AsoUtility.h"
#include "GameCommon.h"
#include "Quaternion.h"

#include "SceneManager.h"
#include "Transform.h"


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
	mVelocity = { 1.0f, 1.0f, 1.0f };

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
	case MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	case MODE::FOLLOW_STRING:
		SetBeforeDrawFollowSrping();
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

		mCameraUp = mQuaRot.GetUp();
		mTargetPos = VAdd(mPos, localPos);
		//
	}

	if (!AsoUtility::EqualsVZero(moveDir)) {

		// Calculate Translate
		const float moveSpeed = 10.0f;

		VECTOR moveVec = VNorm(VTransform(moveDir, mQuaRot.ToMatrix()));
		moveVec = VScale(moveVec, moveSpeed);
		//

		mPos = VAdd(mPos, moveVec);
		mTargetPos = VAdd(mTargetPos, moveVec);
	}
}

void Camera::SetBeforeDrawFixed(void)
{
}

void Camera::SetBeforeDrawFollow(void)
{
	VECTOR objectPos = mObjectTransform->pos;
	Quaternion objectRot = mObjectTransform->quaRot;
	MATRIX objectMat = mObjectTransform->matRot;
	
	// Calculate camera position
	VECTOR relativeCameraPos = objectRot.PosAxis(RELATIVE_CAMERA_FOLLOW);
	mPos = VAdd(objectPos, relativeCameraPos);
	//
	
	// Calculate camera look at position
	VECTOR relativeTargetPos = objectRot.PosAxis(RELATIVE_TARGET_POS);
	mTargetPos = VAdd(objectPos, relativeTargetPos);
	//

	mCameraUp = objectRot.GetUp();
}

void Camera::SetBeforeDrawFollowSrping(void)
{
	float delta = mSceneManager->GetDeltaTime();

	VECTOR objectPos = mObjectTransform->pos;
	Quaternion objectRot = mObjectTransform->quaRot;
	MATRIX objectMat = mObjectTransform->matRot;

	// Calculate camera pos with spring force
	VECTOR relativeCameraPos = objectRot.PosAxis(RELATIVE_CAMERA_SPRING);

	constexpr float POW_SPRING = 24.0f;
	const float DAMPENING = 2.0f * sqrtf(POW_SPRING);

	VECTOR idealPos = VAdd(objectPos, relativeCameraPos);

	VECTOR diff = VSub(mPos, idealPos);

	VECTOR force = VScale(diff, -POW_SPRING);
	force = VSub(force, VScale(mVelocity, DAMPENING));

	mVelocity = VAdd(mVelocity, force);

	mPos = VAdd(mPos, VScale(mVelocity, delta));
	//

	// Calculate camera look at position
	VECTOR relativeTargetPos = objectRot.PosAxis(RELATIVE_TARGET_POS);
	mTargetPos = VAdd(objectPos, relativeTargetPos);
	//

	mCameraUp = objectRot.GetUp();
}

void Camera::SetBeforeDrawShake(void)
{
	mStepShake -= mSceneManager->GetDeltaTime();
	if (mStepShake < 0.0f)
	{
		mPos = mDefaultPos;
		return ChangeMode(MODE::FIXED_POINT);
	}

	float pow = WIDTH_SHAKE * sinf(mStepShake * SPEED_SHAKE);
	VECTOR vel = VScale(mShakeDir, pow);
	mPos = VAdd(mDefaultPos, vel);
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
	case MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;
	case MODE::FOLLOW_STRING:
		SetBeforeDrawFollowSrping();
		break;
	case MODE::SHAKE:
		mStepShake = TIME_SHAKE;
		mShakeDir = VNorm({ 0.7f, 0.7f, 0.0f });
		mDefaultPos = mPos;
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

void Camera::SetTargetTransform(Transform* targetTransform)
{
	mObjectTransform = targetTransform;
}
