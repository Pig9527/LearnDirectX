#pragma once
#include "gfxShader.h"
namespace gfx
{
  class gfxPixelShader
      : public gfxShader
  {
  public:
    gfxPixelShader() = default;
    ~gfxPixelShader() = default;

    virtual void Compile(const std::string &source, ShaderCompileOptions &options) override;
    virtual void CompileFromFile(const std::string &fileName,  ShaderCompileOptions &options) override;
    void Bind() override;
    void UnBind() override;

  private:
    comptr<ID3D11PixelShader> m_pShader;
  };
} // namespace gfx
