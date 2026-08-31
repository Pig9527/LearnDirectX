
#pragma once
#include "pheader.h"

namespace gfx
{

#pragma pack(push,16)

  struct sVertexConstant
  {
    DirectX::XMMATRIX mvp;
    DirectX::XMMATRIX World;
    DirectX::XMMATRIX View;
    DirectX::XMMATRIX Project;
    DirectX::XMMATRIX WorldInvTranspose;
  };

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

  struct sTexTell
  {
    float telling;
    DirectX::XMFLOAT3 pad;
  };
#pragma pack(pop)

  class Context
  {
  public:
    static HWND sHwnd;
    static int sWindowWidth;
    static int sWindowHeight;
    static bool sbRunning;

    static sVertexConstant sVertexConstantMVP;
    static sPsLightMaterial sDirectLightConst;
    static sTexTell sTextureTell;
    static sMaterial arrMaterial[32];
    static sDirectLight arrDirectLight[32];
    static sSpotLight arrSpotLight[32];
    static sPointLight arrPointLight[32];
    static DirectX::XMFLOAT3 CameraTarget;
    static DirectX::XMFLOAT3 CameraPos;
    static DirectX::XMFLOAT3 CameraUp;
  };
}
