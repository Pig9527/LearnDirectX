#include "core.h"
#include <strsafe.h>
using namespace gfx;
using namespace DirectX;

gfxConstBufferMag constMag;
Camera camera;
gfxRenderStateCache renderstate;
Model* pmodel = nullptr;
void Render()
{
  Renderer::Clear();

 ImGuiIO& io = ImGui::GetIO();
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
  {

    camera.Rotate(io.MouseDelta.y * 0.01f,io.MouseDelta.x * 0.01f);
  }
  camera.Update(0.16);
  constMag.SetConstMVP(&camera);
  constMag.Upload2VS();
  constMag.Upload2PS();
  constMag.UploadTex();
  BatchRender2D<VertexPosColorNormalUv>::DrawQuad();

  Context::sTextureTell.telling = 1;

  constMag.UploadTex();
  reinterpret_cast<ModelTexCoordNormal*>(pmodel)->Bind();
  Renderer::DrawIndex(pmodel->GetIndexCnt());


  ImguiLayer::RenderDefMaterial();

  Renderer::Present();
}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  Application app;
  app.Init(TEXT("Load model [house]"));
  app.RenderCallback = Render;

  Context::CameraPos = DirectX::XMFLOAT3{ 0.0f,500.0f,-100.0f };
  Context::sTextureTell.telling = 1.0f;
  constMag.Init();
  camera.Init();


  renderstate.Init();
  renderstate.SetSampleState(SamplerState::LinearWrap);
  renderstate.SetRasteriazerState(RasterizerState::CullNone);

  BatchRender2D<VertexPosColorNormalUv>::Init();

  gfxTexture* pcubeTex = new gfxTexture();
  pcubeTex->Create(L"assets/texture/grass.dds");

  {

    GemotryPlane plane;

    plane.Create(XMFLOAT3{-100,0,-100 }, XMFLOAT3{ 200,0,200 });
    BatchRender2D<VertexPosColorNormalUv>::Draw(plane.Vertices.data(), 1, pcubeTex);
  }

  gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfxLayout<VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());


  pmodel = new ModelTexCoordNormal();
  pmodel->LoadModelFromFile("assets/model/house/house.obj");
  pmodel->Create();
  //gfxContext::Get().m_pDeviceContext->PSSetSamplers(0,1,renderstate.GetSampler(SamplerState::LinearWrap).GetAddressOf());

  BatchRender2D<VertexPosColorNormalUv>::End();
  app.Run();
}
