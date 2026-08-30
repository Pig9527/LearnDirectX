
#pragma once
#include "pheader.h"

namespace gfx
{
  struct sMaterial
  {
    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;
    DirectX::XMFLOAT4 Reflect;
  };

  struct sDirectLight
  {
    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;
    DirectX::XMFLOAT3 Direction;
    float pad;
  };

  struct sSpotLight
  {
    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;

    DirectX::XMFLOAT3 Position;
    float Range;
    DirectX::XMFLOAT3 Direction;
    float Spot;
    DirectX::XMFLOAT3 Att;
    float pad;
  };
  struct sPointLight
  {
    DirectX::XMFLOAT4 Ambient;
    DirectX::XMFLOAT4 Diffuse;
    DirectX::XMFLOAT4 Specular;
    
    DirectX::XMFLOAT3 Position;
    float Range;
    DirectX::XMFLOAT3 Att;
    float pad;
  };

  struct sPsLightMaterial
  {
    sMaterial material;
    sDirectLight directLight;
    DirectX::XMFLOAT3 eye;
    float pad;
  };

  class Context
  {
  public:
    static HWND sHwnd;
    static int sWindowWidth;
    static int sWindowHeight;
    static bool sbRunning;

    static sMaterial arrMaterial[32];
    static sDirectLight arrDirectLight[32];
    static sSpotLight arrSpotLight[32];
    static sPointLight arrPointLight[32];

  };
}
