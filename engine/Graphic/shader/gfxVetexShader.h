#pragma once
#include "gfxShader.h"
namespace gfx
{



  class gfxVertexShader
      : public gfxShader
  {
    public:
      gfxVertexShader() = default;
      ~gfxVertexShader() = default;

      virtual void Compile(const std::string& source, ShaderCompileOptions& options) override;
      virtual void CompileFromFile(const std::string& fileName, ShaderCompileOptions& options) override;
      void Bind() override;
      void UnBind() override;

    private:
      comptr<ID3D11VertexShader> m_pShader;
  };

} // namespace gfx
