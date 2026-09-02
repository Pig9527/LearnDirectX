#include "pheader.h"
#include "gfxShaderVertex.h"
#include "gfxShaderPixel.h"
#include "gfxLayout.h"
#include "Gemotry.h"
namespace gfx
{

  template <typename T>
  class gfxShaderLayoutResouce
  {
    public:
      gfxShaderLayoutResouce() = default;
      ~gfxShaderLayoutResouce() = default;

      void Create(char* vertexShaderPath,char* pixelShaderPath);
      void Bind();
      
    private:
     std::unique_ptr<gfxShader> m_vertexShader;
     std::unique_ptr<gfxShader> m_pixelShader;
     std::unique_ptr<gfxLayout<T>> m_pLayout;
  };
  template <typename T>
  inline void gfxShaderLayoutResouce<T>::Create(char *vertexShaderPath, char *pixelShaderPath)
  {
    m_vertexShader = std::make_unique<gfxShaderVertex>();
    m_vertexShader->CompileFromFile(vertexShaderPath);
    m_vertexShader->Bind();
    m_pixelShader = std::make_unique<gfxShaderPixel>();
    m_pixelShader->CompileFromFile(pixelShaderPath);
    m_pixelShader->Bind();

    m_pLayout = std::make_unique<gfxLayout<T>>();
    m_pLayout->CreateLayout(m_vertexShader->GetBlod());
  }
  template <typename T>
  inline void gfxShaderLayoutResouce<T>::Bind()
  {
    m_vertexShader->Bind();
    m_pixelShader->Bind();
  }
}
