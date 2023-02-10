#include "GameScene.h"
#include <cassert>
#include <sstream>
#include <iomanip>
#include <imgui.h>

#include"SphereCollider.h"
#include "CollisionManager.h"
#include "Player.h"

#include "MeshCollider.h"
#include "TouchableObject.h"

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	safe_delete(objSkydome);
	safe_delete(objGround);
	safe_delete(objFighter);
	safe_delete(objSphere);
	safe_delete(modelSkydome);
	safe_delete(modelGround);
	safe_delete(modelFighter);
	safe_delete(modelSphere);
	safe_delete(lightGroup);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return ;
	}
	// デバッグテキスト初期化
	debugText = DebugText::GetInstance();
	debugText->Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// パーティクルマネージャ生成
	particleMan = ParticleManager::GetInstance();
	particleMan->SetCamera(camera);

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/tex1.png");

	// ライト生成
	lightGroup = LightGroup::Create();
	// 3Dオブエクトにライトをセット
	Object3d::SetLightGroup(lightGroup);

	// モデル読み込み
	modelSkydome = Model::CreateFromOBJ("skydome");
	modelGround = Model::CreateFromOBJ("Wall");
	modelFighter = Model::CreateFromOBJ("chr_sword", true);
	modelSphere = Model::CreateFromOBJ("sphere", true);

	collisionManager = CollisionManager::GetInstance();


	
	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	//objGround = Object3d::Create(modelGround);
	objGround = TouchableObject::Create(modelGround);
	objGround->SetScale({ 4.0f,2.0f,4.0f });

	objFighter = Player::Create(modelFighter);
	objSphere = Object3d::Create(modelSphere);

	objFighter->SetPosition({ 0, 2, 0 });
	objSphere->SetPosition({ 2, 1, 3 });
	objSphere->SetCollider(new SphereCollider);

	// カメラ注視点をセット
	camera->SetTarget({0, 1, 0});
	camera->SetDistance(5.0f);
	camera->SetEye({ 0,4,-5 });
}

void GameScene::Update()
{
	
	lightGroup->Update();
	camera->SetEye({ 0,4,-5 });
	camera->Update();
	particleMan->Update();

	// オブジェクトの回転
	{
		XMFLOAT3 rot = objSphere->GetRotation();
		rot.y += 1.0f;
		objSphere->SetRotation(rot);
		//objFighter->SetRotation(rot);
	}

	objSkydome->Update();
	objGround->SetRotation({ 0,0,0 });
	objGround->SetScale({ 1.0f,2.0f,1.0f });
	objGround->Update();
	objFighter->Update();
	objSphere->Update();

	//全ての衝突をチェック
	collisionManager->CheckAllCollisions();


}

void GameScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	// 3Dオブジェクトの描画
	Object3d::PreDraw(cmdList);
	objSkydome->Draw();
	objGround->Draw();
	objFighter->Draw();
	objSphere->Draw();
	Object3d::PostDraw();

	// パーティクルの描画
	particleMan->Draw(cmdList);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// デバッグテキストの描画
	debugText->DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}
