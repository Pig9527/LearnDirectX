#pragma once
#include "pheader.h"
#include "gfxContext.h"
#include "Vertex.h"
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
template<typename T>
void gfx::gfxVertexBuffer<T>::Create(uint32_t size, T*data,uint32_t slot /*=0*/)
{
  m_slot = slot;
  gfxContext& context = gfxContext::Get();
  D3D11_BUFFER_DESC desc = {};
  desc.ByteWidth = size;
  desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  desc.CPUAccessFlags = 0;
  desc.MiscFlags = 0;
  desc.Usage = D3D11_USAGE_IMMUTABLE;
  D3D11_SUBRESOURCE_DATA db = {};
  db.pSysMem = static_cast<void*>(data);
  HR(context.m_pDevice->CreateBuffer(&desc,&db,m_pBuffer.GetAddressOf()));

}

template<typename T>
void gfx::gfxVertexBuffer<T>::Bind()
{
  UINT stride = sizeof(T);
  UINT offset = 0;
  gfxContext::Get().m_pDeviceContext->IASetVertexBuffers(m_slot,1,m_pBuffer.GetAddressOf(),&stride,&offset);
}

