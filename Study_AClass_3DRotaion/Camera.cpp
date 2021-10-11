#include <math.h>
#include "DxLib.h"
#include "GameCommon.h"
#include "SceneManager.h"
#include "Quaternion.h"
#include "AsoUtility.h"
#include "Camera.h"

Camera::Camera(SceneManager* manager)
{
	mSceneManager = manager;
}

Camera::~Camera()
{
}

void Camera::Init()
{
}

void Camera::Update()
{
}

void Camera::SetBeforeDraw(void)
{
}

void Camera::Draw()
{
}

void Camera::Release(void)
{
}
