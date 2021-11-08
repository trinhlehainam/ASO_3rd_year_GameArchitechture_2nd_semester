#include "SceneManager.h"
#include "Particle.h"

Particle::Particle(SceneManager* manager, int img)
{
	mSceneManager = manager;
	mImgLight = img;

}

void Particle::Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifeTime)
{
	mPos = pos;
	mSize = size;
	mDir = dir;
	mSpeed = speed;
	mLifeTime = lifeTime;
}

void Particle::Init(void)
{
	mImgLight = LoadGraph("Image/Light.png");

	// ¡ì¬

	// 
}

void Particle::Update(void)
{
	// ˆÚ“®ŽžŠÔ
	mPos = VAdd(mPos, VScale(mDir, mSpeed * mSceneManager->GetDeltaTime()));

	// ¶‘¶ŽžŠÔ
	if (mLifeTime > 0.f)
	{
		mLifeTime -= mSceneManager->GetDeltaTime();
	}
}

void Particle::Draw(void)
{
	DrawBillboard3D(mPos, 0.5f, 0.5f, mSize,0.f,mImgLight,true);
}


void Particle::Release(void)
{

}

float Particle::GetZLen(void) const
{
	return mZLen;
}

void Particle::SetZLen(float len)
{
	mZLen = len;
}

VECTOR Particle::GetPos() const
{
	return mPos;
}

bool Particle::IsAlive(void) const
{
	return mLifeTime > 0.f;
}
