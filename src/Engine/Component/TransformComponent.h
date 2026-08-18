#pragma once
#include "pheader.h"
#include "Component.h"

namespace gfx
{
  class TransformComponent
      : public BaseComponent<ComponentType::Transform>
  {
  public:
    void Update();

  private:
    DirectX::XMFLOAT3 m_position;
    DirectX::XMFLOAT3 m_scale;
    DirectX::XMFLOAT3 m_rotate;
  };
} // namespace  gfx
