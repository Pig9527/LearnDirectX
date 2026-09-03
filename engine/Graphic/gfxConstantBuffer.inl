#include "gfxConstantBuffer.h"
#include "gfxContext.h"

namespace gfx
{
  template<typename T>
  gfxConstantBuffer<T>::gfxConstantBuffer(int slot /*= 1*/)
   :m_Slot(slot)
  {

  }

  template <typename T>
  gfxConstantBuffer<T>::~gfxConstantBuffer()
  {
  }

  template <typename T>
  void gfxConstantBuffer<T>::Create()
  {
    ValidateConstantBufferSize<sizeof(T)>();

    gfxContext& context =gfxContext::Get();
    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    desc.ByteWidth = sizeof(T);
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    context.m_pDevice->CreateBuffer(&desc,nullptr,m_pBuffer.GetAddressOf());
    context.m_pDeviceContext->VSSetConstantBuffers(m_Slot,1,m_pBuffer.GetAddressOf());
  }

  template <typename T>
  void gfxConstantBuffer<T>::Upload(const T &data)
  {
     gfxContext& context =gfxContext::Get();
     D3D11_MAPPED_SUBRESOURCE mapped;
     ZeroMemory(&mapped,sizeof(mapped));
     HR(context.m_pDeviceContext->Map(m_pBuffer.Get(),0,D3D11_MAP_WRITE_DISCARD,0,&mapped));

     memcpy_s(mapped.pData,sizeof(T),&data,sizeof(T));
     context.m_pDeviceContext->Unmap(m_pBuffer.Get(),0);
  }

} // namespace gfx
