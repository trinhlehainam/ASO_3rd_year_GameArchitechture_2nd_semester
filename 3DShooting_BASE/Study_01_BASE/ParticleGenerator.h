#pragma once
#include <vector>
#include <DxLib.h>
#include "Quaternion.h"

class ParticleGenerator
{
public:

	//�p�[�e�B�N��������
	static constexpr int NUM_PARTICLE = 30;


	// �~�`����|���S��
	static constexpr int NUM_POLYGON = 10;
	static constexpr float SPLIT_ANGLE_DEG = 360.f / NUM_POLYGON;

	// �傫��
	static constexpr int GEN_MIN_SIZE = 3.f;
	static constexpr int GEN_MAX_SIZE = 5.f;

	static constexpr int GEN_MIN_SPEED = 1.f;
	static constexpr int GEN_MAX_SPEED = 2.f;

	static constexpr int GEN_MIN_LIFE_TIME = 1.f;
	static constexpr int GEN_MAX_LIFE_TIME = 2.f;

	static constexpr float GEN_SEC = 1.f;

	ParticleGenerator(class SceneManager* manager, VECTOR pos, float radious);
	void Init(void);
	void Update(void);
	void DebugProcess(void);
	void Draw(void);
	void DrawMeshSquare(void);
	void DrawMeshCircle(void);
	void Release(void);
	void SetPos(VECTOR pos);
	void SetRot(Quaternion rot);

private:

	class SceneManager* mSceneManager;

	int mImgLight;
	// ���W
	VECTOR mPos;

	// ��]
	Quaternion mQuaRot;

	// ���a
	float mRadious;

	// �|���S���f�[�^(��)
	VERTEX3D mVerticesSquare[6];

	// �|���S���f�[�^
	VERTEX3D mVerticesCircle[NUM_POLYGON+1];

	// �e�X�g�p:���o���b�V���쐬
	void CreateMeshSquare(void);

	// ���_�C���f�b�N�X
	WORD mIndexes[NUM_POLYGON*3];

	std::vector<class Particle*> mParticles;

	// 
	class Particle* Generate(Particle* particle);
	void CreateMeshCircle(void);

};

