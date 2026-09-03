#include "Context.h"

namespace gfx
{
  HWND Context::sHwnd = 0;
  int Context::sWindowWidth = 0;
  int Context::sWindowHeight = 0;
  bool Context::sbRunning = true;
  float Context::sMouseWheel;
  bool Context::sbMButtonDown;
  bool Context::sbMButtonUp;
  float Context::sMouseDownX;
  float Context::sMouseDownY;
  float Context::sMousePosX;
  float Context::sMousePosY;
  DirectX::XMFLOAT2 Context::sMouseLastPos;
  sVertexConstant Context::sVertexConstantMVP;
  sWorldMatrix Context::sWorld;
  sPsLightMaterial Context::sDirectLightConst;
  sTexTell  Context::sTextureTell = {10.0f};
  DirectX::XMFLOAT3 Context::CameraPos = DirectX::XMFLOAT3{0.0f,0.0f,-10.0f};
  DirectX::XMFLOAT3 Context::CameraTarget=DirectX::XMFLOAT3{0.0f,0.0f,0.0f};
  DirectX::XMFLOAT3 Context::CameraUp = DirectX::XMFLOAT3{0.0f,1.0f,0.0f};

  sMaterial  Context::arrMaterial[32] ={
    { 
      DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f },
      DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f },
      DirectX::XMFLOAT4{ 0.5f,0.5f,0.5f,1.0f }
    }

  };
  sDirectLight  Context::arrDirectLight[32] = {
    {
      DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f },
      DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f },
      DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f },
      DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f)
    }
  };
  sSpotLight  Context::arrSpotLight[32];
  sPointLight  Context::arrPointLight[32];

} // namespace gfx
