#include "pheader.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxTextureCube.h"
#include "gfxLayout.h"
#include "gfxContext.h"
#include "gfxRenderState.h"
#include "Geometry.h"
#include "gfxShaderVertex.h"
#include "gfxShaderPixel.h"
#include "Renderer.h"

namespace gfx
{
  template<typename T>
  class SkyBoxMesh
  {
    public:
      SkyBoxMesh() = default;
      ~SkyBoxMesh() = default;

      SkyBoxMesh(const SkyBoxMesh& rhs) =delete;
      SkyBoxMesh& operator=(const SkyBoxMesh& rhs)= delete;

      void Create(char** skyboxfilePath,char** skyboxShaderPath);
      void Bind();
      void Draw();
    private:
      int m_indexCnt;
      std::unique_ptr<gfxVertexBuffer<T>> m_pVerticesBuffer;
      std::unique_ptr<gfxIndexBuffer> m_pIndexBuffer;
      std::unique_ptr<gfxTextureCube> m_pTexture;
      std::unique_ptr<gfxLayout<T>> m_pLayout;
      std::unique_ptr<gfxShaderVertex> m_pShaderVertex;
      std::unique_ptr<gfxShaderPixel> m_pShaderPixel;
  };

  template <typename T>
  inline void SkyBoxMesh<T>::Create(char** skyboxfilePath,char** skyboxShaderPath)
  {
    GeometrySphere sphere;
    sphere.GenerateSphere();
    m_pVerticesBuffer = std::make_unique<gfxVertexBuffer<T>>();
    m_pVerticesBuffer->Create(sphere.Vertices.size() * sizeof(T),sphere.Vertices.data());

    m_pIndexBuffer = std::make_unique<gfxIndexBuffer>();
    m_pIndexBuffer->Create(sphere.Indices.size(),sphere.Indices.data());
    m_indexCnt = sphere.Indices.size();

    m_pTexture = std::make_unique<gfxTextureCube>();
    m_pTexture->Create(skyboxfilePath);

    m_pShaderVertex = std::make_unique<gfxShaderVertex>();
    m_pShaderVertex->CompileFromFile(skyboxShaderPath[0]);

    m_pShaderPixel =std::make_unique<gfxShaderPixel>();
    m_pShaderPixel->CompileFromFile(skyboxShaderPath[1]);

    m_pLayout = std::make_unique<gfxLayout<T>>();
    m_pLayout->CreateLayout(m_pShaderVertex->GetBlod());

  }

  template <typename T>
  inline void SkyBoxMesh<T>::Bind()
  {
    m_pVerticesBuffer->Bind();
    m_pIndexBuffer->Bind();
    m_pTexture->Bind();
    m_pShaderVertex->Bind();
    m_pShaderPixel->Bind();
  }

  template <typename T>
  inline void SkyBoxMesh<T>::Draw()
  {
    Renderer::DrawIndex(m_indexCnt);
  }
}
