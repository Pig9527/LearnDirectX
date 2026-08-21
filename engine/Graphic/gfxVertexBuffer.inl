#include "gfxVertexBuffer.h"
#include "gfxContext.h"
#include "Geometry.h"

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
  gfxContext::Get().m_pDeviceContext->IASetVertexBuffers(0,1,m_pBuffer.GetAddressOf(),&stride,&offset);
}
