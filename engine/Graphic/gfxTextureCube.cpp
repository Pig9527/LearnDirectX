#include "gfxTextureCube.h"
#include "stb_image.h"
#include "gfxContext.h"
namespace gfx
{


  static void ConvertRGBtoRGBA(char* data,int width,int height,char* dest)
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

    void gfxTextureCube::Create(char** skyStr)
    {
      gfxContext& context = gfxContext::Get();
      m_initData.reserve(6);

   
      int width, height, channels;
      // TODO: 内存泄漏
      stbi_uc* data = nullptr;
      for (size_t i = 0; i <= 6 -1; i++)
      {
        data = stbi_load(skyStr[i],&width,&height,&channels,0);
        if (!data)
        {
          continue;
        }
        D3D11_SUBRESOURCE_DATA initData;
        ZeroMemory(&initData,sizeof(initData));
        if(channels == 3)
        {
          char* convertDest = nullptr;
          convertDest = new char[width * height * 4];


          ConvertRGBtoRGBA((char*)data, width, height, convertDest);
          initData.pSysMem = convertDest;
          m_convertRGBAs.push_back(convertDest);
        }
        else
        {
          initData.pSysMem = data;
        }
        initData.SysMemPitch = width * 4;
        initData.SysMemSlicePitch = 0;
        m_initData.push_back(initData);
        
      }
      D3D11_TEXTURE2D_DESC desc;
      ZeroMemory(&desc, sizeof(desc));
      desc.ArraySize = 6;
      desc.MipLevels = 1;
      desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
      desc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;
      desc.Width = width;
      desc.Height = height;
      desc.Usage = D3D11_USAGE_DEFAULT;
      desc.SampleDesc.Count = 1;
      desc.SampleDesc.Quality = 0;
      desc.CPUAccessFlags = 0;

      D3D11_SHADER_RESOURCE_VIEW_DESC sr;
      ZeroMemory(&sr, sizeof(sr));
      sr.Format = desc.Format;
      sr.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
      sr.TextureCube.MipLevels = desc.MipLevels;
      sr.TextureCube.MostDetailedMip = 0;
      HRESULT hr = S_OK;
      hr = context.m_pDevice->CreateTexture2D(&desc, m_initData.data(), m_textures.GetAddressOf());
      hr = context.m_pDevice->CreateShaderResourceView(m_textures.Get(),&sr,m_shaderResourceViews.GetAddressOf());

      //if(convertDest){delete[] convertDest;}

    }
    void gfxTextureCube::Bind()
    {
      gfxContext::Get().m_pDeviceContext->PSSetShaderResources(0,1,m_shaderResourceViews.GetAddressOf());
    }
}
