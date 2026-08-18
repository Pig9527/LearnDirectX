#pragma once
#include "pheader.h"
#include "gfxShader.h"
namespace gfx
{
  template<typename T>
  class gfxLayout
  {
    public:

    gfxLayout() = default;
    ~gfxLayout() = default;

    void CreateLayout(const comptr<ID3DBlob>& blod);
    
    private:
      comptr<ID3D11InputLayout> m_pLayout;
  };
  

  template <typename T>
  void gfxLayout<T>::CreateLayout(const comptr<ID3DBlob>& blod)
  {
    uint32_t num = T::sLayoutNum;
    D3D11_INPUT_ELEMENT_DESC* desc = T::sLayout;
    HRESULT hr = gfxContext::Get().m_pDevice->CreateInputLayout(desc, num, blod->GetBufferPointer(), blod->GetBufferSize(), m_pLayout.GetAddressOf());

    gfxContext::Get().m_pDeviceContext->IASetInputLayout(m_pLayout.Get());

    gfxContext::Get().m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  }
}
