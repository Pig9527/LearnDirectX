#pragma once
#include "pheader.h"
namespace gfx
{
  class ImguiLayer
  {
    public:
      void Attach();
      void Detach();

      void Render();

      DirectX::XMFLOAT4& GetColor() {return m_color;}
     
      float theta = 0.0f,phi = 0.0f,tx = 0.0f,ty = 0.0f,scale = 1.0f,fov = DirectX::XM_PIDIV2;

      DirectX::XMFLOAT4 ambient = DirectX::XMFLOAT4{0.2,0.5,0.6,1.0};
      DirectX::XMFLOAT4 diffuse = DirectX::XMFLOAT4{0.2,0.5,0.6,1.0};
      DirectX::XMFLOAT4 specular = DirectX::XMFLOAT4{0.2,0.5,0.6,1.0};
      float specularPower = 0.002f;
      DirectX::XMFLOAT3 lightDir = DirectX::XMFLOAT3{0.5f,2.0f,1.0f};
      DirectX::XMFLOAT3 lightColor = DirectX::XMFLOAT3{0.2f,0.3f,0.5f};
      DirectX::XMFLOAT3 eyePos = DirectX::XMFLOAT3{0.2f,0.3f,0.5f};

    private:
      DirectX::XMFLOAT4 m_color= DirectX::XMFLOAT4{0.2,0.5,0.6,1.0};
  };
} // namespace gfx
