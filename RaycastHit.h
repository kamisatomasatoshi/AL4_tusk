#pragma once

#include "BaseCollider.h"
#include<DirectXMath.h>

class Object3d;

struct RaycastHit{
	Object3d* object = nullptr;

	BaseCollider* collider = nullptr; 

	DirectX::XMVECTOR inter;

	float distance = 0.0f;

};