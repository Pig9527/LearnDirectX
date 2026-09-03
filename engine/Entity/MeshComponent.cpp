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
    m_pVerticesBuffer->Bind();
    m_pIndicesBuffer->Bind();

    Renderer::DrawIndex(m_pIndicesBuffer->GetIndexCount());
  }

  void MeshComponent::OnAttach()
  {
    switch (MeshType)
    {
      case eMeshType::Cube:
      {
         GeometryCube cube;
         cube.GenerateCube(1.0f);
         m_pVerticesBuffer = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
         m_pVerticesBuffer->Create(cube.Vertices.size() * sizeof(VertexPosColorNormalUv),cube.Vertices.data());

         m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
         m_pIndicesBuffer->Create(cube.Indices.size(), cube.Indices.data());
      }
        break;
      case eMeshType::Sphere:
        {
          GeometrySphere sphere;
          sphere.radius = 1.0f;
          sphere.GenerateSphere();
          m_pVerticesBuffer = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
          m_pVerticesBuffer->Create(sphere.Vertices.size() * sizeof(VertexPosColorNormalUv),sphere.Vertices.data());

          m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
          m_pIndicesBuffer->Create(sphere.Indices.size(), sphere.Indices.data());
       }
        break;
      case eMeshType::Cylinder:
      {
        GeometryCylinder cylinder;
        cylinder.Radius = 1.0f;
        cylinder.GenerateCylinder();
        m_pVerticesBuffer = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
        m_pVerticesBuffer->Create(cylinder.Vertices.size() * sizeof(VertexPosColorNormalUv),cylinder.Vertices.data());
        
        m_pIndicesBuffer = std::make_shared<gfxIndexBuffer>();
        m_pIndicesBuffer->Create(cylinder.Indices.size(), cylinder.Indices.data());
      }
      break;
      case eMeshType::Plane:
      {
        GeometryPlane plane;
        //plane.Size = 1.0f;
        plane.GeneratePlane();
        m_pVerticesBuffer = std::make_shared<gfxVertexBuffer<VertexPosColorNormalUv>>();
        m_pVerticesBuffer->Create(plane.Vertices.size() * sizeof(VertexPosColorNormalUv),plane.Vertices.data());

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
