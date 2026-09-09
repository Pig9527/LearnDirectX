#include "World.h"
#include "Entity/ShaderComponent.h"
#include "imgui/imgui.h"
#include "TransformComponent.h"
#include "MaterialTextureComponent.h"
namespace gfx
{
    World::World(const WORLD_DESC& desc)
      :m_desc(desc)
    {
    }

    void World::Create()
    {
      m_camera.Init();
      if(m_desc.bEnableSkyBox)
      {
        m_pSkybox = std::make_unique<SkyBoxMesh<VertexPosColorNormalUv>>();
        m_pSkybox->Create(m_desc.pSkyBoxTexturePath,m_desc.pSkyBoxShaderPath);
      }
      CONST_BUFFER_DESC_STRUCT desc;
      desc.type = CONST_BUFFER_TYPE::VS;
      desc.slot = 0;
      m_pVertexConstant = std::make_unique<gfxConstantBuffer<sVertexConstant>>(desc);
      m_pVertexConstant->Create();

      // m_pDirectLightConstant = std::make_unique<gfxConstantBuffer<sDirectLight>>();
      // m_pDirectLightConstant->SetSlot(1);
      // m_pDirectLightConstant->Create();

      desc.type = CONST_BUFFER_TYPE::PS;
      desc.slot = 2;
      m_pPixelConstant = std::make_unique<gfxConstantBuffer<sChangeEveryFrame>>(desc);
      m_pPixelConstant->Create();

      m_renderState = std::make_unique<gfxRenderStateCache>();
      m_renderState->Init();
      m_renderState->SetSampleState(SamplerState::LinearWrap);
    }

    void World::Add(std::shared_ptr<Entity> &entity)
    {
        m_entities.push_back(entity);
    }

  void World::Update()
  {
    if (m_desc.bCamera)
    {
      m_camera.Update(1000.0f/60.0f);

      ImGuiIO& io = ImGui::GetIO();
      if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
      {
        m_camera.Rotate(io.MouseDelta.y * 0.01f, io.MouseDelta.x * 0.01f);
      }
    }

    if(m_desc.bEnableSkyBox)
    {
      m_renderState->SetDepthStencilState(DepthStencilState::LESSEQU);
      m_renderState->SetRasteriazerState(RasterizerState::CullNone);
      m_pSkybox->Bind();
      m_pSkybox->Draw();
    }

    std::shared_ptr<gfxShaderVSPS> previous = nullptr;
    m_renderState->SetDepthStencilState(DepthStencilState::Default);

    for (auto &entity : m_entities)
    {
      auto& shaderName = entity->GetComponent<ShaderComponent>();
      auto shader = gfxResource::Get().FindShader(shaderName->Name);
      if (previous != shader)
      {
        previous = shader;
        shader->Bind();
      }

      auto& transform = entity->GetComponent<gfx::TransformComponent>();
      auto& meaterialTex = entity->GetComponent<gfx::MaterialTextureComponent>();
      if (m_desc.bCamera)
      {
        //Context::sVertexConstantMVP.World = DirectX::XMMatrixIdentity();

        Context::sVertexConstantMVP.World =DirectX::XMMatrixTranspose(
          DirectX::XMMatrixTranslation(transform->Position.x, transform->Position.y, transform->Position.z) *
          DirectX::XMMatrixScaling(transform->Scale.x, transform->Scale.y, transform->Scale.z));
        
        Context::sVertexConstantMVP.View = m_camera.GetViewMatrix();
        Context::sVertexConstantMVP.Project = m_camera.GetProjectMatrix();
        Context::sVertexConstantMVP.mvp = Context::sVertexConstantMVP.Project *
          Context::sVertexConstantMVP.View * Context::sVertexConstantMVP.World;
        Context::sVertexConstantMVP.WorldInvTranspose = DirectX::XMMatrixTranspose(
          DirectX::XMMatrixInverse(nullptr,Context::sVertexConstantMVP.World)
        );
        m_pVertexConstant->Upload(Context::sVertexConstantMVP);
      }
      
      if (m_desc.bDirectLight)
      {
        m_everyFrame.eye = m_camera.GetPosition();
        m_everyFrame.viewPorject = m_camera.GetProjectVeiwMatrix();

        memcpy(&m_everyFrame.light.Ambient, &Context::arrDirectLight[0], sizeof(sDirectLight));
        memcpy(&m_everyFrame.pointLight.Ambient,&Context::arrPointLight[0],sizeof(sPointLight));
        m_everyFrame.repeat = meaterialTex->TextureRepeat;
        memcpy(&m_everyFrame.material.Ambient,&Context::arrMaterial[0],sizeof(sMaterial));
        m_pPixelConstant->Upload(m_everyFrame);
      }
      entity->Update();

    }
  }
}
