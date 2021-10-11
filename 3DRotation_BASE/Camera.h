#pragma once
#include "DxLib.h"
class Unit;

class Camera
{

public:

	// �J�����̍���
	static constexpr float HEIGHT = 300.0f;

	// �����_����J�����܂ł̋���
	static constexpr float DIS_TARGET2CAMERA = 500.0f;

	// �����_����L�����N�^�[�܂ł̋���
	static constexpr float DIS_TARGET2UNIT = 300.0f;

	Camera(void);
	~Camera();

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

	void SetUnit(Unit* unit);
	VECTOR GetPos(void);
	VECTOR GetAngles(void);
	VECTOR GetTargetPos(void);

private:

	Unit* mUnit;

	// �J�����̈ʒu
	VECTOR mPos;

	// �J�����p�x(rad)
	VECTOR mAngles;

	// �����_
	VECTOR mTargetPos;

};

