#include "Camera.h"
#include "Context.h"

gfx::Camera::Camera()
{
  m_projectMatrix = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
      static_cast<float>(Context::sWindowWidth)/static_cast<float>(Context::sWindowHeight),
      1.0f,1000.0f
    ));

    m_viewMatrix = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixLookAtLH(
          DirectX::XMVectorSet(0.0,0.0f,-2.0f,0.0f),
          DirectX::XMVectorSet(0.0,0.0f,0.0f,0.0f),
          DirectX::XMVectorSet(0.0,1.0f,0.0f,0.0f)
      ));
    
    CalculateProjectView();
}

gfx::Camera::~Camera()
{
}

void gfx::Camera::CalculateProjectView()
{
 m_projectViewMatrix = m_projectMatrix * m_viewMatrix;
}
