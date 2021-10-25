#pragma once
#include "Transform.h"

class Rock
{
public:
	Rock(void);
	void Init(int modelID, VECTOR pos, VECTOR angle, VECTOR scale);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	Transform mTransform;
	int modeilID;
};

