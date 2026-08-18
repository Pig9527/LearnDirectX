#pragma once
#include "pheader.h"
namespace gfx
{

  struct VertexBufferPos
  {
    static constexpr uint32_t POS = 0;
    static constexpr uint32_t COLOR = 1;
    static constexpr uint32_t NORMAL = 2;
    static constexpr uint32_t TEXCOORD = 3;
    static constexpr uint32_t TARGETS = 4;
  };

  template<typename T>
  class gfxVertexBuffer
  {
    public:

      void Create(uint32_t size, T* data,uint32_t slot = 0);
      void Bind();
      inline comptr<ID3D11Buffer>& GetBuffer(){return m_pBuffer;}
    private:
      uint32_t m_slot = 0;
      uint32_t m_stride = 0;
      comptr<ID3D11Buffer> m_pBuffer;
  };
} // namespace gfx
#include "gfxVertexBuffer.inl"
