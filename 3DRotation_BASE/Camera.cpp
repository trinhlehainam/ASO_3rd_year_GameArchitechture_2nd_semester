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

	// �J�����̏����ݒ�
	mPos = VGet(0.0f, HEIGHT, -DIS_TARGET2CAMERA);

	mAngles = VGet(0.0f, 0.0f, 0.0f);
	mAngles.x = AsoUtility::Deg2Rad(30.0f);

}

void Camera::Update()
{


	float movePow = 5.0f;

	// ������
	//// �����ɃJ������ړ�
	//if (CheckHitKey(KEY_INPUT_N))
	//{
	//	mPos.y -= movePow;
	//}

	//// �����ɃJ�������ړ�
	//if (CheckHitKey(KEY_INPUT_M))
	//{
	//	mPos.y += movePow;
	//}


	// �J������]
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		// �E��]
		mAngles.y += AsoUtility::Deg2Rad(1.0f);
	}
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		// ����]
		mAngles.y += AsoUtility::Deg2Rad(-1.0f);
	}

	// ������
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	// ���]
	//	mAngles.x += AsoUtility::Deg2Rad(1.0f);
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	// ����]
	//	mAngles.x += AsoUtility::Deg2Rad(-1.0f);
	//}

}

void Camera::SetBeforeDraw(void)
{

	if (mUnit == nullptr)
	{

		// �J�����Z�b�g
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

		// �����_�̈ړ�
		//-------------------------------------

		// �J�����p�x(rad)����A�J�����̌���(Vec)���擾
		dirX = sin(mAngles.y);
		dirZ = cos(mAngles.y);

		// �P�ʃx�N�g���ɕϊ�
		dir = VNorm({ dirX, 0.0f, dirZ });

		// �J�����̌����ƈړ��ʂ���ړ��x�N�g�����擾
		movePow = VScale(dir, DIS_TARGET2UNIT);

		// ���j�b�g����J�����̌����ɑ΂��āA
		// ��苗�����ꂽ�ꏊ�𒍎��_�Ƃ���
		VECTOR unitPos = mUnit->GetPos();
		mTargetPos = VAdd(unitPos, movePow);
		mTargetPos.y = 0.0f;
		//-------------------------------------

		// �J�����̈ړ�
		//-------------------------------------

		// �J�����p�x(rad)����A�J�����̔��Ό���(Vec)���擾
		float revRad = AsoUtility::Deg2Rad(180.0f);
		dirX = sin(mAngles.y + revRad);
		dirZ = cos(mAngles.y + revRad);

		// �P�ʃx�N�g���ɕϊ�
		dir = VNorm({ dirX, 0.0f, dirZ });

		// �J�����̔��Ό����ƈړ��ʂ���ړ��x�N�g�����擾
		movePow = VScale(dir, DIS_TARGET2CAMERA);

		// �����_����J�����̔��Ό����ɑ΂��āA
		// ��苗�����ꂽ�ꏊ���J�����ʒu�Ƃ���
		mPos = VAdd(mTargetPos, movePow);

		// �����͌Œ�
		mPos.y = HEIGHT;
		//-------------------------------------

		// �J�����̐ݒ�
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
