#include "core.h"

gfx::CubeMesh<gfx::VertexPosColorNormalUv> cube;
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
  //cube.Bind();
  //cube.Draw();


  sphere.Bind();
  sphere.Draw();
  gfx::ImguiLayer::Begin("setting");

  gfx::ImguiLayer::End();

  gfx::Renderer::Present();
}


int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.RenderCallback = Render;

  app.Init(TEXT("normal"));



  renderstate.Init();

  renderstate.SetDepthStencilState(gfx::DepthStencilState::LESSEQU);
  renderstate.SetRasteriazerState(gfx::RasterizerState::CullNone);
  //renderstate.SetRasteriazerState(gfx::RasterizerState::WireFrame);
  renderstate.SetSampleState(gfx::SamplerState::LinearWrap);
  constMag.Init();
  camera.Init();

  cube.Create(cubeDesc);


  skybox.Create(skyTexturePath, skyshaderFilePath);
  sphere.Create(sphereDesc);

  cubeShaderLayout.Create("assets/shader/09noramlTex/basicV.hlsl","assets/shader/09noramlTex/basicP.hlsl");
  //skyboxShaderLayout.Create();

  app.Run();

  return 0;
}

