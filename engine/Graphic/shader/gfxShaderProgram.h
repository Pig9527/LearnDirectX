#pragma once
#include "pheader.h"
#include "gfxContext.h"
#include "gfxShader.h"
namespace  gfx
{
  class gfxShaderProgram
  {
    public:
      gfxShaderProgram() = default;
      ~gfxShaderProgram() = default;

      void Init(const std::string& vertexPath,const std::string& pixelPath);

      void Bind();
      void UnBind();
      std::shared_ptr<gfxShader>& GetVertexShader() { return m_pVertxShader; }
    private:
      std::shared_ptr<gfxShader> m_pVertxShader;
      std::shared_ptr<gfxShader> m_pPixelShader;
      std::string m_name;
  }; 
} // namespace  gfx
