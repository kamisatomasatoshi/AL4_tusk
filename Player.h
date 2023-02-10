#pragma once

#include "Object3d.h"
class Player : public Object3d {
public:
	static Player* Create(Model* model = nullptr);

public:
	bool Initialize()override;

	void Update() override;

	void OnCollision(const CollisionInfo& info)override;

private:
	//接地フラグ
	bool onGround = true;
	//落下ベクトル
	DirectX::XMVECTOR fallV;

};