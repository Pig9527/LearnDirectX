#include "pheader.h"
#include "Vertex.h"
#include "gfxVertexBuffer.h"
#include "gfxTexture.h"

namespace gfx
{
  struct sBatchOriginText
  {
    gfxTexture* pTexture;

    gfxVertexBuffer<VertexPosColor>* vertexPosColorObj;
    gfxVertexBuffer<VertexPosColorNormalUv>* vertexPosColorNormalUvObj;
    gfxVertexBuffer<VertexPosColorUv>* vertexPosColorUvObj;


    VertexPosColor* pVertexPosColorBuffer;
    VertexPosColorNormalUv* pVertexPosColorNormalUvBuffer;
    VertexPosColorUv* pVertexPosColorUv;

    VertexPosColor* basePtrPosColor;
    VertexPosColor* currentPtrPosColor;
    VertexPosColorNormalUv* basePtrPosColorNormalUv;
    VertexPosColorNormalUv* currentPtrPosColorNormalUv;
    VertexPosColorUv* basePtrPosColorUv;
    VertexPosColorUv* currentPtrPosColorUv;
    uint32_t indexCnt;

  };

  class BatchRender
  {
  
    public:
  
    static void Init();

    static void Begin();
    static void DrawQuadNormalUv();
    static void End();

    static void Draw(std::vector<VertexPosColorNormalUv> vertices , gfxTexture* texture = nullptr);
    

    static std::vector<sBatchOriginText> batchs;
    //static void DrawQuad();
  };
} // namespace gfx
