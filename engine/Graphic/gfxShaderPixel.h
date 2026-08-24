#pragma once
#include "gfxShader.h"
namespace gfx
{
  class gfxShaderPixel
      : public gfxShader
  {
  public:
    gfxShaderPixel() = default;
    ~gfxShaderPixel() = default;

    virtual void Compile(const std::string &source) override;
    virtual void CompileFromFile(const std::string &fileName) override;
    void Bind() override;
    void UnBind() override;

  private:
    comptr<ID3D11PixelShader> m_pShader;
  };
} // namespace gfx
