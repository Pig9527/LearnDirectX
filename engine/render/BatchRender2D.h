#include "pheader.h"
#include "Vertex.h"
#include "gfxVertexBuffer.h"
#include "gfxTexture.h"

namespace gfx
{

  template<typename T>
  struct sBatchOriginText
  {
    gfxTexture* pTexture;

    gfxVertexBuffer<T>* pVertices;
    T* pVerticesBuffer;

    T* pBaseVertexBuffer;
    T* pCurrentVertexBuffer;
    uint32_t indexCnt;

  };

  template <typename T>
  class BatchRender2D
  {
  
    public:
  
    static void Init();

    static void Begin();
    static void DrawQuad();
    static void End();

    static void Draw(T* vertices ,int slot = 1,gfxTexture* texture = nullptr);
    

    static std::vector<sBatchOriginText<T>> batchs;
    //static void DrawQuad();
  };


} // namespace gfx
 #include "BatchRender2D.inl"
