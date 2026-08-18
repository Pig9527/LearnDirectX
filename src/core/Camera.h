#pragma once
#include "pheader.h"

namespace gfx
{
  class Camera
  {
    public:
      Camera();
      ~Camera();

      void CalculateProjectView();
      DirectX::XMMATRIX& GetProjectVeiwMatrix() {return m_projectViewMatrix;}
      DirectX::XMMATRIX& GetProjectMatrix() {return m_projectMatrix;}
      DirectX::XMMATRIX& GetViewMatrix() {return m_viewMatrix;}
    private:
      DirectX::XMMATRIX m_projectMatrix;
      DirectX::XMMATRIX m_viewMatrix;
      DirectX::XMMATRIX m_projectViewMatrix;
  };
}
