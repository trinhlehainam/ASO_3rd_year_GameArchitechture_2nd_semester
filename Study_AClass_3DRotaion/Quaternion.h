#pragma once
#include "DxLib.h"

class Quaternion
{

public:

	double w;
	double x;
	double y;
	double z;

	Quaternion(void);
	Quaternion(VECTOR rad);
	Quaternion(double w, double x, double y, double z);

	// �I�C���[�p����Q�֕ϊ�
	static Quaternion Euler(VECTOR rad);
	static Quaternion Euler(double radX, double radY, double radZ);

	// Q�̍���
	static Quaternion Mult(Quaternion q1, Quaternion q2);
	Quaternion Mult(Quaternion q);

	// �w�莲���w��p���A��]������
	static Quaternion AngleAxis(double rad, VECTOR axis);

	// Q����I�C���[�p�֕ϊ�
	static VECTOR ToEuler(Quaternion q);
	VECTOR ToEuler(void);

	// Q����s��֕ϊ�
	static MATRIX ToMatrix(Quaternion q);
	MATRIX ToMatrix(void);
	
	static float Dot(Quaternion q1, Quaternion q2);
	float Dot(Quaternion b);

	// ���K��
	Quaternion Normalized(void);
	void Normalize(void);

	// �t�N�H�[�^�j�I��
	Quaternion Inverse(void);

};

