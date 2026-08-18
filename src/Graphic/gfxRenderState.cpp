#include "gfxRenderState.h"
#include "gfxContext.h"
gfx::gfxRenderStateCache::gfxRenderStateCache()
{
}

gfx::gfxRenderStateCache::~gfxRenderStateCache()
{
}

void gfx::gfxRenderStateCache::Init()
{
  initBlendState();
}

void gfx::gfxRenderStateCache::initBlendState()
{
  gfxContext &context = gfxContext::Get();
  {
    D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
    ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
    renderTargetBlendDesc.BlendEnable = false;
    renderTargetBlendDesc.SrcBlend = D3D11_BLEND_ONE;
    renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.DestBlend = D3D11_BLEND_SRC_ALPHA;
    renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = renderTargetBlendDesc;

    m_blendStateDescMaps[BlendState::Opaque] = blendDesc;

    comptr<ID3D11BlendState> pBlendState;
    HR(context.m_pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf()));
    m_blendStateMaps[BlendState::Opaque] = pBlendState;
  }

  // texture sampler state
  {
    comptr<ID3D11SamplerState> state;
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));

    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.MipLODBias = 0.0f;
    desc.MaxAnisotropy = 1;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    HR(context.m_pDevice->CreateSamplerState(&desc, state.GetAddressOf()));
    m_samplerStateDescMaps[SamplerState::PointClamp] = desc;
    m_samplerStateMaps[SamplerState::PointClamp] = state;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc,sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    desc.MipLODBias = 1;
    m_samplerStateDescMaps[SamplerState::LinearClamp] = desc;
    context.m_pDevice->CreateSamplerState(&desc,pstate.GetAddressOf());
    m_samplerStateMaps[SamplerState::LinearClamp] = pstate;
  }

}
