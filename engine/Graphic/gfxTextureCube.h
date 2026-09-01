#pragma once

#include "pheader.h"

namespace gfx
{
  class gfxTextureCube
  {
    public:
      gfxTextureCube() = default;
      ~gfxTextureCube() = default;
    
      void Create(char** skyStr);
      void Bind();
    private:
      comptr<ID3D11ShaderResourceView> m_shaderResourceViews;
      comptr<ID3D11Texture2D> m_textures;
      std::vector<char*> m_convertRGBAs;
      std::vector<D3D11_SUBRESOURCE_DATA> m_initData;
  };
}
