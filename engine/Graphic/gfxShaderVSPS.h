#pragma once

#include "pheader.h"
#include "gfxShaderPixel.h"
#include "gfxShaderVertex.h"
#include "gfxLayout.h"
#include "Vertex.h"

namespace gfx
{

  enum class VertexType
  {
    POS_COLOR,
    POS_COLOR_NORMAL,
    POS_COLOR_NORMAL_UV,
    POS_COLOR_NORMAL_UV_TANGENT,
  };

  struct sShader_desc
  {
    std::string VertexPath;
    std::string PixelPath;
    VertexType Type;
  };

  class gfxShaderVSPS
  {
  public:
    gfxShaderVSPS(const sShader_desc &desc);
    ~gfxShaderVSPS() = default;

    void Ceate();
    void Bind();
    void UnBind();
  private:
    sShader_desc m_desc;
    std::unique_ptr<gfxShader> m_pVertexShader;
    std::unique_ptr<gfxShader> m_pPixelShader;
    std::unique_ptr<gfxLayout<VertexPosColor>> m_pLayoutDefault;
    std::unique_ptr<gfxLayout<VertexPosColorNormal>> m_pLayoutWidthNor;
    std::unique_ptr<gfxLayout<VertexPosColorNormalUv>> m_pLayoutWidthNorUv;
    std::unique_ptr<gfxLayout<VertexPosColorNormalUvTangent>> m_pLayoutWidthNorUvTang;
  };
}
