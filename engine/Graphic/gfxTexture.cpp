#include "gfxTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "gfxContext.h"
#include "DDSTextureLoader11.h"

static void ConvertRGB2RGBA(char* data,int width,int height,char* dest)
{
  //std::vector<char> rgba(width*height*4);
  for (int i = 0; i < width * height; i++)
  {
    dest[i * 4 + 0] = data[i * 3 + 0];
    dest[i * 4 + 1] = data[i * 3 + 1];
    dest[i * 4 + 2] = data[i * 3 + 2];
    dest[i * 4 + 3] = 255;
  }
}

gfx::gfxTexture::gfxTexture(int slot /*= 1*/)
{
  m_slot = slot;
}

gfx::gfxTexture::~gfxTexture()
{
}

void gfx::gfxTexture::Create(const std::wstring path, eTextureType type /*= eTextureType::DDS*/)
{

  HRESULT hr = S_OK;
  if (type == eTextureType::DDS)
  {
    gfxContext& context = gfx::gfxContext::Get();
    hr = DirectX::CreateDDSTextureFromFile(context.m_pDevice.Get(),path.c_str(),nullptr,m_pShaderView.GetAddressOf());
  }
}

void gfx::gfxTexture::Create(const char* path)
{
  int width, height, channel;
  m_filePath = path;
  stbi_uc* data = stbi_load(m_filePath.c_str(), &width, &height, &channel, 0);
  if (!data)
  {
    return;
  }
  m_width = width;
  m_height = height;
  m_Channels = channel;

  D3D11_TEXTURE2D_DESC tdc = {};
  tdc.ArraySize = 1;
  tdc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
  tdc.CPUAccessFlags = 0;
  tdc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  tdc.Width = width;
  tdc.Height = height;
  tdc.SampleDesc.Count = 1;
  tdc.SampleDesc.Quality = 0;
  tdc.Usage = D3D11_USAGE_IMMUTABLE;
  tdc.MipLevels = 1;
  D3D11_SUBRESOURCE_DATA td = {};
  char* convertDest = nullptr;
  if (m_Channels == 3)
  {
    char* convertDest = new char[m_width * m_height * 4];
    ConvertRGB2RGBA((char*)data, m_width, m_height, convertDest);
    td.pSysMem = convertDest;
  }
  else
  {
    td.pSysMem = data;
  }

  td.SysMemPitch = width * 4 * sizeof(char);

  gfxContext& context = gfxContext::Get();

  HR(context.m_pDevice->CreateTexture2D(&tdc, &td, m_pTexture.GetAddressOf()));
  HR(context.m_pDevice->CreateShaderResourceView(m_pTexture.Get(), nullptr, m_pShaderView.GetAddressOf()));

  if (convertDest) { delete[] convertDest; }
  stbi_image_free(data);
}

void gfx::gfxTexture::CreateWihteTexture()
{
  m_width = 1;
  m_height = 1;
  m_Channels = 4;
  gfxContext& context = gfxContext::Get();
  D3D11_TEXTURE2D_DESC texDesc;
  ZeroMemory(&texDesc, sizeof(texDesc));
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
  HR(context.m_pDevice->CreateTexture2D(&texDesc, &subdata, m_pTexture.GetAddressOf()));
  HR(context.m_pDevice->CreateShaderResourceView(m_pTexture.Get(), nullptr, m_pShaderView.GetAddressOf()));
}

void gfx::gfxTexture::Bind()
{ 
   gfxContext::Get().m_pDeviceContext->PSSetShaderResources(m_slot,1,m_pShaderView.GetAddressOf());
}


