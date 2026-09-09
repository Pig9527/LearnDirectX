#include "RendererSystem.h"
#include "TransformComponent.h"
#include "Renderer.h"

namespace  gfx
{

  struct sRenderSystem
  {
    VertexPosColorNormalUv* pCubeVertexBase;
    VertexPosColorNormalUv* pCubeVertexCurrent;
    uint32_t* m_pCubeIndexBase;
    uint32_t* m_pCubeIndexCurrent;
    VertexPosColorNormalUv* pSpereBase;

  };

  static sRenderSystem system;
  void RendererSystem::Init()
  {
    system.pCubeVertexBase = new VertexPosColorNormalUv[1000]();
    system.m_pCubeIndexBase = new uint32_t[1000]();

    system.pCubeVertexCurrent = system.pCubeVertexBase;
    system.m_pCubeIndexCurrent = system.m_pCubeIndexBase;

    system.pSpereBase = new VertexPosColorNormalUv[10000];

  }

  void RendererSystem::Push(std::shared_ptr<Entity> &entity)
  {
    m_pEntities.push_back(entity);
  }

  void RendererSystem::Begin()
  {
    for (auto& entity: m_pEntities )
    {
      // get cube Mesh
      auto& mesh = entity->GetComponent<CubeMeshComponent>();
      auto& transform = entity->GetComponent<TransformComponent>();

      //vertex transform
      DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(
        DirectX::XMMatrixScaling(transform->Scale.x,transform->Scale.y,transform->Scale.z)*
        DirectX::XMMatrixTranslation(transform->Position.x,transform->Position.y,transform->Position.z)
      );
      for(auto& vertex:mesh->Vertices)
      {
        DirectX::XMVECTOR pos = DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&vertex.position),world);
        DirectX::XMStoreFloat3(&vertex.position,pos);
      }

      //copy vetex data and index data
      int32_t vertexCnt = mesh->Vertices.size();
      int32_t indexCnt = mesh->Indices.size();
      memcpy(system.pCubeVertexCurrent,mesh->Vertices.data(),vertexCnt);
      system.m_pCubeIndexCurrent += vertexCnt;
      
      int offset = 0;
      for (uint32_t i = 0;i<indexCnt; i++)
      {
        mesh->Indices[i]+= offset;
      }
      offset += indexCnt;
      memcpy(system.m_pCubeIndexCurrent,mesh->Indices.data(),indexCnt);
      system.m_pCubeIndexCurrent += indexCnt;
    }
  }

  void RendererSystem::End()
  {

  }
  void RendererSystem::RenderCube()
  {
    uint32_t cnt = (char*)system.m_pCubeIndexCurrent - (char*)system.m_pCubeIndexBase;
    Renderer::DrawIndex(cnt);
  }
} // namespace  gfx
