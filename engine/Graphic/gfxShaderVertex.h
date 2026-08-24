#pragma once
#include "gfxShader.h"
namespace gfx
{



  class gfxShaderVertex
      : public gfxShader
  {
    public:
      gfxShaderVertex() = default;
      ~gfxShaderVertex() = default;

      virtual void Compile(const std::string& source) override;
      virtual void CompileFromFile(const std::string& fileName) override;
      comptr<ID3DBlob>& GetByteBlod() {return m_pByteBlod;}
      void Bind() override;
      void UnBind() override;

    private:
      comptr<ID3D11VertexShader> m_pShader;
  };

} // namespace gfx
