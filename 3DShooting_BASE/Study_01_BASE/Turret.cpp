#include "DxLib.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "Resource.h"
#include "ResourceManager.h"
#include "Turret.h"

Turret::Turret(SceneManager* manager,
	Transform* transformPlayer,
	Transform* transformParent,
	VECTOR localPos,
	VECTOR localAddAxis)
{

	mSceneManager = manager;
	mTransformPlayer = transformPlayer;

	mTransformParent = transformParent;
	mLocalPos = localPos;
	mLocalAddAxis = localAddAxis;

	ResourceManager* rem = mSceneManager->GetResource();

	mTransformStand.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_STAND));
	mTransformGun.SetModel(rem->LoadModelDuplicate(ResourceManager::SRC::TURRET_GUN));

	mExplosion = new SpriteAnimator(
		mSceneManager, ResourceManager::SRC::SHIP_EXPLOSION, 120, 8.0f);

	mStepDamaged = -1;

	// �C�g���[�J����]
	mLocalAddAxisGun = { 0.0f, 0.0f, 0.0f };

	ChangeState(STATE::ATTACK);

}

void Turret::Init(void)
{

	Quaternion localRot;
	Quaternion axis;

	// ���f������̊�{���(�C��)
	mTransformStand.scale = { SCALE, SCALE, SCALE };
	mTransformStand.quaRot = Quaternion();

	// ���[�J����]
	mTransformStand.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(0.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformStand, { 0, 0, 0 });



	// ���f������̊�{���(�C�g)
	mTransformGun.scale = { SCALE, SCALE, SCALE };
	mTransformGun.quaRot = Quaternion();

	// ���[�J����]
	mTransformGun.quaRotLocal = Quaternion::Euler(
		AsoUtility::Deg2RadF(-5.0f),
		AsoUtility::Deg2RadF(180.0f),
		AsoUtility::Deg2RadF(0.0f)
	);

	// �e���f���Ɠ���
	SyncParent(&mTransformGun, { 0, 0, 0 });

	// �ϋv��
	mHp = 2;

	// �C�䃍�[�J���ғ���(deg)
	mAnglePowStand = ANGLE_POW_STAND;

	// �C�g���[�J���ғ���(deg)
	mAnglePowGun = ANGLE_POW_GUN;

}

void Turret::Update(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
	{

		float deg;

		// �C�䃍�[�J����]

		// �C��
		SyncParent(&mTransformStand, mLocalAddAxisStand);

		// �C�g���[�J����]
		
		// �C�g
		//SyncParent(&mTransformGun, mix.ToEuler());

		// ��_������
		if (mStepDamaged > 0.0f)
		{
			mStepDamaged -= mSceneManager->GetDeltaTime();
		}

	}
		break;
	case Turret::STATE::DESTROY:

		// �e�̍X�V
		mExplosion->Update();
		break;
	}

}

void Turret::Draw(void)
{

	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:

		if (mStepDamaged > 0.0f)
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.8f, 0.1f, 0.1f, 0.8f));
		}
		else
		{
			MV1SetMaterialDifColor(mTransformStand.modelId, 0, GetColorF(0.48f, 0.52f, 0.4f, 1.0f));
			MV1SetMaterialDifColor(mTransformGun.modelId, 0, GetColorF(0.2f, 0.4f, 0.3f, 1.0f));
		}

		MV1DrawModel(mTransformStand.modelId);
		MV1DrawModel(mTransformGun.modelId);

		if (IS_DEBUG)
		{
			DrawSphere3D(mTransformStand.pos, COLLISION_RADIUS, 10, 0xff0000, 0xffffff, false);
		}

		break;
	case Turret::STATE::DESTROY:
		mExplosion->Draw();
		break;
	}

}

void Turret::Release(void)
{

	mExplosion->Release();
	delete mExplosion;

}

void Turret::SyncParent(Transform* transform, VECTOR addAxis)
{
	VECTOR localPos;
	transform->quaRot = mTransformParent->quaRot;
	localPos = Quaternion::PosAxis(transform->quaRot, mLocalPos);

	transform->pos = VAdd(mTransformParent->pos, VScale(localPos, SCALE));

	transform->Update();
}

bool Turret::IsAlive(void)
{
	return mState == STATE::ATTACK;
}

VECTOR Turret::GetPos(void)
{
	return mTransformStand.pos;
}

void Turret::Damage(void)
{

	mStepDamaged = TIME_DAMAGED_EFFECT;

	mHp -= 1;
	if (mHp <= 0)
	{
		ChangeState(STATE::DESTROY);
	}

}

void Turret::ChangeState(STATE state)
{

	mState = state;
	switch (mState)
	{
	case Turret::STATE::NONE:
		break;
	case Turret::STATE::ATTACK:
		break;
	case Turret::STATE::DESTROY:
	{
		auto mat = mTransformGun.quaRot.ToMatrix();
		auto localPos = VTransform({ 0.0f, 1.2f, 0.0f }, mat);
		auto birthPos = VAdd(mTransformStand.pos, VScale(localPos, SCALE));
		mExplosion->Create(birthPos);
	}
	break;
	}

}
