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

	// �Đ�����A�j���[�V�����̐ݒ�
	mAnimWalk = MV1AttachAnim(mModel, 1);

	// �A�j���[�V���������Ԃ̎擾
	mTimeTotalAnimWalk = MV1GetAttachAnimTotalTime(mModel, mAnimWalk);
	mStepAnim = 0.0f;

	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);

}

void Unit::Update(void)
{

	// �o�ߎ��Ԃ̎擾
	float deltaTime = mSceneManager->GetDeltaTime();
	
	// �V�����A�j���[�V�����Đ����Ԃ��Z�b�g
	mStepAnim += (deltaTime * SPEED_ANIM);
	if (mStepAnim > mTimeTotalAnimWalk)
	{
		mStepAnim = 0.0f;
	}
	MV1SetAttachAnimTime(mModel, mAnimWalk, mStepAnim);


	// �ړ���
	float movePow = 5.0f;

	// �J�����p�x���擾
	VECTOR cameraAngles = mSceneManager->GetCamera()->GetAngles();

	// ����L�[����
	bool isHitMove = false;

	// ��]�������p�x
	float rotRad = 0;

	// �J���������ɑO�i������
	if (CheckHitKey(KEY_INPUT_W))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(0);
	}


	// �J�������������ނ�����
	if (CheckHitKey(KEY_INPUT_S))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(180);
	}


	// �J������������E���ֈړ�������
	if (CheckHitKey(KEY_INPUT_D))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(90);
	}


	// �J�����������獶���ֈړ�������
	if (CheckHitKey(KEY_INPUT_A))
	{
		isHitMove = true;
		rotRad = AsoUtility::Deg2Rad(-90);
	}
	

	if (isHitMove){

		// �ړ�����
		mPos.x += sinf(cameraAngles.y + rotRad) * movePow;
		mPos.z += cosf(cameraAngles.y + rotRad) * movePow;

		// �p�^�[���@�@deg�v�Z
		//------------------------------------------------------------------------------
		//// ��]����
		//float degUnitAngleY = AsoUtility::Rad2Deg(mAngles.y);
		//float degMoveAngleY = AsoUtility::Rad2Deg(cameraAngles.y + rotRad);
		//degMoveAngleY = AsoUtility::DegIn360(degMoveAngleY);

		//// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
		//float aroundDir = AsoUtility::DirNearAroundDeg(degUnitAngleY, degMoveAngleY);

		//// �u���u�����Ȃ��悤�Ɋp�x���𖄂߂�
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

		// �p�^�[���A�@rad�v�Z
		//------------------------------------------------------------------------------
		// ��]����
		float radUnitAngleY = mAngles.y;
		float radMoveAngleY = cameraAngles.y + rotRad;
		radMoveAngleY = AsoUtility::RadIn2PI(radMoveAngleY);

		// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
		float aroundDir = AsoUtility::DirNearAroundRad(radUnitAngleY, radMoveAngleY);

		// �u���u�����Ȃ��悤�Ɋp�x���𖄂߂�
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

	// ���f���̈ړ�
	MV1SetPosition(mModel, mPos);

	// ���f���̉�]
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
