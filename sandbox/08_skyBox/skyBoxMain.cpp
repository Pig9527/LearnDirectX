#include "core.h"
#include "Graphic/gfxTextureCube.h"

gfx::Camera camera;
gfx::gfxConstBufferMag constMag;

gfx::gfxIndexBuffer skyIndicesBuffer;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> skyVerticesBuffer;
gfx::gfxTextureCube skyTexCube;
gfx::gfxTextureCube skydaylightTexCube;
gfx::gfxTextureCube skysunlightTexCube;
gfx::gfxShaderVertex vertexShader;
gfx::gfxShaderPixel pixelShader;
gfx::gfxLayout<gfx::VertexPosColorNormalUv> skyinputlayout;

gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> cubeVerticesBuffer;
gfx::gfxIndexBuffer cubeIndexBuffer;
gfx::gfxShaderVertex DefvertexShader;
gfx::gfxShaderPixel DefpixelShader;
gfx::gfxTexture cubeTexture;
gfx::gfxLayout<gfx::VertexPosColorNormalUv> cubeinputlayout;

gfx::gfxRenderStateCache renderState;
int sphereSkyIndexCnt = 0;

char* skydaylightTexturePath[] = {
  "assets/texture/skybox/daylight0.png",
  "assets/texture/skybox/daylight1.png",
  "assets/texture/skybox/daylight2.png",
  "assets/texture/skybox/daylight3.png",
  "assets/texture/skybox/daylight4.png",
  "assets/texture/skybox/daylight5.png"
};

char* skyTexturePath[] = {
  "assets/texture/skybox/right.jpg",
  "assets/texture/skybox/left.jpg",
  "assets/texture/skybox/top.jpg",
  "assets/texture/skybox/bottom.jpg",
  "assets/texture/skybox/front.jpg",
  "assets/texture/skybox/back.jpg"
};

char* skysunTexturePath[] = {
  "assets/texture/skybox/sunset_posX.bmp",
  "assets/texture/skybox/sunset_negX.bmp",
  "assets/texture/skybox/sunset_posY.bmp",
  "assets/texture/skybox/sunset_negY.bmp",
  "assets/texture/skybox/sunset_posZ.bmp",
  "assets/texture/skybox/sunset_negZ.bmp"
};

  char* combstr[] ={"skybox1","skybox2","sun"};
  int currentSky = 0;
gfx::gfxTexture* textObj[6] = {};

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

  renderState.SetDepthStencilState(gfx::DepthStencilState::LESSEQU);
  //renderState.SetRasteriazerState(gfx::RasterizerState::WireFrame);
  vertexShader.Bind();
  pixelShader.Bind();
  skyVerticesBuffer.Bind();
  skyIndicesBuffer.Bind();
  if(currentSky == 0)   skyTexCube.Bind();
  else if(currentSky == 1) skydaylightTexCube.Bind();
  else if(currentSky == 2) skysunlightTexCube.Bind();

  gfx::Renderer::DrawIndex(sphereSkyIndexCnt);

  renderState.SetDepthStencilState(gfx::DepthStencilState::Default);
  DefvertexShader.Bind();
  DefpixelShader.Bind();
  cubeVerticesBuffer.Bind();
  cubeIndexBuffer.Bind();
  cubeTexture.Bind();
  gfx::Renderer::DrawIndex(36);

  gfx::ImguiLayer::Begin("setting");


  ImGui::Combo("shybox",&currentSky,combstr,ARRAYSIZE(combstr));
  gfx::ImguiLayer::End();

  gfx::Renderer::Present();
}

// void LoadSkyBox()
// {

//   gfx::gfxContext& context = gfx::gfxContext::Get();
//   {
//     size_t arrlen = ARRAYSIZE(skyTexturePath);
//     for (size_t i = 0; i <= arrlen - 1; i++)
//     {
//       gfx::gfxTexture* tex = new gfx::gfxTexture();
//       tex->Create(skyTexturePath[i]);
//       textObj[i] = tex;

//       context.m_pDeviceContext->CopySubresourceRegion(
//         textureCube.GetTexture().Get(),
//         D3D11CalcSubresource(0,i,0),0,0,0,
//         reinterpret_cast<ID3D11Resource*>(textObj[i]->GetTexture().Get()),0,nullptr
//       );
//     }
//   }

//   textureCube.Bind();
// }

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{

  gfx::Application app;
  app.RenderCallback = Render;
  app.Init(L"SkyBox");



  renderState.Init();

  renderState.SetSampleState(gfx::SamplerState::AnisotropicClamp);
  renderState.SetRasteriazerState(gfx::RasterizerState::CullNone);


  constMag.Init();
  camera.Init();


  {
    gfx::GeometrySphere sphere;
    sphere.Create();

    skyIndicesBuffer.Create(sphere.Indices.size(), sphere.Indices.data());
    //indicesBuffer.Bind();

    skyVerticesBuffer.Create(sphere.Verteices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)sphere.Verteices.data());

    sphereSkyIndexCnt = sphere.Indices.size();
    //verticesBuffer.Bind();
  }
  {
    gfx::GemotryCube cube;
    cube.Create(2.0f);

    cubeIndexBuffer.Create(cube.Indices.size(), cube.Indices.data());
    //cubeIndexBuffer.Bind();

    cubeVerticesBuffer.Create(cube.Vertices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)cube.Vertices.data());
    //verticesBuffer.Bind();
  }


  vertexShader.CompileFromFile("assets/shader/skybox/skyboxV.hlsl");
  pixelShader.CompileFromFile("assets/shader/skybox/skyboxP.hlsl");
  skyTexCube.Create(skyTexturePath);
  skydaylightTexCube.Create(skydaylightTexturePath);
  skysunlightTexCube.Create(skysunTexturePath);

  DefvertexShader.CompileFromFile("assets/shader/skybox/defV.hlsl");
  DefpixelShader.CompileFromFile("assets/shader/skybox/defP.hlsl");
  cubeTexture.Create(L"assets/texture/WoodCrate.dds");
  

 
  skyinputlayout.CreateLayout(vertexShader.GetByteBlod());
  cubeinputlayout.CreateLayout(DefvertexShader.GetByteBlod());

  app.Run();
  return 0;
}
