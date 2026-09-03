#pragma once
#include "pheader.h"
#include "Component.h"
#include "core/Context.h"
#include "gfxConstantBuffer.h"
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
    
    void Update() override;

    void OnAttach() override;

    std::string GetTypeName() const override;
    DirectX::XMFLOAT3 Position;
    DirectX::XMFLOAT3 Scale;
    DirectX::XMFLOAT3 Rotate;
    bool bDirty = false;
    std::shared_ptr<gfxConstantBuffer<sWorldMatrix>> m_pConstantBuffer;
    //gfxConstantBuffer<sWorldMatrix> m_pConstantBuffer;
    
  };
} // namespace gfx
