#pragma once
#include "pheader.h"
#include "gfxRenderState.h"
namespace gfx
{

  enum class eTextureType
  {
    DDS,
    other
  };

  class gfxTexture
  {
  public:
    gfxTexture(int slot = 1);
    ~gfxTexture();

    void Create(const std::wstring path, eTextureType type = eTextureType::DDS);
    void Create(const char* path);
    void CreateWihteTexture();
    void Bind();

    comptr<ID3D11Texture2D>& GetTexture(){return m_pTexture;}
    comptr<ID3D11ShaderResourceView>& GetShaderResourceView(){return m_pShaderView;}
  private:
    std::string m_filePath;
    bool m_bMipMaps = false;
    int32_t m_Channels;
    int32_t m_width;
    int32_t m_height;
    int m_slot;
    comptr<ID3D11Texture2D> m_pTexture;
    comptr<ID3D11ShaderResourceView> m_pShaderView;
  };
} // namespace gfx
