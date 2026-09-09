#include "MeshComponent.h"

#include "Geometry/Geometry.h"
#include "Renderer.h"

namespace gfx
{
  MeshComponent::MeshComponent()
    :MeshType(eMeshType::Cube)
    ,MaterialName("Default")
    ,bVisible(true)
    ,bCastShadow(true)
    ,bReceiveShadows(true)
  {}

  MeshComponent::MeshComponent(eMeshType type)
    :MeshType(type)
    ,MaterialName("Default")
    ,bVisible(true)
    ,bCastShadow(true)
    ,bReceiveShadows(true)
  {
  }

  void MeshComponent::Update()
  {
    m_pVerticesBufferNorUvTang->Bind();
    //m_pVertexPosBuffer->Bind();
    //m_pVertexColorBuffer->Bind();
    //m_pVertexNormalBuffer->Bind();
    //m_pVertexTexCoordBuffer->Bind();
    //m_pVertexTangentBuffer->Bind();
    m_pIndicesBuffer->Bind();

    Renderer::DrawIndex(m_pIndicesBuffer->GetIndexCount());
  }

  void MeshComponent::OnAttach()
  {
    switch (MeshType)
    {
      case eMeshType::Cube:
      {
        /*GeometryCube cube;
        cube.GenerateCube(1.0f);
        m_pVerticesBufferNormalUv = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
        m_pVerticesBuffer->Create(cube.Vertices.size() * sizeof(VertexPosColorNormalUv),cube.Vertices.data());

        m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
        m_pIndicesBuffer->Create(cube.Indices.size(), cube.Indices.data());*/
      }
        break;
      case eMeshType::Sphere:
        {
        /*GeometrySphere sphere;
        sphere.radius = 1.0f;
        sphere.GenerateSphere();
        m_pVerticesBufferNormalUv = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
        m_pVerticesBuffer->Create(sphere.Vertices.size() * sizeof(VertexPosColorNormalUv),sphere.Vertices.data());

        m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
        m_pIndicesBuffer->Create(sphere.Indices.size(), sphere.Indices.data());*/
       }
        break;
      case eMeshType::Cylinder:
      {
        /* GeometryCylinder cylinder;
         cylinder.Radius = 1.0f;
         cylinder.GenerateCylinder();
         m_pVerticesBufferNormalUv = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
         m_pVerticesBuffer->Create(cylinder.Vertices.size() * sizeof(VertexPosColorNormalUv),cylinder.Vertices.data());

         m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
         m_pIndicesBuffer->Create(cylinder.Indices.size(), cylinder.Indices.data());*/
      }
      break;
      case eMeshType::Plane:
      {
        GeometryPlane plane;
        //plane.Size = 1.0f;
        plane.GeneratePlane();

        /*  m_pVertexPosBuffer = std::make_shared < gfxVertexBuffer<DirectX::XMFLOAT3>>();
          m_pVertexPosBuffer->Create(plane.VertexPos.size() * sizeof(DirectX::XMFLOAT3), plane.VertexPos.data());

          m_pVertexColorBuffer = std::make_shared<gfxVertexBuffer<DirectX::XMFLOAT4>>();
          m_pVertexColorBuffer->Create(plane.VertexColor.size() * sizeof(DirectX::XMFLOAT4), plane.VertexColor.data(), 1);

          m_pVertexNormalBuffer = std::make_shared<gfxVertexBuffer<DirectX::XMFLOAT3>>();
          m_pVertexNormalBuffer->Create(plane.VertexColor.size() * sizeof(DirectX::XMFLOAT4), plane.VertexNormal.data(), 2);

          m_pVertexTexCoordBuffer = std::make_shared<gfxVertexBuffer<DirectX::XMFLOAT2>>();
          m_pVertexTexCoordBuffer->Create(plane.VertexColor.size() * sizeof(DirectX::XMFLOAT4), plane.VertexTexCoord.data(), 3);

          m_pVertexTangentBuffer = std::make_shared<gfxVertexBuffer<DirectX::XMFLOAT4>>();
          m_pVertexTangentBuffer->Create(plane.VertexColor.size() * sizeof(DirectX::XMFLOAT4), plane.VertexTangent.data(), 4);*/


        m_pVerticesBufferNorUvTang = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUvTangent>>();
        m_pVerticesBufferNorUvTang->Create(plane.Vertices.size() * sizeof(VertexPosColorNormalUvTangent), plane.Vertices.data());

        m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
        m_pIndicesBuffer->Create(plane.Indices.size(), plane.Indices.data());
      }
      break;
      case eMeshType::Coto:
      case eMeshType::Custom:
      break;
    }
  }
}
