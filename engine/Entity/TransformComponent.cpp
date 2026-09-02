#include "TransformComponent.h"

namespace gfx
{
  TransformComponent::TransformComponent()
    :Position(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
    ,Scale(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
    ,Rotate(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position)
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &scale)
    :Position(position)
    ,Scale(scale)
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &scale, const DirectX::XMFLOAT3 &rotate)
    :Position(position)
    ,Scale(scale)
    ,Rotate(rotate)
  {
  }

}