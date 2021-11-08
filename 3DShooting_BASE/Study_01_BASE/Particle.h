#pragma once
#include <DxLib.h>
class Particle
{
public:
	Particle(class SceneManager* manager,int img);
	void Generate(VECTOR pos, float size, VECTOR dir, float speed, float lifeTime);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	float GetZLen(void) const;
	void SetZLen(float len);

	VECTOR GetPos() const;


	bool IsAlive(void) const;
private:
	SceneManager* mSceneManager;
	int mImgLight;
	// 座標
	VECTOR mPos;
	//大きさ
	float mSize;
	// 移動方向
	VECTOR mDir;
	//移動速度
	float mSpeed;
	//生存時間
	float mLifeTime;
	//zソート
	float mZLen;
};
