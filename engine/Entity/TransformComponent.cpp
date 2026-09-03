#include "TransformComponent.h"

namespace gfx
{
  TransformComponent::TransformComponent()
    :Position(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
    ,Scale(DirectX::XMFLOAT3{1.0f,1.0f,1.0f})
    ,Rotate(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
        ,bDirty(true)
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position)
    :Position(position)
    , Scale(DirectX::XMFLOAT3{1.0f,1.0f,1.0f})
    , Rotate(DirectX::XMFLOAT3{0.0f,0.0f,0.0f})
    , bDirty(true)
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &scale)
    :Position(position)
    ,Scale(scale)
    ,Rotate(DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f })
    , bDirty(true)
  {
  }

  TransformComponent::TransformComponent(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &scale, const DirectX::XMFLOAT3 &rotate)
    :Position(position)
    ,Scale(scale)
    ,Rotate(rotate)
    ,bDirty(true)
  {
  }

  void TransformComponent::Update()
  {
#if 0
    if (!bDirty)
    {
      return;
    }
     sWorldMatrix wordlMatrix;
     wordlMatrix.world  = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixScaling(Scale.x,Scale.y,Scale.z)*
      DirectX::XMMatrixRotationRollPitchYaw(Rotate.x,Rotate.y,Rotate.z)*
      DirectX::XMMatrixTranslation(Position.x,Position.y,Position.z)
    );
    wordlMatrix.worldInvTranspose = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixInverse(nullptr,wordlMatrix.world)
    );
    m_pConstantBuffer->Upload(wordlMatrix);
    bDirty = true;
#endif

  }

  void TransformComponent::OnAttach()
  {
#if 0
    m_pConstantBuffer = std::make_shared<gfxConstantBuffer<sWorldMatrix>>(3);
    m_pConstantBuffer->Create();

    //context.m_pDeviceContext->PSSetConstantBuffers(2, 1, m_TexRepeatConstant.GetBuffer().GetAddressOf());
#endif
  }

   std::string TransformComponent::GetTypeName() const
  {
    return "TransformComponent";
  }

}
