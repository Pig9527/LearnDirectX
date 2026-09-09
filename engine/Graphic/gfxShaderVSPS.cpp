#include "gfxShaderVSPS.h"

namespace gfx
{
  gfxShaderVSPS::gfxShaderVSPS(const sShader_desc &desc)
  {
    m_desc = desc;
  }

  void gfxShaderVSPS::Ceate()
  {
    m_pVertexShader = std::make_unique<gfxShaderVertex>();
    m_pVertexShader->CompileFromFile(m_desc.VertexPath);

    m_pPixelShader = std::make_unique<gfxShaderPixel>();
    m_pPixelShader->CompileFromFile(m_desc.PixelPath);

    switch (m_desc.Type)
    {
    case VertexType::POS_COLOR:
      {
        m_pLayoutDefault = std::make_unique<gfxLayout<VertexPosColor>>();
        m_pLayoutDefault->CreateLayout(m_pVertexShader->GetBlod());
      }break;
      case VertexType::POS_COLOR_NORMAL:
      {
        m_pLayoutWidthNor = std::make_unique<gfxLayout<VertexPosColorNormal>>();
        m_pLayoutWidthNor->CreateLayout(m_pVertexShader->GetBlod());
      }break;
      case VertexType::POS_COLOR_NORMAL_UV:
      {
        m_pLayoutWidthNorUv = std::make_unique<gfxLayout<VertexPosColorNormalUv>>();
        m_pLayoutWidthNorUv->CreateLayout(m_pVertexShader->GetBlod());
      }break;
      case VertexType::POS_COLOR_NORMAL_UV_TANGENT:
      {
        m_pLayoutWidthNorUvTang = std::make_unique<gfxLayout<VertexPosColorNormalUvTangent>>();
        m_pLayoutWidthNorUvTang->CreateLayout(m_pVertexShader->GetBlod());
      }break;
    }
  }
  void gfxShaderVSPS::Bind()
  {
    m_pVertexShader->Bind();
    m_pPixelShader->Bind();
  }

  void gfxShaderVSPS::UnBind()
  {
    m_pVertexShader->UnBind();
    m_pPixelShader->UnBind();
  }
}
