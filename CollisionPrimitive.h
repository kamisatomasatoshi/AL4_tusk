#pragma once
#pragma once
/// <summary>
///当たり判定プリミティブ
/// </summary>


#include<DirectXMath.h>

struct Sphere {
	DirectX::XMVECTOR center = { 0,0,0,1 };

	float radius = 1.0f;

};

struct Plane {
	DirectX::XMVECTOR normal = { 0,1,0,0 };

	float distance = 0.0f;

};

class Triangle {
public:
	DirectX::XMVECTOR p0;
	DirectX::XMVECTOR p1;
	DirectX::XMVECTOR p2;

	DirectX::XMVECTOR normal;

	void ComputeNormal();

};

struct Ray
{
	DirectX::XMVECTOR start = { 0,0,0,1 };

	DirectX::XMVECTOR dir = { 1,0,0,0 };

};


//class BaseCollsion
//{
//protected:
//
//	uint32_t collisionAttribute = 0xffffffff;
//	//衝突マスク(相手)
//	uint32_t CollisionMask = 0xffffffff;
//
//	//名前(自分)
//	std::string collsionName;
//	//名前(相手)
//	char opponentCollsionName[256];
//
//	virtual ~BaseCollsion() = default;
//
//public:
//	//衝突時に呼ばれる関数
//	virtual void OnCollision() = 0;
//	//衝突属性(自分)を取得
//	const uint32_t GetCollisionAttribute();
//	//衝突属性(自分)を取得
//	void SetCollisionAttribute(uint32_t collisionAttribute_);
//	//衝突属性(相手)を取得
//	const uint32_t GetCollisionMask();
//	//衝突属性(相手)を設定
//	void SetCollisionMask(uint32_t CollisionMask_);
//
//	void SetCollsionName(std::string name);
//	std::string GetCollsionName();
//
//	void SetOpponentCollsionName(std::string name);
//	std::string GetOpponentCollsionName();
//};
//
///// <summary>
///// 球
///// </summary>
//class Sphere : public BaseCollsion
//{
//public:
//
//	//中心座標
//	AliceMathF::Vector4 center = { 0.0f,0.0f,0.0f,1.0f };
//	//半径
//	float radius = 1.0f;
//private:
//	char PADING[4]{};
//
//public:
//
//	//半径を取得
//	const float GetRadius();
//	//半径をを設定
//	void SetRadius(float radius_);
//	//中心座標を取得
//	const AliceMathF::Vector4& GetCenter();
//	//中心座標をを設定
//	void SetCenter(AliceMathF::Vector4& center_);
//	//衝突時に呼ばれる関数
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// 平面
///// </summary>
//class Plane : public BaseCollsion
//{
//protected:
//	//法線ベクトル
//	AliceMathF::Vector4 normal = { 0.0f,1.0f,0.0f,0.0f };
//	//原点点(0,0,0)からの距離
//	float distance = 0.0f;
//private:
//	char PADING[4]{};
//public:
//	//原点点(0,0,0)からの距離を取得
//	const float GetDistance();
//	//原点点(0,0,0)からの距離を設定
//	void SetDistance(float distance_);
//	//法線ベクトルを取得
//	const AliceMathF::Vector4& GetNormal();
//	//法線ベクトルを設定
//	void SetNormal(AliceMathF::Vector4& normal_);
//	//衝突時に呼ばれる関数
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// 法線付き三角形(時計回りが表面)
///// </summary>
//class Triangle : public BaseCollsion
//{
//public:
//
//	//頂点座標3つ
//	AliceMathF::Vector4 p0;
//	AliceMathF::Vector4 p1;
//	AliceMathF::Vector4 p2;
//	//法線ベクトル
//	AliceMathF::Vector4 normal;
//
//public:
//	/// <summary>
//	/// 法線の計算
//	/// </summary>
//	void ComputeNormal();
//
//	//頂点座標1つ目取得
//	const AliceMathF::Vector4& GetP0();
//	//頂点座標1つ目を設定
//	void SetP0(AliceMathF::Vector4& p0_);
//
//	//頂点座標2つ目を取得
//	const AliceMathF::Vector4& GetP1();
//	//頂点座標2つ目を設定
//	void SetP1(AliceMathF::Vector4& p1_);
//
//	//頂点座標3つ目を取得
//	const AliceMathF::Vector4& GetP2();
//	//頂点座標3つ目を設定
//	void SetP2(AliceMathF::Vector4& p2_);
//
//	//法線ベクトルを取得
//	const AliceMathF::Vector4& GetNormal();
//	//法線ベクトルを設定
//	void SetNormal(AliceMathF::Vector4& normal_);
//	//衝突時に呼ばれる関数
//	virtual void OnCollision()
//	{
//	};
//};
//
///// <summary>
///// レイ(半直線)
///// </summary>
//class Ray : public BaseCollsion
//{
//public:
//
//	//始点座標
//	AliceMathF::Vector4 start = { 0,0,0,1 };
//	//方向
//	AliceMathF::Vector4 dir = { 1,0,0,0 };
//
//	//始点座標
//	DirectX::XMVECTOR Xstart = { 0,0,0,1 };
//	//方向
//	DirectX::XMVECTOR Xdir = { 1,0,0,0 };
//
//public:
//
//	//始点座標を取得
//	const AliceMathF::Vector4& GetStart();
//	//始点座標を設定
//	void SetStart(AliceMathF::Vector4& start_);
//
//	//方向を取得
//	const AliceMathF::Vector4& GetDir();
//	//方向を設定
//	void SetDir(AliceMathF::Vector4& dir_);
//	//衝突時に呼ばれる関数
//	virtual void OnCollision()
//	{
//	};
//};
//
//class RayCast : public Ray
//{
//protected:
//	//距離
//	float range = 0.0f;
//private:
//	char PADING[4]{};
//public:
//	//半径を取得
//	const float GetRange();
//	//半径をを設定
//	void SetRange(float range_);
//};
//
//class OBB : public BaseCollsion
//{
//protected:
//	AliceMathF::Vector3 center = {};//位置
//	AliceMathF::Vector3 normaDirect[3];//方向ベクトル
//	float Length[3]{};// 各軸方向の長さ
//private:
//	char PADING[4]{};
//public:
//	const AliceMathF::Vector3 GetDirect(uint16_t elem);//指定軸番号の方向ベクトルを取得
//	const float GetLen(uint16_t elem);// 指定軸方向の長さを取得
//	const AliceMathF::Vector3 GetCenter();// 位置を取得
//	//衝突時に呼ばれる関数
//	virtual void OnCollision()
//	{
//	};
//
//	void CreateOBB(std::vector<PosNormalUv> vertex_, Transform& transform);
//
//	void UpdateOBB(Transform& transform);
//};