#include "gfxTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"
#include "gfxContext.h"

void gfx::gfxTexture::Create()
{
  int width,height,channel;
  stbi_uc* data = stbi_load(m_filePath.c_str(),&width,&height,&channel,0);
  if (!data)
  {
    m_width = 1;
    m_height = 1;
    m_Channels = 4;

    D3D11_TEXTURE2D_DESC tdc = {};
    tdc.ArraySize = 1;
    tdc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    tdc.CPUAccessFlags = 0;
    //m_Channels == 3 ? tdc.Format = DXGI_FORMAT_R8G8B8_UNORM : tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    tdc.Width = m_width;
    tdc.Height = m_height;
    tdc.SampleDesc.Count = 1;
    tdc.SampleDesc.Quality = 0;
    tdc.Usage = D3D11_USAGE_IMMUTABLE;
    tdc.MipLevels = 1;

    uint32_t data = 0xffffffff;

    D3D11_SUBRESOURCE_DATA td = {};
    td.pSysMem = &data;
    td.SysMemPitch = m_width * 4 * sizeof(char);

    gfxContext& context = gfxContext::Get();

    HR(context.m_pDevice->CreateTexture2D(&tdc, &td, m_pTexture.GetAddressOf()));
    HR(context.m_pDevice->CreateShaderResourceView(m_pTexture.Get(), nullptr, m_pShaderView.GetAddressOf()));

    context.m_pDeviceContext->PSSetShaderResources(0, 1, m_pShaderView.GetAddressOf());
    return;
  }
  m_width = width;
  m_height = height;
  m_Channels = channel;

  D3D11_TEXTURE2D_DESC tdc={};
  tdc.ArraySize = 1;
  tdc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  tdc.CPUAccessFlags = 0;
  //m_Channels == 3 ? tdc.Format = DXGI_FORMAT_R8G8B8_UNORM : tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
  tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  tdc.Width =width;
  tdc.Height= height;
  tdc.SampleDesc.Count = 1;
  tdc.SampleDesc.Quality = 0;
  tdc.Usage = D3D11_USAGE_IMMUTABLE;
  tdc.MipLevels = 1;
  D3D11_SUBRESOURCE_DATA td = {};
    std::vector<uint8_t> rgbadata(m_width * m_height * 4);
    for (int i = 0; i < width * height; i++)
    {
      rgbadata[i * 4 + 0] = data[i * 3 + 0];
      rgbadata[i * 4 + 1] = data[i * 3 + 1];
      rgbadata[i * 4 + 2] = data[i * 3 + 2];
      rgbadata[i * 4 + 3] = 255;
    }

    td.pSysMem = rgbadata.data();
    td.SysMemPitch = width * 4 * sizeof(char);



  
  gfxContext& context = gfxContext::Get();

  HR(context.m_pDevice->CreateTexture2D(&tdc,&td,m_pTexture.GetAddressOf()));
  HR(context.m_pDevice->CreateShaderResourceView(m_pTexture.Get(),nullptr,m_pShaderView.GetAddressOf()));

  context.m_pDeviceContext->PSSetShaderResources(0,1,m_pShaderView.GetAddressOf());
  stbi_image_free(data);
}

gfx::gfxTexture::gfxTexture(const TextureDesc &textureDesc)
{
  m_filePath = textureDesc.filePath;

}

gfx::gfxTexture::~gfxTexture()
{
}
