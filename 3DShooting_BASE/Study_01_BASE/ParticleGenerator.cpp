#include "ParticleGenerator.h"
#include "AsoUtility.h"
#include "Quaternion.h"

ParticleGenerator::ParticleGenerator(SceneManager* manager, VECTOR pos, float radius):
	mSceneMng(manager), mPos(pos), mRadius(radius)
{
}

void ParticleGenerator::Init(void)
{
	CreateMeshSquare();
	CreateMeshCircle();
}

void ParticleGenerator::Update(void)
{
}

void ParticleGenerator::Draw(void)
{
	DrawMeshSquare();
}

void ParticleGenerator::DrawMeshSquare(void)
{
	DrawPolygon3D(mVerticeSquare.data(), mVerticeSquare.size(), DX_NONE_GRAPH, true);

	for (const auto& vertex : mVerticeSquare)
		DrawSphere3D(vertex.pos, 2, 3, 0xff0000, 0xff0000, true);
}

void ParticleGenerator::DrawMeshCircle(void)
{
	DrawPolygonIndexed3D(mVerticeCircle.data(), 0, mIndices.data(), mVerticeCircle.size() - 1, DX_NONE_GRAPH, true);

	for (const auto& vertex : mVerticeSquare)
		DrawSphere3D(vertex.pos, 2, 3, 0xff0000, 0xff0000, true);
}

void ParticleGenerator::Release(void)
{
}

void ParticleGenerator::CreateMeshSquare(void)
{
	COLOR_U8 color = GetColorU8(255, 255, 255, 255);

	for (auto& vert : mVerticeSquare)
		vert.dif = color;
	
	float z = 0.0f;
	float h = 100.0f;
	mVerticeSquare[0].pos = { z,z,z };
	mVerticeSquare[1].pos = { z,z,h };
	mVerticeSquare[2].pos = { h,z,h };

	mVerticeSquare[3].pos = { z,z,z };
	mVerticeSquare[4].pos = { h,z,h };
	mVerticeSquare[5].pos = { h,z,z };

}

void ParticleGenerator::CreateMeshCircle(void)
{
	COLOR_U8 white = GetColorU8(255, 255, 255, 255);
	COLOR_U8 green = GetColorU8(0, 200, 0, 255);

	mVerticeCircle[0].dif = green;
	for (int i = 0; i < mVerticeCircle.size(); ++i)
		mVerticeCircle[i].dif = white;

	// Center
	mVerticeCircle[0].pos = mPos;
	
	VECTOR pos;
	Quaternion rot;
	float angle = 0.0f;
	for (int i = 0; i < mVerticeCircle.size(); ++i) {
		rot = Quaternion::AngleAxis(AsoUtility::Deg2RadF(angle), AsoUtility::AXIS_Y);
		pos = { 0.0f,0.0f,mRadius };
		pos = VTransform(mPos, rot.ToMatrix());
		mVerticeCircle[i].pos = VAdd(mPos, pos);
		angle += SPLIT_ANGLE_DEG;
	}

	for (int i = 0; i < mIndices.size(); ++i) {
		int idx = i * 3;
		mIndices[idx] = 0;
		mIndices[idx + 1] = i + 1;
		mIndices[idx + 2] = i + 2;
	}
}
