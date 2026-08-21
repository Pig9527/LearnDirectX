#pragma once
#include "pheader.h"
#include "gfxRenderState.h"
namespace gfx
{

  enum class TextureSpace
  {
    Linear,
    SRGB
  };

  struct TextureDesc
  {
    std::string filePath;
    int slot = 1;
    TextureSpace textureSpace = TextureSpace::SRGB;

    bool operator==(const TextureDesc &rhs) const
    {
      return this->filePath == rhs.filePath;
    }
  };

  class gfxTexture
  {
  public:
    gfxTexture(const TextureDesc &textureDesc);
    ~gfxTexture();

    void Create();
    void Bind();

  private:
    std::string m_filePath;
    TextureSpace m_textureSpace;
    bool m_bMipMaps = false;
    int32_t m_Channels;
    int32_t m_width;
    int32_t m_height;
    int m_slot;
    comptr<ID3D11Texture2D> m_pTexture;
    comptr<ID3D11ShaderResourceView> m_pShaderView;
  };
} // namespace gfx
