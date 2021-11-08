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
	// ���W
	VECTOR mPos;
	//�傫��
	float mSize;
	// �ړ�����
	VECTOR mDir;
	//�ړ����x
	float mSpeed;
	//��������
	float mLifeTime;
	//z�\�[�g
	float mZLen;
};
