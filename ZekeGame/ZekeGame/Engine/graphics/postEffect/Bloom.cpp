#include "stdafx.h"
#include "Bloom.h"
#include "PostEffect.h"

Bloom::Bloom()
{
	//�V�F�[�_�[���������B
	InitShader();
	//�e�탌���_�����O�^�[�Q�b�g�̏������B
	InitRenderTarget();
	//���u�����h�X�e�[�g���������B
	InitAlphaBlendState();
	//�萔�o�b�t�@�̏������B
	InitConstantBuffer();
	//�T���v���X�e�[�g�̏������B
	InitSamplerState();
}


Bloom::~Bloom()
{
	if (m_disableBlendState != nullptr) {
		m_disableBlendState->Release();
	}
	if (m_blurParamCB != nullptr) {
		m_blurParamCB->Release();
	}
	if (m_samplerState != nullptr) {
		m_samplerState->Release();
	}
	if (m_finalBlendState != nullptr) {
		m_finalBlendState->Release();
	}
}
void Bloom::InitConstantBuffer()
{
	//m_cbBlur.Create(&m_blurParam, sizeof(m_blurParam));
	D3D11_BUFFER_DESC desc;

	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = (((sizeof(SBlurParam) - 1) / 16) + 1) * 16;	//16�o�C�g�A���C�����g�ɐ؂肠����B
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.CPUAccessFlags = 0;
	g_graphicsEngine->GetD3DDevice()->CreateBuffer(&desc, NULL, &m_blurParamCB);
}
void Bloom::InitSamplerState()
{
	/*D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	m_samplerState.Create(desc);*/
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	g_graphicsEngine->GetD3DDevice()->CreateSamplerState(&desc, &m_samplerState);
}
void Bloom::InitShader()
{
	m_vsShader.Load("Assets/shader/bloom.fx", "VSMain", Shader::EnType::VS);
	m_psLuminance.Load("Assets/shader/bloom.fx", "PSSamplingLuminance", Shader::EnType::PS);
	m_vsXBlur.Load("Assets/shader/bloom.fx", "VSXBlur", Shader::EnType::VS);
	m_vsYBlur.Load("Assets/shader/bloom.fx", "VSYBlur", Shader::EnType::VS);
	m_psBlur.Load("Assets/shader/bloom.fx", "PSBlur", Shader::EnType::PS);
	m_psCombine.Load("Assets/shader/bloom.fx", "PSCombine", Shader::EnType::PS);
	m_copyVS.Load("Assets/shader/copy.fx", "VSMain", Shader::EnType::VS);
	m_copyPS.Load("Assets/shader/copy.fx", "PSMain", Shader::EnType::PS);
}
void Bloom::InitRenderTarget()
{
	int w = FRAME_BUFFER_W;
	int h = FRAME_BUFFER_H;
	//�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬�B
	DXGI_SAMPLE_DESC multiSampleDesc;
	ZeroMemory(&multiSampleDesc, sizeof(multiSampleDesc));
	multiSampleDesc.Count = 1;
	multiSampleDesc.Quality = 0;
	m_luminanceRT.Create(
		w,
		h,
		DXGI_FORMAT_R16G16B16A16_FLOAT
		);
	//�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬����B
	for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++) {
		int shift = i + 1;
		int baseIndex = i * 2;
		//���u���[�p�B
		m_downSamplingRT[baseIndex].Create(
			w >> shift,
			h >> (shift - 1),
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);
		//�c�u���[�p�B
		m_downSamplingRT[baseIndex + 1].Create(
			w >> shift,
			h >> shift,
			DXGI_FORMAT_R16G16B16A16_FLOAT
		);
		}
	
	//�ڂ��������p�B
	m_combineRT.Create(
		w >> 2,
		h >> 2,
		DXGI_FORMAT_R16G16B16A16_FLOAT
	);
	//m_isEnable = config.bloomConfig.isEnable;

	////�P�x���o�p�̃����_�����O�^�[�Q�b�g���쐬����B
	//m_luminanceRT.Create(
	//	FRAME_BUFFER_W,
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);

	////�u���[�������邽�߂̃_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g���쐬�B
	////���u���[�p�B
	//m_downSamplingRT[0].Create(
	//	FRAME_BUFFER_W * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	FRAME_BUFFER_H,
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);
	////�c�u���[�p�B
	//m_downSamplingRT[1].Create(
	//	FRAME_BUFFER_W * 0.5f,	//���̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	FRAME_BUFFER_H * 0.5f,	//�c�̉𑜓x���t���[���o�b�t�@�̔����ɂ���B
	//	DXGI_FORMAT_R16G16B16A16_FLOAT
	//);
}
void Bloom::InitAlphaBlendState()
{
	CD3D11_DEFAULT defaultSettings;
	//�f�t�H���g�Z�b�e�B���O�ŏ���������B
	CD3D11_BLEND_DESC blendDesc(defaultSettings);
	auto device = g_graphicsEngine->GetD3DDevice();

	device->CreateBlendState(&blendDesc, &m_disableBlendState);

	//�ŏI�����p�̃u�����h�X�e�[�g���쐬����B
	//�ŏI�����͉��Z�����B
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	device->CreateBlendState(&blendDesc, &m_finalBlendState);
}
void Bloom::Update()
{
	float total = 0;
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurDispersion);
		total += 2.0f*m_blurParam.weights[i];

	}
	// �K�i��
	for (int i = 0; i < NUM_WEIGHTS; i++) {
		m_blurParam.weights[i] /= total;
	}
	////�K�E�X�t�B���^�̏d�݂��X�V����B
	//float total = 0;
	//for (int i = 0; i < NUM_WEIGHTS; i++) {
	//	m_blurParam.weights[i] = expf(-0.5f*(float)(i*i) / m_blurDispersion);
	//	total += 2.0f*m_blurParam.weights[i];

	//}
	//// �K�i���B�d�݂̃g�[�^����1.0�ɂȂ�悤�ɁA�S�̂̏d�݂ŏ��Z���Ă���B
	//for (int i = 0; i < NUM_WEIGHTS; i++) {
	//	m_blurParam.weights[i] /= total;
	//}
}

void Bloom::Draw(PostEffect& postEffect)
{
	//rc.PSSetSampler(0, m_samplerState);
	//float clearColor[] = {
	//	0.0f, 0.0f, 0.0f, 0.0f
	//};
	auto deviceContext = g_graphicsEngine->GetD3DDeviceContext();
	deviceContext->PSSetSamplers(0, 1, &m_samplerState);
	float clearColor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//�܂��͋P�x�𒊏o����B
	{
		//���u�����h�𖳌��ɂ���B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
		//�P�x���o�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
		g_graphicsEngine->ChangeRenderTarget(&m_luminanceRT, m_luminanceRT.GetViewport());
		//�����_�����O�^�[�Q�b�g�̃N���A�B
		m_luminanceRT.ClearRenderTarget(clearColor);
			//�V�[�����e�N�X�`���Ƃ���B
		auto mainRTTexSRV = IGameObjectManager().GetMainRenderTarget()->GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &mainRTTexSRV);

		//�t���X�N���[���`��B
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsShader, m_psLuminance);
	}
	//�P�x���ڂ����B
	{
		RenderTarget* prevRt = &m_luminanceRT;
		int rtIndex = 0;
		for (int i = 0; i < NUM_DOWN_SAMPLING_RT / 2; i++) {
			//XBlur
			{
				//	//X�u���[�p�̃����_�����O�^�[�Q�b�g�ɕύX����B
				g_graphicsEngine->ChangeRenderTarget(&m_downSamplingRT[rtIndex], m_downSamplingRT[rtIndex].GetViewport());
				m_blurParam.offset.x = 16.0f / prevRt->GetWidth();
				m_blurParam.offset.y = 0.0f;
				deviceContext->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);
				m_downSamplingRT[rtIndex].ClearRenderTarget(clearColor);
				//rc.ClearRenderTargetView(0, clearColor);
				auto prevSRV = prevRt->GetRenderTargetSRV();
				deviceContext->VSSetShaderResources(0, 1, &prevSRV);
				deviceContext->PSSetShaderResources(0, 1, &prevSRV);
				deviceContext->PSSetConstantBuffers(0, 1, &m_blurParamCB);
				postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsXBlur, m_psBlur);
				//rc.RSSetViewport(0.0f, 0.0f, (float)m_downSamplingRT[rtIndex].GetWidth(), (float)m_downSamplingRT[rtIndex].GetHeight());
			}
			prevRt = &m_downSamplingRT[rtIndex];
			rtIndex++;
			//YBlur
			{
				g_graphicsEngine->ChangeRenderTarget(&m_downSamplingRT[rtIndex], m_downSamplingRT[rtIndex].GetViewport());
				m_blurParam.offset.x = 0.0f;
				//TODO : add some func to bloom shader
				m_blurParam.offset.y = 16.0f / prevRt->GetWidth();
				//
				auto preSRV = prevRt->GetRenderTargetSRV();
				deviceContext->VSSetShaderResources(0, 1, &preSRV);
				deviceContext->PSSetShaderResources(0, 1, &preSRV);
				m_downSamplingRT[rtIndex].ClearRenderTarget(clearColor);
				deviceContext->UpdateSubresource(m_blurParamCB, 0, nullptr, &m_blurParam, 0, 0);
				//�u���[�p�̒萔�o�b�t�@��ݒ肷��B
				deviceContext->PSSetConstantBuffers(0, 1, &m_blurParamCB);
				postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsYBlur, m_psBlur);
			}
			prevRt = &m_downSamplingRT[rtIndex];
			rtIndex++;
		}
	}
	//�{�P�摜�̍쐬�B
	{
		g_graphicsEngine->ChangeRenderTarget(&m_combineRT, m_combineRT.GetViewport());
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);
		m_combineRT.ClearRenderTarget(clearColor);
		auto srv3 = m_downSamplingRT[3].GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &srv3);
		auto srv5 = m_downSamplingRT[3].GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(1, 1, &srv5);
		auto srv7 = m_downSamplingRT[3].GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(2, 1, &srv7);
		auto srv9 = m_downSamplingRT[3].GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(3, 1, &srv9);
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vsShader, m_psCombine);
	}
	//�ŏI�����B
	{
		auto mainRT = IGameObjectManager().GetMainRenderTarget();
		g_graphicsEngine->ChangeRenderTarget(mainRT, mainRT->GetViewport());
		// �A���t�@�u�����f�B���O�����Z�����ɂ���B
		float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
		//rc.OMSetBlendState(AlphaBlendState::add, 0, 0xFFFFFFFF);

		//�萔�o�b�t�@��ݒ肷��B
		auto combineSRV = m_combineRT.GetRenderTargetSRV();
		deviceContext->PSSetShaderResources(0, 1, &combineSRV);
		postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_copyVS, m_copyPS);
		//�A���t�@�u�����f�B���O�����Ƃɖ߂��B
		//rc.OMSetBlendState(AlphaBlendState::trans, 0, 0xFFFFFFFF);
		deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	}
	/*rc.PSUnsetShaderResource(0);
	rc.PSUnsetShaderResource(1);
	rc.PSUnsetShaderResource(2);
	rc.PSUnsetShaderResource(3);*/
}
	

	//	//XY�u���[���������e�N�X�`����t0���W�X�^�ɐݒ肷��B
	//	auto srv = m_downSamplingRT[1].GetRenderTargetSRV();
	//	deviceContext->PSSetShaderResources(0, 1, &srv);

	//	//���Z�����p�̃u�����f�B���O�X�e�[�g��ݒ肷��B
	//	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	//	deviceContext->OMSetBlendState(m_finalBlendState, blendFactor, 0xffffffff);
	//	//�t���X�N���[���`��B
	//	postEffect.DrawFullScreenQuadPrimitive(deviceContext, m_vs, m_psFinal);

	//	//�u�����f�B���O�X�e�[�g��߂��B
	//	deviceContext->OMSetBlendState(m_disableBlendState, blendFactor, 0xffffffff);

	//}

//}