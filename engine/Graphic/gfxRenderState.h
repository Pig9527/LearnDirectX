#pragma once
#include "pheader.h"
namespace gfx
{
  enum class BlendState
  {
    Opaque = 0,
    PremulitplineAlpha,
    NonPremultipliedAlpha,
    Additvie,
    Invalid
  };

  enum class SamplerState
  {
      PointClamp= 0,
      PointWrap,
      LinearClamp,
      LinearWrap,
      AnisotropicClamp,
      AnisotropicWrap,
      ShadowPCF
  };

  enum class RasterizerState
  {
    WireFrame = 0,
    CullNone,
    CullClockwise,
    CullCountClockwise,
    Pancking,
    Invalid
  };

  enum class DepthStencilState
  {
    Default,
    Invalid
  };

  class gfxRenderStateCache
  {
    public:
      gfxRenderStateCache();
      ~gfxRenderStateCache();

      void Init();

      void SetRasteriazerState(RasterizerState state);
      void SetSampleState(SamplerState state,uint32_t slot = 0,uint32_t num = 1);
      void SetBlendState(BlendState state);
      void SetDepthStencilState(DepthStencilState state);
      comptr<ID3D11BlendState>& GetBlendState(BlendState state){return m_blendStateMaps[state];} 
      comptr<ID3D11SamplerState>& GetSampler(SamplerState state){return m_samplerStateMaps[state];} 
      comptr<ID3D11RasterizerState>& GetRasterizerState( RasterizerState state){return m_rasterizerStateMaps[state];} 
      comptr<ID3D11DepthStencilState>& GetDepthStencilState(DepthStencilState state){return m_depthStencilStateMaps[state];} 
    private:
      void initBlendState();
      void initSamplerState();
      void initDepthStencilState();
      void initRasterizerState();
    private:
      std::unordered_map<BlendState,comptr<ID3D11BlendState>> m_blendStateMaps;
      std::unordered_map<BlendState,D3D11_BLEND_DESC> m_blendStateDescMaps;

      std::unordered_map<SamplerState,D3D11_SAMPLER_DESC> m_samplerStateDescMaps;
      std::unordered_map<SamplerState,comptr<ID3D11SamplerState>> m_samplerStateMaps;

      std::unordered_map<RasterizerState,D3D11_RASTERIZER_DESC> m_rasterizerStateDescMaps;
      std::unordered_map<RasterizerState,comptr<ID3D11RasterizerState>> m_rasterizerStateMaps;

      std::unordered_map<DepthStencilState,D3D11_DEPTH_STENCIL_DESC> m_depthStencilStateDescMaps;
      std::unordered_map<DepthStencilState,comptr<ID3D11DepthStencilState>> m_depthStencilStateMaps;
  };
} // namespace gfx
