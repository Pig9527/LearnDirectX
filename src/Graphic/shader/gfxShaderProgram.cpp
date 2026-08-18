#include "gfxShaderProgram.h"
#include "gfxVetexShader.h"
#include "gfxPixelShader.h"

namespace gfx
{
    void gfxShaderProgram::Init(const std::string& vertexPath, const std::string& pixelPath)
    {
      m_pVertxShader = std::make_shared<gfxVertexShader>();
      ShaderCompileOptions option;
      m_pVertxShader->CompileFromFile(vertexPath,option);

      m_pPixelShader = std::make_shared<gfxPixelShader>();
      m_pPixelShader->CompileFromFile(pixelPath, option);
      
    }

    void gfxShaderProgram::Bind()
    {
      m_pVertxShader->Bind();
      m_pPixelShader->Bind();
    }

    void gfxShaderProgram::UnBind()
    {
      m_pVertxShader->UnBind();
      m_pPixelShader->UnBind();
    }

}
