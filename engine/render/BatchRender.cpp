#include "BatchRender.h"
#include "Graphic/gfxIndexBuffer.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxTexture.h"
#include "Graphic/gfxConstantBuffer.h"
#include "Graphic/gfxLayout.h"
#include "Renderer.h"

constexpr int QUAD_VERTEX = 4;
constexpr int QUAD_INDICES = 6;
constexpr int QUAD_CNT = 500;

constexpr int MAXVERTEX = QUAD_VERTEX * QUAD_CNT;
constexpr int MAXINDICES = QUAD_INDICES * QUAD_CNT;


namespace gfx
{
 std::vector<sBatchOriginText> BatchRender::batchs;
  struct sBatch
  {
    gfxIndexBuffer indicesBuffer;
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

  void BatchRender::Init()
  {


    //indices
    uint32_t offset = 0;
    uint32_t* indices = new uint32_t[MAXINDICES]();
    for (size_t i = 0; i < QUAD_CNT; i++)
    {
      indices[i *6 +0] = offset + 0;
      indices[i *6 +1] = offset + 1;
      indices[i *6 +2] = offset + 2;

      indices[i *6 +3] = offset + 3;
      indices[i *6 +4] = offset + 4;
      indices[i *6 +5] = offset + 5;
    }
    s_batch.indicesBuffer.Create(MAXINDICES,indices);
    delete indices;

    gfxTexture* white = new gfxTexture();
    white->CreateWihteTexture();
    
    batchs.reserve(32);

    for (uint32_t i = 0; i < 32; i++)
    {
      sBatchOriginText DefaultBatch;

      i== 0 ? DefaultBatch.pTexture = white : DefaultBatch.pTexture = nullptr;

      DefaultBatch.pVertexPosColorBuffer = new VertexPosColor[MAXVERTEX];
      DefaultBatch.pVertexPosColorNormalUvBuffer = new VertexPosColorNormalUv[MAXVERTEX];
      DefaultBatch.pVertexPosColorUv = new VertexPosColorUv[MAXVERTEX];
 
      batchs.push_back(DefaultBatch);
    }
    
  

    // s_batch.pVertexPosColorBuffer = new VertexPosColor[MAXVERTEX];
    // s_batch.pVertexPosColorNormalUvBuffer = new VertexPosColorNormalUv[MAXVERTEX];
    // s_batch.pVertexPosColorUv = new VertexPosColorUv[MAXVERTEX];

    //

  }
  void BatchRender::Begin()
  {

  }
  void BatchRender::DrawQuadNormalUv()
  {
    for (auto& batch : batchs)
    {
      batch.pTexture->Bind();
      batch.vertexPosColorNormalUvObj->Bind();
      Renderer::DrawIndex(batch.indexCnt);
    }
  }
  void BatchRender::End()
  {
    for (auto& batch : batchs)
    {
      batch.vertexPosColorObj = new gfxVertexBuffer<VertexPosColor>();
      int size = (char*)batch.currentPtrPosColor - (char*)batch.basePtrPosColor;
      batch.vertexPosColorObj->Create(size,batch.basePtrPosColor);

      size =  (char*)batch.currentPtrPosColorNormalUv - (char*)batch.currentPtrPosColorNormalUv;
      batch.vertexPosColorNormalUvObj->Create(size,batch.basePtrPosColorNormalUv);

      size = (char*)batch.currentPtrPosColorUv - (char*)batch.basePtrPosColorUv;
      batch.vertexPosColorUvObj->Create(size,batch.basePtrPosColorUv);
    }
    
  }
  void BatchRender::Draw(std::vector<VertexPosColorNormalUv> vertices, gfxTexture *texture)
  {
    for (auto& vertex : vertices)
    {

      for (auto& batch: batchs)
      {
        if(batch.pTexture == texture)
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
  }
}
