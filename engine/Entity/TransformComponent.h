#pragma once
#include "pheader.h"
#include "Component.h"

namespace gfx
{
  
  class TransformComponent
    :public Component
  {
    public:
    TransformComponent();
    TransformComponent(const DirectX::XMFLOAT3& position);

    TransformComponent(const DirectX::XMFLOAT3& position,const DirectX::XMFLOAT3& scale);

    TransformComponent(const DirectX::XMFLOAT3& position,const DirectX::XMFLOAT3& scale,const DirectX::XMFLOAT3& rotate);
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Scale;
    DirectX::XMFLOAT3 Rotate;
  };
} // namespace gfx
