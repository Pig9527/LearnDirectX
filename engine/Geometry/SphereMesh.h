
#include "pheader.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxTexture.h"
#include "gfxLayout.h"
#include "gfxContext.h"
#include "gfxRenderState.h"
#include "Geometry.h"
#include "Renderer.h"
#include "mesh.h"
namespace gfx
{

  template<typename T>
  class SphereMesh
  {
    public:
    SphereMesh() = default;
    ~SphereMesh() = default;

    SphereMesh(const SphereMesh& rhs) =delete;
    SphereMesh& operator=(const SphereMesh& rhs)= delete;

    void Create(sMeshCreateDesc& meshDesc);
    void Bind();
    void Draw();

    private:
     std::unique_ptr<gfxVertexBuffer<T>> m_pVerticesBuffer;
     std::unique_ptr<gfxIndexBuffer> m_pIndexBuffer;
     std::unique_ptr<gfxTexture> m_pTexture;
     int m_indexCnt;
  };

  template <typename T>
  inline void SphereMesh<T>::Create(sMeshCreateDesc& meshDesc)
  {
    GeometrySphere sphere;
    sphere.Create();
    m_pVerticesBuffer = std::make_unique<gfxVertexBuffer<T>>();
    m_pVerticesBuffer->Create(sphere.Verteices.size() * sizeof(T), sphere.Verteices.data());

    m_pIndexBuffer = std::make_unique<gfxIndexBuffer>();
    m_pIndexBuffer->Create(sphere.Indices.size(), sphere.Indices.data());
    m_indexCnt = sphere.Indices.size();

    
    m_pTexture = std::make_unique<gfxTexture>();
    if (meshDesc.type == eTextureType::DDS)
    {
      m_pTexture->Create(meshDesc.wTexFilePath[0]);
    }
    else
    {
      m_pTexture->Create(meshDesc.texFilePath[0]);
    }
  }

  template <typename T>
  inline void SphereMesh<T>::Bind()
  {
    m_pVerticesBuffer->Bind();
    m_pIndexBuffer->Bind();
    m_pTexture->Bind();
  }
  template <typename T>
  inline void SphereMesh<T>::Draw()
  {
    Renderer::DrawIndex(m_indexCnt);
  }
}
