#include "gfxWhiteTexture.h"
#include "gfxContext.h"
namespace gfx
{
    gfxWhiteTexture::gfxWhiteTexture()
    :m_width(1)
    ,m_height(1)
    ,m_channels(4)
    {
    }

    gfxWhiteTexture::~gfxWhiteTexture()
    {
    }

    void gfxWhiteTexture::Create()
    {
      gfxContext& context = gfxContext::Get();
      D3D11_TEXTURE2D_DESC texDesc;
      ZeroMemory(&texDesc,sizeof(texDesc));
      texDesc.ArraySize = 1;
      texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      texDesc.CPUAccessFlags = 0;
      texDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      texDesc.Width = m_width;
      texDesc.Height = m_height;
      texDesc.MipLevels = 1;
      texDesc.MiscFlags = 0;
      texDesc.SampleDesc.Quality = 0;
      texDesc.SampleDesc.Count = 1;
      texDesc.Usage = D3D11_USAGE_IMMUTABLE;
      uint32_t data = 0xffffffff;

      D3D11_SUBRESOURCE_DATA subdata;
      subdata.pSysMem = &data;
      subdata.SysMemPitch = m_width * sizeof(uint32_t);

      HR(context.m_pDevice->CreateTexture2D(&texDesc,&subdata,m_ptexture.GetAddressOf()));
      HR(context.m_pDevice->CreateShaderResourceView(m_ptexture.Get(),nullptr,m_pShaderResourceView.GetAddressOf()));
    }

    void gfxWhiteTexture::Bind()
    {
      gfxContext::Get().m_pDeviceContext->PSSetShaderResources(0,1,m_pShaderResourceView.GetAddressOf());
    }

} // namespace gfx
