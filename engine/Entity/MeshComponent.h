#pragma once
#include "pheader.h"
#include "Component.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"

namespace gfx
{

  class MeshComponent
      : public Component
  {
  public:
    enum class eMeshType
    {
      Cube,
      Sphere,
      Cylinder,
      Plane,
      Coto,
      Custom
    };

    MeshComponent();
    explicit MeshComponent(eMeshType type);


    void Update() override;
    void OnAttach() override;

    eMeshType MeshType;
    std::string MaterialName;
    bool bVisible;
    bool bCastShadow;
    bool bReceiveShadows;

    std::shared_ptr<gfxVertexBuffer<VertexPosColorNormalUvTangent>> m_pVerticesBufferNorUvTang;
    std::shared_ptr<gfxVertexBuffer<VertexPosColorNormalUv>> m_pVerticesBufferNormalUv;
    std::shared_ptr<gfxVertexBuffer<DirectX::XMFLOAT3>> m_pVertexPosBuffer;
    std::shared_ptr<gfxVertexBuffer<DirectX::XMFLOAT4>> m_pVertexColorBuffer;
    std::shared_ptr<gfxVertexBuffer<DirectX::XMFLOAT3>> m_pVertexNormalBuffer;
    std::shared_ptr<gfxVertexBuffer<DirectX::XMFLOAT2>> m_pVertexTexCoordBuffer;
    std::shared_ptr<gfxVertexBuffer<DirectX::XMFLOAT4>> m_pVertexTangentBuffer;
    std::shared_ptr<gfxIndexBuffer> m_pIndicesBuffer;
  };
}
