#include "stdafx.h"
#include "CEffectEngine.h"

CEffectEngine::CEffectEngine()
{
}


CEffectEngine::~CEffectEngine()
{
	for (auto e : m_effectsMap) {
		ES_SAFE_RELEASE(e.second);
	}
	// 先にエフェクト管理用インスタンスを破棄
	m_manager->Destroy();

	// 次に描画用インスタンスを破棄
	m_renderer->Destroy();
}


void CEffectEngine::Init() {
	m_renderer = ::EffekseerRendererDX11::Renderer::Create(g_graphicsEngine->GetD3DDevice(), g_graphicsEngine->GetD3DDeviceContext(), 2000);
	// エフェクト管理用インスタンスの生成
	m_manager = ::Effekseer::Manager::Create(2000);
	m_manager->SetCoordinateSystem(::Effekseer::CoordinateSystem::LH);
	// 描画用インスタンスから描画機能を設定
	m_manager->SetSpriteRenderer(m_renderer->CreateSpriteRenderer());
	m_manager->SetRibbonRenderer(m_renderer->CreateRibbonRenderer());
	m_manager->SetRingRenderer(m_renderer->CreateRingRenderer());
	m_manager->SetTrackRenderer(m_renderer->CreateTrackRenderer());
	m_manager->SetModelRenderer(m_renderer->CreateModelRenderer());

	// 描画用インスタンスからテクスチャの読込機能を設定
	// 独自拡張可能、現在はファイルから読み込んでいる。
	m_manager->SetTextureLoader(m_renderer->CreateTextureLoader());
	m_manager->SetModelLoader(m_renderer->CreateModelLoader());
}

void CEffectEngine::Update() {
	// 視点位置を確定
	CVector3 pos = camera3d->GetPosition();
	m_position = ::Effekseer::Vector3D(pos.x, pos.y, pos.z);

	// カメラ行列を設定
	CVector3 tar = camera3d->GetTarget();
	/*
	g_renderer->SetCameraMatrix(
	::Effekseer::Matrix44().LookAtLH(g_position, ::Effekseer::Vector3D(tar.x, tar.y, tar.z), ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
	*/
	m_renderer->SetCameraMatrix(camera3d->GetViewMatrix());

	// 投影行列を設定
	/*
	g_renderer->SetProjectionMatrix(
	::Effekseer::Matrix44().PerspectiveFovLH(camera3d->GetViewAngle(), camera3d->GetAspect(), 0.1f, 50000.0f));
	*/
	m_renderer->SetProjectionMatrix(camera3d->GetProjectionMatrix());

	m_manager->Update();
}


void CEffectEngine::Draw() {
	m_renderer->BeginRendering();
	m_manager->Draw();
	m_renderer->EndRendering();
}


Effekseer::Effect* CEffectEngine::GetEffect(const wchar_t* filepath) {
	Effekseer::Effect* res = nullptr;
	auto it = m_effectsMap.find(filepath);
	if (it == m_effectsMap.end()) {
		res = Effekseer::Effect::Create(&(g_graphicsEngine->GetEffectEngine().GetEffekseerManager()), (const EFK_CHAR*)filepath);
		m_effectsMap.insert({ filepath, std::move(res)});
	}
	else {
		res = it->second;
	}
	return res;
}