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
    private:
      DirectX::XMFLOAT4 m_color= DirectX::XMFLOAT4{0.2,0.5,0.6,1.0};
  };
} // namespace gfx
