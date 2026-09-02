
#include "pheader.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxTexture.h"
#include "gfxLayout.h"
#include "gfxContext.h"
#include "gfxRenderState.h"
#include "Gemotry.h"
#include "Renderer.h"
#include "mesh.h"

namespace gfx
{
  template<typename T>
  class CubeMesh
  {
    public:
    CubeMesh() = default;
    ~CubeMesh() = default;

    CubeMesh(const CubeMesh& rhs) =delete;
    CubeMesh& operator=(const CubeMesh& rhs)= delete;

    void Create(const sMeshCreateDesc& meshDesc);
    void Bind();
    void Draw();

    private:
     std::unique_ptr<gfxVertexBuffer<T>> m_pVerticesBuffer;
     std::unique_ptr<gfxIndexBuffer> m_pIndexBuffer;
     std::unique_ptr<gfxTexture> m_pTexture;
     std::unique_ptr<gfxTexture> m_pNormalTexture;
     std::unique_ptr<gfxTexture> m_pDiffuseTexture;
     std::unique_ptr<gfxTexture> m_pSpecularTexture;
     int m_indexCnt;
  };

  template <typename T>
  inline void CubeMesh<T>::Create(const sMeshCreateDesc& meshDesc)
  {
    GemotryCube cube;
    cube.Create(2.0f);
    m_pVerticesBuffer = std::make_unique<gfxVertexBuffer<T>>();
    int sie = sizeof(T);
    int s = sizeof(VertexPosColorNormalUv);
    m_pVerticesBuffer->Create(cube.Vertices.size() * sizeof(T),cube.Vertices.data());

    m_pIndexBuffer = std::make_unique<gfxIndexBuffer>();
    m_pIndexBuffer->Create(cube.Indices.size(),cube.Indices.data());

    m_indexCnt = cube.Indices.size();

    m_pTexture = std::make_unique<gfxTexture>();
    if (meshDesc.type == eTextureType::DDS)
    {
      m_pTexture->Create(meshDesc.wTexFilePath[0]);
    }
    else
    {
      m_pTexture->Create(meshDesc.texFilePath[0]);
    }

    m_pNormalTexture = std::make_unique<gfxTexture>(2);
    m_pNormalTexture->Create(meshDesc.wTexFilePath[1]);

  }

  template <typename T>
  inline void CubeMesh<T>::Bind()
  {
    m_pVerticesBuffer->Bind();
    m_pIndexBuffer->Bind();
    m_pTexture->Bind();
    m_pNormalTexture->Bind();
  }
  template <typename T>
  inline void CubeMesh<T>::Draw()
  {
    Renderer::DrawIndex(m_indexCnt);
  }
}
