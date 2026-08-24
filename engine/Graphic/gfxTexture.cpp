#include "gfxTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "gfxContext.h"

static std::vector<char> ConvertRGB2RGBA(char* data,int width,int height)
{
  std::vector<char> rgba(width*height*4);
 for (int i = 0; i < width * height; i++)
  {
    rgba[i * 4 + 0] = data[i * 3 + 0];
    rgba[i * 4 + 1] = data[i * 3 + 1];
    rgba[i * 4 + 2] = data[i * 3 + 2];
    rgba[i * 4 + 3] = 255;
  }
  return rgba;
}

gfx::gfxTexture::gfxTexture(const TextureDesc &textureDesc)
{
  m_filePath = textureDesc.filePath;
  m_slot = textureDesc.slot;
}

gfx::gfxTexture::~gfxTexture()
{
}

void gfx::gfxTexture::Create()
{
  int width,height,channel;
  stbi_uc* data = stbi_load(m_filePath.c_str(),&width,&height,&channel,0);
  if (!data)
  {
    return;
  }
  m_width = width;
  m_height = height;
  m_Channels = channel;

  D3D11_TEXTURE2D_DESC tdc={};
  tdc.ArraySize = 1;
  tdc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  tdc.CPUAccessFlags = 0;
  tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  tdc.Width =width;
  tdc.Height= height;
  tdc.SampleDesc.Count = 1;
  tdc.SampleDesc.Quality = 0;
  tdc.Usage = D3D11_USAGE_IMMUTABLE;
  tdc.MipLevels = 1;
  D3D11_SUBRESOURCE_DATA td = {};
  if(m_Channels == 3)
  {
    td.pSysMem = ConvertRGB2RGBA((char*)data,m_width,m_height).data();
  }
  else
  {
    td.pSysMem = data;
  }

  td.SysMemPitch = width * 4 * sizeof(char);
  
  gfxContext& context = gfxContext::Get();

  HR(context.m_pDevice->CreateTexture2D(&tdc,&td,m_pTexture.GetAddressOf()));
  HR(context.m_pDevice->CreateShaderResourceView(m_pTexture.Get(),nullptr,m_pShaderView.GetAddressOf()));


  stbi_image_free(data);
}

void gfx::gfxTexture::Bind()
{ 
   gfxContext::Get().m_pDeviceContext->PSSetShaderResources(m_slot,1,m_pShaderView.GetAddressOf());
}


