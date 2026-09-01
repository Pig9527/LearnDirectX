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
  initSamplerState();
  initDepthStencilState();
  initRasterizerState();
}

void gfx::gfxRenderStateCache::SetRasteriazerState(RasterizerState state)
{
  auto rasterizer = m_rasterizerStateMaps[state];
  if (state == RasterizerState::Invalid)
  {
    gfxContext::Get().m_pDeviceContext->RSSetState(nullptr);
    return;
  }
  gfxContext::Get().m_pDeviceContext->RSSetState(rasterizer.Get());
}

void gfx::gfxRenderStateCache::SetSampleState(SamplerState state,uint32_t slot/*=0*/,uint32_t num /*=1*/)
{
  auto sampler = m_samplerStateMaps[state];
  gfxContext::Get().m_pDeviceContext->PSSetSamplers(slot,num,sampler.GetAddressOf());
}

void gfx::gfxRenderStateCache::SetBlendState(BlendState state)
{
  auto blend = m_blendStateMaps[state];
  UINT mask = 0xffffffff;
  if (state == BlendState::Invalid)
  {
    gfx::gfxContext::Get().m_pDeviceContext->OMSetBlendState(nullptr,nullptr,mask);
    return;
  }
  
  gfxContext::Get().m_pDeviceContext->OMSetBlendState(blend.Get(),nullptr,mask);
}

void gfx::gfxRenderStateCache::SetDepthStencilState(DepthStencilState state)
{
  auto depthStencil = m_depthStencilStateMaps[state];
  gfxContext::Get().m_pDeviceContext->OMSetDepthStencilState(depthStencil.Get(),0);
}

void gfx::gfxRenderStateCache::initBlendState()
{
  gfxContext &context = gfxContext::Get();
  {
    D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
    ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
    renderTargetBlendDesc.BlendEnable = true;
    renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    renderTargetBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;
    renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.IndependentBlendEnable = false;
    blendDesc.RenderTarget[0] = renderTargetBlendDesc;

    comptr<ID3D11BlendState> pBlendState;
    HR(context.m_pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf()));
    m_blendStateMaps[BlendState::Opaque] = pBlendState;
    m_blendStateDescMaps[BlendState::Opaque] = blendDesc;
  }

  {
    D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
    ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
    renderTargetBlendDesc.BlendEnable = true;
    renderTargetBlendDesc.SrcBlend = D3D11_BLEND_ONE;
    renderTargetBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = renderTargetBlendDesc;

    comptr<ID3D11BlendState> pBlendState;
    HR(context.m_pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf()));
    m_blendStateMaps[BlendState::PremulitplineAlpha] = pBlendState;
    m_blendStateDescMaps[BlendState::PremulitplineAlpha] = blendDesc;
  }

  {
    D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
    ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
    renderTargetBlendDesc.BlendEnable = true;
    renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    renderTargetBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = renderTargetBlendDesc;

    comptr<ID3D11BlendState> pBlendState;
    HR(context.m_pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf()));
    m_blendStateMaps[BlendState::NonPremultipliedAlpha] = pBlendState;
    m_blendStateDescMaps[BlendState::NonPremultipliedAlpha] = blendDesc;
  }

  {
    D3D11_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc;
    ZeroMemory(&renderTargetBlendDesc, sizeof(renderTargetBlendDesc));
    renderTargetBlendDesc.BlendEnable = true;
    renderTargetBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    renderTargetBlendDesc.DestBlend = D3D11_BLEND_ONE;
    renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND_ZERO;
    renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND_ONE;
    renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = false;
    blendDesc.RenderTarget[0] = renderTargetBlendDesc;

    comptr<ID3D11BlendState> pBlendState;
    HR(context.m_pDevice->CreateBlendState(&blendDesc, pBlendState.GetAddressOf()));
    m_blendStateMaps[BlendState::Additvie] = pBlendState;
    m_blendStateDescMaps[BlendState::Additvie] = blendDesc;
  }
}

void gfx::gfxRenderStateCache::initSamplerState()
{
  gfxContext &context = gfxContext::Get();
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
    comptr<ID3D11SamplerState> state;
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));

    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
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
    m_samplerStateDescMaps[SamplerState::PointWrap] = desc;
    m_samplerStateMaps[SamplerState::PointWrap] = state;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.MipLODBias = 1;
    desc.MaxAnisotropy = 1;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    m_samplerStateDescMaps[SamplerState::LinearClamp] = desc;
    HR(context.m_pDevice->CreateSamplerState(&desc, pstate.GetAddressOf()));
    m_samplerStateMaps[SamplerState::LinearClamp] = pstate;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MipLODBias = 1;
    desc.MaxAnisotropy = 1;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    m_samplerStateDescMaps[SamplerState::LinearWrap] = desc;
    HR(context.m_pDevice->CreateSamplerState(&desc, pstate.GetAddressOf()));
    m_samplerStateMaps[SamplerState::LinearWrap] = pstate;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_ANISOTROPIC;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    desc.MaxAnisotropy = 16;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    desc.MipLODBias = 0.0f;
    m_samplerStateDescMaps[SamplerState::AnisotropicClamp] = desc;
    HR(context.m_pDevice->CreateSamplerState(&desc, pstate.GetAddressOf()));
    m_samplerStateMaps[SamplerState::AnisotropicClamp] = pstate;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_ANISOTROPIC;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MaxAnisotropy = 16;
    desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    desc.MipLODBias = 0.0f;
    m_samplerStateDescMaps[SamplerState::AnisotropicWrap] = desc;
    HR(context.m_pDevice->CreateSamplerState(&desc, pstate.GetAddressOf()));
    m_samplerStateMaps[SamplerState::AnisotropicWrap] = pstate;
  }

  {
    comptr<ID3D11SamplerState> pstate;
    pstate.Reset();
    D3D11_SAMPLER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    desc.MaxAnisotropy = 16;
    desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
    desc.BorderColor[0] = 0.0f;
    desc.BorderColor[1] = 0.0f;
    desc.BorderColor[2] = 0.0f;
    desc.BorderColor[3] = 0.0f;
    desc.MaxAnisotropy = 0.0f;
    desc.MinLOD = -FLT_MAX;
    desc.MaxLOD = FLT_MAX;
    desc.MipLODBias = 0.0f;
    m_samplerStateDescMaps[SamplerState::ShadowPCF] = desc;
    HR(context.m_pDevice->CreateSamplerState(&desc, pstate.GetAddressOf()));
    m_samplerStateMaps[SamplerState::ShadowPCF] = pstate;
  }
}

void gfx::gfxRenderStateCache::initDepthStencilState()
{
  { 
    comptr<ID3D11DepthStencilState> pdepthStencil;
    D3D11_DEPTH_STENCIL_DESC deptchStencilDesc;
    ZeroMemory(&deptchStencilDesc, sizeof(deptchStencilDesc));
    deptchStencilDesc.DepthEnable = true;
    deptchStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    deptchStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
    deptchStencilDesc.StencilEnable = false;

    HR(gfxContext::Get().m_pDevice->CreateDepthStencilState(&deptchStencilDesc, pdepthStencil.GetAddressOf()));
    m_depthStencilStateDescMaps[DepthStencilState::Default] = deptchStencilDesc;
    m_depthStencilStateMaps[DepthStencilState::Default] = pdepthStencil;
  }
  { 
    comptr<ID3D11DepthStencilState> pdepthStencil;
    D3D11_DEPTH_STENCIL_DESC deptchStencilDesc;
    ZeroMemory(&deptchStencilDesc, sizeof(deptchStencilDesc));
    deptchStencilDesc.DepthEnable = true;
    deptchStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    deptchStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    deptchStencilDesc.StencilEnable = false;
    
    HR(gfxContext::Get().m_pDevice->CreateDepthStencilState(&deptchStencilDesc, pdepthStencil.GetAddressOf()));
    m_depthStencilStateDescMaps[DepthStencilState::LESSEQU] = deptchStencilDesc;
    m_depthStencilStateMaps[DepthStencilState::LESSEQU] = pdepthStencil;
  }


}

void gfx::gfxRenderStateCache::initRasterizerState()
{
  gfxContext &context = gfxContext::Get();
  {
    comptr<ID3D11RasterizerState> pRasterizer;
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    HR(context.m_pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizer.GetAddressOf()));
    m_rasterizerStateDescMaps[RasterizerState::WireFrame] = rasterizerDesc;
    m_rasterizerStateMaps[RasterizerState::WireFrame] = pRasterizer;
  }

  {
    comptr<ID3D11RasterizerState> pRasterizer;
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.CullMode = D3D11_CULL_NONE;
    HR(context.m_pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizer.GetAddressOf()));
    m_rasterizerStateDescMaps[RasterizerState::CullNone] = rasterizerDesc;
    m_rasterizerStateMaps[RasterizerState::CullNone] = pRasterizer;
  }

  {
    comptr<ID3D11RasterizerState> pRasterizer;
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.CullMode = D3D11_CULL_FRONT;
    HR(context.m_pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizer.GetAddressOf()));
    m_rasterizerStateDescMaps[RasterizerState::CullClockwise] = rasterizerDesc;
    m_rasterizerStateMaps[RasterizerState::CullClockwise] = pRasterizer;
  }
  {
    comptr<ID3D11RasterizerState> pRasterizer;
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = true;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 0.0f;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    HR(context.m_pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizer.GetAddressOf()));
    m_rasterizerStateDescMaps[RasterizerState::CullCountClockwise] = rasterizerDesc;
    m_rasterizerStateMaps[RasterizerState::CullCountClockwise] = pRasterizer;
  }

  {
    comptr<ID3D11RasterizerState> pRasterizer;
    D3D11_RASTERIZER_DESC rasterizerDesc;
    ZeroMemory(&rasterizerDesc, sizeof(rasterizerDesc));
    rasterizerDesc.AntialiasedLineEnable = false;
    rasterizerDesc.DepthBias = 0;
    rasterizerDesc.DepthBiasClamp = 0.0f;
    rasterizerDesc.DepthClipEnable = false;
    rasterizerDesc.FillMode = D3D11_FILL_SOLID;
    rasterizerDesc.FrontCounterClockwise = false;
    rasterizerDesc.MultisampleEnable = false;
    rasterizerDesc.ScissorEnable = false;
    rasterizerDesc.SlopeScaledDepthBias = 1.0f;
    rasterizerDesc.CullMode = D3D11_CULL_BACK;
    HR(context.m_pDevice->CreateRasterizerState(&rasterizerDesc, pRasterizer.GetAddressOf()));
    m_rasterizerStateDescMaps[RasterizerState::Pancking] = rasterizerDesc;
    m_rasterizerStateMaps[RasterizerState::Pancking] = pRasterizer;
  }
}
