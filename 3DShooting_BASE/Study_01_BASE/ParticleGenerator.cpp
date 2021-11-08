#include <cmath>
#include <algorithm>
#include "AsoUtility.h"
#include "Quaternion.h"
#include "SceneManager.h"
#include "Camera.h"
#include "ParticleGenerator.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radious)
{
	mSceneManager = manager;
	mPos = pos;
	mRadious = radious;
}

void ParticleGenerator::Init(void)
{
	mImgLight = LoadGraph("Image/Light.png", true);
	// ��Mesh�̍쐬
	//CreateMeshSquare();
	// �~�`Mesh�̍쐬
	//CreateMeshCircle();
	for (int i = 0; i < NUM_PARTICLE; i++)
	{
		mParticles.push_back(Generate(nullptr));
	}
}

void ParticleGenerator::Update(void)
{
	for (auto& p : mParticles)
	{
		p->Update();
		// �������Ԃ��؂ꂽ��
		if (p->IsAlive())
		{
			//p = Generate(p);
		}
	}

	// 
	DebugProcess();
}

void ParticleGenerator::DebugProcess(void)
{
	Quaternion tmpQ;
	bool isHitKey = false;
	// �E��]
	if (CheckHitKey(KEY_INPUT_L))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.f), AsoUtility::AXIS_Y
		);
	}

	// ����]
	if (CheckHitKey(KEY_INPUT_J))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(-1.f), AsoUtility::AXIS_Y
		);
	}


	// ������]
	if (CheckHitKey(KEY_INPUT_I))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(1.f), AsoUtility::AXIS_X
		);
	}

	// ����]
	if (CheckHitKey(KEY_INPUT_K))
	{
		isHitKey = true;
		tmpQ = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(-1.f), AsoUtility::AXIS_X
		);
	}

	if (isHitKey)
	{
		mQuaRot = mQuaRot.Mult(tmpQ);
		CreateMeshCircle();
	}
}

void ParticleGenerator::Draw(void)
{
	// �J�����̌���
	Camera* camera = mSceneManager->GetCamera();
	VECTOR c2t = camera->GetDir();

	VECTOR c2p;
	for (auto& p : mParticles)
	{
		// �J�������猩���p�[�e�B�N���̌���(�x�N�g��)
		c2p = VSub(p->GetPos(), camera->GetPos());
		// �������Z�b�g
		p->SetZLen(VDot(c2t, c2p));

	}
	// �C�e���[�^�[�R���N�V����
	std::sort(mParticles.begin(), mParticles.end(),
		[](Particle* x, Particle* y) 
		{return x->GetZLen() > y->GetZLen(); });

	DrawBillboard3D(mPos, 0.5f, 0.5f, 100.0f, 0.f,mImgLight, true);
	SetUseBackCulling(false);
	DrawMeshCircle();

	for (auto& p : mParticles)
	{
		p->Draw();
	}
	SetUseBackCulling(true);
}

void ParticleGenerator::DrawMeshSquare(void)
{
	DrawPolygon3D(mVerticesSquare, 2, DX_NONE_GRAPH, true);
	//
	for (auto& v : mVerticesSquare)
	{
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::DrawMeshCircle(void)
{
	// �~�`���b�V���̕`��
	// 0�̂Ƃ���͒��_���ł�
	DrawPolygonIndexed3D(mVerticesCircle, NUM_POLYGON*3, mIndexes, NUM_POLYGON, DX_NONE_GRAPH, true);
	// ���܂��Œ��_�`��
	for (auto& v : mVerticesCircle)
	{
		DrawSphere3D(v.pos, 2, 3, 0xff0000, 0xff0000, true);
	}
}

void ParticleGenerator::Release(void)
{
	DeleteGraph(mImgLight);
	for (auto& p : mParticles)
	{
		p->Release();
		p = nullptr;
	}
}

void ParticleGenerator::SetPos(VECTOR pos)
{
	mPos = pos;
}

void ParticleGenerator::SetRot(Quaternion rot)
{
	mQuaRot = rot;
	CreateMeshCircle();
}

void ParticleGenerator::CreateMeshSquare(void)
{
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);

	for (int i = 0; i < 6; i++)
	{
		mVerticesSquare[i].dif = c;
	}
	float h = 100.f;
	//
	mVerticesSquare[0].pos = { 0,0,0 };
	mVerticesSquare[1].pos = { 0,0,100 };
	mVerticesSquare[2].pos = { 100,0,100 };
	mVerticesSquare[3].pos = { 0,0,0 };
	mVerticesSquare[4].pos = { 100,0,100 };
	mVerticesSquare[5].pos = { 100,0,0 };

}

Particle* ParticleGenerator::Generate(Particle* particle)
{
	if (particle == nullptr)
	{
		particle = new Particle(mSceneManager, mImgLight);
	}

#pragma region �����ʒu
	// �����ʒu
	VECTOR pos = {0,0,0};
	Quaternion rotY = Quaternion::AngleAxis(
		AsoUtility::Deg2RadF(GetRand(360.f)), AsoUtility::AXIS_Y);
	rotY = mQuaRot.Mult(rotY);
	pos = rotY.PosAxis({ 0.f,0.f,(float)GetRand(mRadious) });
#pragma endregion

	// �ړ�����
	VECTOR dir={0,0,0};
	//------------------------------------------------------------------------------------------
	//�@ x����]�����(60-80)
	//�A y����]��x�����]������
	//�B ��]������ɕϊ�
	float randDeg = 60 + GetRand(80 - 60);
	randDeg *= -1.f;
	Quaternion rotX = Quaternion::AngleAxis(AsoUtility::Deg2RadF(randDeg), AsoUtility::AXIS_X);
	Quaternion rot = mQuaRot.Mult(rotX);
	dir = rot.GetForward();
	//------------------------------------------------------------------------------------------
	// �傫��
	float size = GEN_MIN_SIZE + GetRand(GEN_MAX_SIZE - GEN_MIN_SIZE);

	//�@���x
	float speed = GEN_MIN_SPEED + GetRand(GEN_MAX_SPEED - GEN_MIN_SPEED);

	//�@��������
	float lifeTime = GEN_MIN_LIFE_TIME + GetRand(GEN_MAX_LIFE_TIME - GEN_MIN_LIFE_TIME);

	particle->Generate(pos, size, dir, speed, lifeTime);
	return particle;
}

void ParticleGenerator::CreateMeshCircle(void)
{
	COLOR_U8 c = GetColorU8(255, 255, 255, 255);
	COLOR_U8 g = GetColorU8(0, 200, 0, 255);

	for (int i = 1; i < (NUM_POLYGON+1); i++)
	{
		mVerticesCircle[i].dif = c;
	}
	
	//���_��
	int cntVertex = 0;
	// �~�̒��S���_
	mVerticesCircle[cntVertex++].pos = mPos;
	auto cpos = mVerticesCircle[0].pos;

	float add_deg = 360.f / NUM_POLYGON;
	float cntAngle = 0;
	// �~���̃��[�v�쐬
	auto rad = 0.f;
	VECTOR pos;
	Quaternion rot;


	while (cntVertex<(NUM_POLYGON + 1))
	{
		//���_���W(�N���[�^�j�I��)
		rot = Quaternion::AngleAxis(
			AsoUtility::Deg2RadF(cntAngle), AsoUtility::AXIS_Y);
		rot = mQuaRot.Mult(rot);

		// ���W�����(���W����]������)
		pos = rot.PosAxis({ 0.f,0.f,mRadious });

		// �\����
		mVerticesCircle[cntVertex++].pos = VAdd(cpos, pos);
		
		// ��]�p�x��������
		cntAngle+= add_deg;
		
	}
	int cntIdx = 0;
	int cntTry = 1;
	for (int i = 1; i < NUM_POLYGON; i++)
	{
		mIndexes[cntIdx++] = 0;
		mIndexes[cntIdx++] = cntTry;
		mIndexes[cntIdx++] = ++cntTry;
	}

	mIndexes[cntIdx++] = 0;
	mIndexes[cntIdx++] = cntTry;
	mIndexes[cntIdx++] = 1;
}
