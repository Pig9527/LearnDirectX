#pragma once
#include "pheader.h"
namespace gfx
{
  class gfxWhiteTexture
  {
    public:
      gfxWhiteTexture();
      ~gfxWhiteTexture();
    
      void Create();
      void Bind();
    private:
      int m_width;
      int m_height;
      int m_channels;
      comptr<ID3D11Texture2D> m_ptexture;
      comptr<ID3D11ShaderResourceView> m_pShaderResourceView;
  }; 
} // namespace gfx
