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
      ShadwoPCF
  };

  class gfxRenderStateCache
  {
    public:
      gfxRenderStateCache();
      ~gfxRenderStateCache();

      void Init();
      comptr<ID3D11SamplerState>& GetSampler(SamplerState state){return m_samplerStateMaps[state];}
    private:
      void initBlendState();
    private:
      std::unordered_map<BlendState,comptr<ID3D11BlendState>> m_blendStateMaps;
      std::unordered_map<BlendState,D3D11_BLEND_DESC> m_blendStateDescMaps;

      std::unordered_map<SamplerState,D3D11_SAMPLER_DESC> m_samplerStateDescMaps;
      std::unordered_map<SamplerState,comptr<ID3D11SamplerState>> m_samplerStateMaps;
  };
} // namespace gfx
