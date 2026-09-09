#include "core.h"

std::unique_ptr<gfx::World> pWorld;

void Render()
{

  gfx::Renderer::Clear();
  pWorld->Update();

  gfx::ImguiLayer::RenderDefMaterial();


  gfx::Renderer::Present();
}


int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.RenderCallback = Render;

  app.Init(TEXT("normal"));

  gfx::WORLD_DESC desc;
  desc.bEnableSkyBox = true;
  desc.pSkyBoxTexturePath[0] = "assets/texture/skybox/right.jpg";
  desc.pSkyBoxTexturePath[1] = "assets/texture/skybox/left.jpg";
  desc.pSkyBoxTexturePath[2] = "assets/texture/skybox/top.jpg";
  desc.pSkyBoxTexturePath[3] = "assets/texture/skybox/bottom.jpg";
  desc.pSkyBoxTexturePath[4] = "assets/texture/skybox/front.jpg";
  desc.pSkyBoxTexturePath[5] = "assets/texture/skybox/back.jpg";

  desc.pSkyBoxShaderPath[0] = "assets/shader/09normalTex/skyboxV.hlsl";
  desc.pSkyBoxShaderPath[1] = "assets/shader/09normalTex/skyboxP.hlsl";
  pWorld = std::make_unique<gfx::World>(desc);
  pWorld->Create();

  gfx::sShader_desc shaderDesc;
  shaderDesc.VertexPath = "assets/shader/09normalTex/basicV.hlsl";
  shaderDesc.PixelPath = "assets/shader/09normalTex/basicP.hlsl";
  shaderDesc.Type = gfx::VertexType::POS_COLOR_NORMAL_UV;
  gfx::gfxResource::Get().AddShader("basic",shaderDesc);

  shaderDesc.VertexPath =  "assets/shader/09normalTex/normalMapV.hlsl";
  shaderDesc.PixelPath =  "assets/shader/09normalTex/normalMapP.hlsl";
  shaderDesc.Type = gfx::VertexType::POS_COLOR_NORMAL_UV_TANGENT;
  gfx::gfxResource::Get().AddShader("normal",shaderDesc);

#define PLANE_WIDTH  20.0f

  DirectX::XMFLOAT3 cylinderPos[] =
  {
    DirectX::XMFLOAT3{0.0f,1.0f,0.0f},
    DirectX::XMFLOAT3{-PLANE_WIDTH/2.0f,1.1f,PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{PLANE_WIDTH/2.0f,1.1f,PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{PLANE_WIDTH/2.0f,1.1f,-PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{-PLANE_WIDTH/2.0f,1.1f,-PLANE_WIDTH/2.0f},
  };

  std::shared_ptr<gfx::Entity> plane;
  plane = std::make_shared<gfx::Entity>("plane");
  plane->AddComponent<gfx::TransformComponent>(DirectX::XMFLOAT3{ 0.0f,-1.0f,0.0f }, DirectX::XMFLOAT3{ PLANE_WIDTH,1.0f,PLANE_WIDTH });
  plane->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/stones.dds",5.0f);
  plane->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/stones_nmap.dds",
    5.0f,2,gfx::MaterialTextureComponent::eTextureMaterialType::Normal);

  plane->AddComponent<gfx::MeshComponent>(gfx::MeshComponent::eMeshType::Plane);
  plane->AddComponent<gfx::ShaderComponent>("normal");
  pWorld->Add(plane);



  

  app.Run();

  return 0;
}

