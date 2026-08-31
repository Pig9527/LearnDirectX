
#include "Graphic/gfxIndexBuffer.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxTexture.h"
#include "Graphic/gfxConstantBuffer.h"
#include "Graphic/gfxLayout.h"
#include "core/Context.h"
#include "Renderer.h"
#include "Graphic/gfxContext.h"


namespace gfx
{
  constexpr int QUAD_VERTEX = 4;
  constexpr int QUAD_INDICES = 6;
  constexpr int QUAD_CNT = 500;

  constexpr int MAXVERTEX = QUAD_VERTEX * QUAD_CNT;
  constexpr int MAXINDICES = QUAD_INDICES * QUAD_CNT;


  template<typename T>
  std::vector<sBatchOriginText<T>> BatchRender2D<T>::batchs;
  struct sBatch
  {
    gfxIndexBuffer indicesBuffer;
    gfxConstantBuffer<sPsLightMaterial> constantBuffer;
    // gfxTexture* arrTesture;

    // uint32_t defTextureIndex = 0;
    // VertexPosColor* pVertexPosColorBuffer;
    // VertexPosColorNormalUv* pVertexPosColorNormalUvBuffer;
    // VertexPosColorUv* pVertexPosColorUv;

    // VertexPosColorNormalUv* basePtrPosColorNormalUv;
    // VertexPosColorNormalUv* currentPtrPosColorNormalUv;
    // uint32_t indexCnt;

  };

  sBatch s_batch;

  template <typename T>
  void BatchRender2D<T>::Init()
  {


    //indices
    uint32_t offset = 0;
    uint32_t* indices = new uint32_t[MAXINDICES]();
    for (size_t i = 0; i < QUAD_CNT; i++)
    {
      indices[i *6 +0] = offset + 0;
      indices[i *6 +1] = offset + 1;
      indices[i *6 +2] = offset + 2;

      indices[i *6 +3] = offset + 2;
      indices[i *6 +4] = offset + 3;
      indices[i *6 +5] = offset + 0;
      offset += 4;
    }
    s_batch.indicesBuffer.Create(MAXINDICES,indices);
    s_batch.indicesBuffer.Bind();
    delete indices;

    gfxTexture* white = new gfxTexture();
    white->CreateWihteTexture();
    
    batchs.reserve(32);

    for (uint32_t i = 0; i < 32; i++)
    {
      sBatchOriginText<T> DefaultBatch;
      ZeroMemory(&DefaultBatch, sizeof(DefaultBatch));
      i== 0 ? DefaultBatch.pTexture = white : DefaultBatch.pTexture = nullptr;

      DefaultBatch.pVerticesBuffer = new T[MAXVERTEX]();
      DefaultBatch.pBaseVertexBuffer = DefaultBatch.pVerticesBuffer;
      DefaultBatch.pCurrentVertexBuffer = DefaultBatch.pBaseVertexBuffer;

      batchs.push_back(DefaultBatch);
    }
    
    s_batch.constantBuffer.Create();
    gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(1,1,s_batch.constantBuffer.GetBuffer().GetAddressOf());
  }
  template <typename T>
  void BatchRender2D<T>::Begin()
  {

  }
  template <typename T>
  void BatchRender2D<T>::DrawQuad()
  {
    sPsLightMaterial material;
    material.material = Context::arrMaterial[0];
    material.directLight = Context::arrDirectLight[0];
    material.eye = DirectX::XMFLOAT3(0.0f,10.0f,-10.0f);
    s_batch.constantBuffer.Upload(material);
    for (auto& batch : batchs)
    {
      if(batch.pTexture == nullptr)
        continue;
      if(batch.indexCnt == 0)
        continue;
      batch.pTexture->Bind();
      batch.pVertices->Bind();
      Renderer::DrawIndex(batch.indexCnt);
    }
  }
  template <typename T>
  void BatchRender2D<T>::End()
  {
    for (auto& batch : batchs)
    {
      //batch.vertexPosColorObj = new gfxVertexBuffer<VertexPosColor>();
      //int size = (char*)batch.currentPtrPosColor - (char*)batch.basePtrPosColor;
      //batch.vertexPosColorObj->Create(size,batch.basePtrPosColor);

      batch.pVertices = new gfxVertexBuffer<T>();
      int  size =  (char*)batch.pCurrentVertexBuffer - (char*)batch.pBaseVertexBuffer;
      if (size == 0)
      {
        continue;
      }
      batch.pVertices->Create(size,batch.pBaseVertexBuffer);

      /*  batch.vertexPosColorUvObj = new gfxVertexBuffer<VertexPosColorUv>();
        size = (char*)batch.currentPtrPosColorUv - (char*)batch.basePtrPosColorUv;
        batch.vertexPosColorUvObj->Create(size,batch.basePtrPosColorUv);*/
    }
    
  }
  template <typename T>
  void BatchRender2D<T>::Draw(T* vertices , int slot /*=1*/, gfxTexture* texture /*=nullptr*/)
  {
    INT vertexSize = sizeof(T);
    batchs[slot].pTexture = texture;
    memcpy(batchs[slot].pCurrentVertexBuffer,vertices,sizeof(T) *4);
    batchs[slot].pCurrentVertexBuffer += 4;
    batchs[slot].indexCnt += 6;
    // for (auto& vertex : vertices)
    // {

    //   batchs[slot].pTexture = texture;
    //   batchs[slot].currentPtrPosColorNormalUv->position = vertex.position;
    //   batchs[slot].currentPtrPosColorNormalUv->color = vertex.color;
    //   batchs[slot].currentPtrPosColorNormalUv->normal = vertex.normal;
    //   batchs[slot].currentPtrPosColorNormalUv->uv = vertex.uv;
    //   batchs[slot].currentPtrPosColorNormalUv++;
    // }
    // batchs[slot].indexCnt += (vertices.size() / 4) * 6;
#if 0
      for (auto& batch : batchs)
      {
        if (batch.pTexture == texture)
        {
          batch.currentPtrPosColorNormalUv->position = vertex.position;
          batch.currentPtrPosColorNormalUv->color = vertex.color;
          batch.currentPtrPosColorNormalUv->normal = vertex.normal;
          batch.currentPtrPosColorNormalUv->uv = vertex.uv;
          batch.currentPtrPosColorNormalUv++;
          batch.indexCnt++;
          break;
        }
        else
        {
          batch.pTexture = texture;
          batch.currentPtrPosColorNormalUv->position = vertex.position;
          batch.currentPtrPosColorNormalUv->color = vertex.color;
          batch.currentPtrPosColorNormalUv->normal = vertex.normal;
          batch.currentPtrPosColorNormalUv->uv = vertex.uv;
          batch.currentPtrPosColorNormalUv++;
          batch.indexCnt++;
          break;
        }



        // if (!texture)
        // {
        //   batchs[0].currentPtrPosColorNormalUv->position = vertex.position;
        //   batchs[0].currentPtrPosColorNormalUv->color = vertex.color;
        //   batchs[0].currentPtrPosColorNormalUv->normal = vertex.normal;
        //   batchs[0].currentPtrPosColorNormalUv->uv = vertex.uv;
        //   batchs[0].currentPtrPosColorNormalUv++;
        //   batchs[0].indexCnt++;
        // }
        // else
        // {


        // }
        // s_batch.currentPtrPosColorNormalUv->position = vertex.position;
        // s_batch.currentPtrPosColorNormalUv->color = vertex.color;
        // s_batch.currentPtrPosColorNormalUv->normal = vertex.normal;
        // s_batch.currentPtrPosColorNormalUv->uv = vertex.uv;
        // s_batch.currentPtrPosColorNormalUv++;
        // s_batch.indexCnt++;
      }
#endif

  }
}
