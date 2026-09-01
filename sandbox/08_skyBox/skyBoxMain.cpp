#include "core.h"
#include "Graphic/gfxTextureCube.h"

gfx::Camera camera;
gfx::gfxConstBufferMag constMag;

gfx::gfxIndexBuffer indicesBuffer;
gfx::gfxIndexBuffer cubeIndexBuffer;

gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> verticesBuffer;
gfx::gfxVertexBuffer<gfx::VertexPosColorUv> cubeVerticesBuffer;
gfx::gfxTextureCube textureCube;

gfx::gfxShaderVertex vertexShader;
gfx::gfxShaderPixel pixelShader;

gfx::gfxShaderVertex DefvertexShader;
gfx::gfxShaderPixel DefpixelShader;

gfx::gfxTexture cubeTexture;
// char* skyTexturePath[] = {
//   "assets/texture/skybox/daylight0.png",
//   "assets/texture/skybox/daylight1.png",
//   "assets/texture/skybox/daylight2.png",
//   "assets/texture/skybox/daylight3.png",
//   "assets/texture/skybox/daylight4.png",
//   "assets/texture/skybox/daylight5.png"
// };

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

  vertexShader.Bind();
  pixelShader.Bind();
  verticesBuffer.Bind();
  indicesBuffer.Bind();
  textureCube.Bind();
  gfx::Renderer::DrawIndex(36);

  DefvertexShader.Bind();
  DefpixelShader.Bind();
  cubeVerticesBuffer.Bind();
  cubeIndexBuffer.Bind();
  cubeTexture.Bind();
  gfx::Renderer::DrawIndex(36);

  gfx::ImguiLayer::Begin("setting");

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

  gfx::gfxRenderStateCache renderState;

  renderState.Init();
  renderState.SetDepthStencilState(gfx::DepthStencilState::LESSEQU);
  renderState.SetSampleState(gfx::SamplerState::AnisotropicWrap);
  renderState.SetRasteriazerState(gfx::RasterizerState::CullNone);


  constMag.Init();
  camera.Init();


  {
    gfx::GemotryCube cube;
    cube.Create(2.0f);

    indicesBuffer.Create(cube.Indices.size(), cube.Indices.data());
    //indicesBuffer.Bind();

    verticesBuffer.Create(cube.Vertices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)cube.Vertices.data());
    //verticesBuffer.Bind();
  }
  {
    gfx::GemotryCube cube;
    cube.Create(2.0f);

    cubeIndexBuffer.Create(cube.Indices.size(), cube.Indices.data());
    //cubeIndexBuffer.Bind();

    cubeVerticesBuffer.Create(cube.Vertices.size() * sizeof(gfx::VertexPosColorUv),
      (gfx::VertexPosColorUv*)cube.Vertices.data());
    //verticesBuffer.Bind();
  }


  vertexShader.CompileFromFile("assets/shader/skybox/skyboxV.hlsl");
  //vertexShader.Bind();


  pixelShader.CompileFromFile("assets/shader/skybox/skyboxP.hlsl");
 // pixelShader.Bind();


  DefvertexShader.CompileFromFile("assets/shader/skybox/defV.hlsl");
  //vertexShader.Bind();


  DefpixelShader.CompileFromFile("assets/shader/skybox/defP.hlsl");
  //.Bind();
  cubeTexture.Create(L"assets/texture/WoodCrate.dds");
  
  textureCube.Create();
  textureCube.Bind();



  gfx::gfxLayout<gfx::VertexPosColorNormalUv> inputlayout;
  inputlayout.CreateLayout(vertexShader.GetByteBlod());


  app.Run();
  return 0;
}
