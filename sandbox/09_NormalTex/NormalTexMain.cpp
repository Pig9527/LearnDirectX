#include "core.h"

//gfx::CubeMesh<gfx::VertexPosColorNormalUv> cube;
gfx::SphereMesh<gfx::VertexPosColorNormalUv> sphere;

gfx::SkyBoxMesh<gfx::VertexPosColorNormalUv> skybox;
gfx::gfxShaderLayoutResouce<gfx::VertexPosColorNormalUv> cubeShaderLayout;
gfx::gfxShaderLayoutResouce<gfx::VertexPosColorNormalUv> skyboxShaderLayout;
gfx::Camera camera;
gfx::gfxConstBufferMag constMag;
gfx::gfxRenderStateCache renderstate;

char* skyTexturePath[] = {
  "assets/texture/skybox/right.jpg",
  "assets/texture/skybox/left.jpg",
  "assets/texture/skybox/top.jpg",
  "assets/texture/skybox/bottom.jpg",
  "assets/texture/skybox/front.jpg",
  "assets/texture/skybox/back.jpg"
};

char* skyshaderFilePath[] = {
  "assets/shader/skybox/skyboxV.hlsl",
  "assets/shader/skybox/skyboxP.hlsl"
};

gfx::sMeshCreateDesc cubeDesc 
{
  
  {L"assets/texture/floor.dds",L"assets/texture/floor_nmap.dds",L"",L""},
};

gfx::sMeshCreateDesc sphereDesc
{
  {L"assets/texture/floor.dds",L"assets/texture/floor_nmap.dds",L"",L""},
  {"assets/texture/awesomeface.png","assets/texture/floor_nmap.dds","",""},
  gfx::eTextureType::other
};

//std::shared_ptr<gfx::Entity> cube;
std::vector<std::shared_ptr<gfx::Entity>> scenes;

void Render()
{

  gfx::Renderer::Clear();

  ImGuiIO& io = ImGui::GetIO();
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
  {
    camera.Rotate(io.MouseDelta.y * 0.01f, io.MouseDelta.x * 0.01f);
  }

  camera.Update(0.16f);

  constMag.SetConstMVP(&camera);
  constMag.Upload2VS();
  constMag.Upload2PS();

  renderstate.SetDepthStencilState(gfx::DepthStencilState::LESSEQU);
  skybox.Bind();
  skybox.Draw();

  renderstate.SetDepthStencilState(gfx::DepthStencilState::Default);
  cubeShaderLayout.Bind();
  gfx::Context::sVertexConstantMVP.World = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f) * DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f));
  constMag.SetConstMVP(&camera);
  constMag.Upload2VS();

  for(auto& entity:scenes)
  {
    auto& transform = entity->GetComponent<gfx::TransformComponent>();
    gfx::Context::sVertexConstantMVP.World = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixTranslation(transform->Position.x,transform->Position.y,transform->Position.z) *
      DirectX::XMMatrixScaling(transform->Scale.x,transform->Scale.y,transform->Scale.z));
    
    constMag.SetConstMVP(&camera);
    constMag.Upload2VS();

    entity->Update();
  }
  //cube->Update();
  // cube.Bind();
  // cube.Draw();


  // gfx::Context::sVertexConstantMVP.World = DirectX::XMMatrixTranspose( DirectX::XMMatrixTranslation(0.0f,2.5f,0.0f) *
  //  DirectX::XMMatrixScaling(1.0f,1.0f,1.0f));
  // constMag.SetConstMVP(&camera);
  // constMag.Upload2VS();
  // sphere.Bind();
  // sphere.Draw();
  gfx::ImguiLayer::Begin("setting");

  gfx::ImguiLayer::End();

  gfx::Renderer::Present();
}


int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.RenderCallback = Render;

  app.Init(TEXT("normal"));
#define PLANE_WIDTH  10.0f

  DirectX::XMFLOAT3 cylinderPos[] =
  {
    DirectX::XMFLOAT3{0.0f,1.0f,0.0f},
    DirectX::XMFLOAT3{-PLANE_WIDTH/2.0f,1.1f,PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{PLANE_WIDTH/2.0f,1.1f,PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{PLANE_WIDTH/2.0f,1.1f,-PLANE_WIDTH/2.0f},
    DirectX::XMFLOAT3{-PLANE_WIDTH/2.0f,1.1f,-PLANE_WIDTH/2.0f},
  };
  
  for (size_t i = 0; i < 5; i++)
  {
    std::shared_ptr<gfx::Entity> sphere;
    sphere = std::make_shared<gfx::Entity>("sphere");
    sphere->AddComponent<gfx::TransformComponent>(DirectX::XMFLOAT3{cylinderPos[i].x,cylinderPos[i].y + 4.0f,cylinderPos[i].z});
    sphere->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/stone.dds");
    sphere->AddComponent<gfx::MeshComponent>(gfx::MeshComponent::eMeshType::Sphere);
    scenes.push_back(sphere);

  }

  for (size_t i = 0; i < 5; i++)
  {
    std::shared_ptr<gfx::Entity> cylinder;
    cylinder = std::make_shared<gfx::Entity>("cylinder");
    cylinder->AddComponent<gfx::TransformComponent>(cylinderPos[i]);
    cylinder->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/stone.dds");
    cylinder->AddComponent<gfx::MeshComponent>(gfx::MeshComponent::eMeshType::Cylinder);
    scenes.push_back(cylinder);
    // std::shared_ptr<gfx::Entity> cube;
    // cube = std::make_shared<gfx::Entity>("cube");
    // cube->AddComponent<gfx::TransformComponent>(DirectX::XMFLOAT3{i * 0.0f,i*0.0f,0.0f});
    // cube->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/floor.dds");
    // cube->AddComponent<gfx::MeshComponent>(gfx::MeshComponent::eMeshType::Cube);

    // scenes.push_back(cube);
  }
  
  std::shared_ptr<gfx::Entity> plane;
  plane = std::make_shared<gfx::Entity>("plane");
  plane->AddComponent<gfx::TransformComponent>(DirectX::XMFLOAT3{0.0f,-1.0f,0.0f},DirectX::XMFLOAT3{PLANE_WIDTH,1.0f,PLANE_WIDTH});
  plane->AddComponent<gfx::MaterialTextureComponent>(L"assets/texture/floor.dds");
  plane->AddComponent<gfx::MeshComponent>(gfx::MeshComponent::eMeshType::Plane);
  scenes.push_back(plane);




  renderstate.Init();

  renderstate.SetDepthStencilState(gfx::DepthStencilState::LESSEQU);
  renderstate.SetRasteriazerState(gfx::RasterizerState::CullNone);
  //renderstate.SetRasteriazerState(gfx::RasterizerState::WireFrame);
  renderstate.SetSampleState(gfx::SamplerState::LinearWrap);
  constMag.Init();
  camera.Init();

 // cube.Create(cubeDesc);


  skybox.Create(skyTexturePath, skyshaderFilePath);
  //sphere.Create(sphereDesc);

  cubeShaderLayout.Create("assets/shader/09noramlTex/basicV.hlsl","assets/shader/09noramlTex/basicP.hlsl");
  //skyboxShaderLayout.Create();

  app.Run();

  return 0;
}

