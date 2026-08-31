#include "core.h"
#include <strsafe.h>
using namespace gfx;
using namespace DirectX;

gfxConstBufferMag constMag;
Camera camera;
gfxRenderStateCache renderstate;
void Render()
{
  Renderer::Clear();

#if 0
  DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

  DirectX::XMMATRIX project = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4,
    static_cast<float>(gfx::Context::sWindowWidth) / static_cast<float>(gfx::Context::sWindowHeight), 0.1f, 1000.0f));

#if 1
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMLoadFloat3(&Context::CameraPos),
    DirectX::XMLoadFloat3(&Context::CameraTarget),
    DirectX::XMLoadFloat3(&Context::CameraUp)
  ));
#else
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMVectorSet(0.0f, 10.0f, -10.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
  ));

#endif

  Context::sVertexConstantMVP.mvp = project * view * world;
  Context::sVertexConstantMVP.World = world;
  Context::sVertexConstantMVP.View = view;
  Context::sVertexConstantMVP.Project = project;
  Context::sVertexConstantMVP.WorldInvTranspose = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixInverse(nullptr, world)
  );
#endif
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


  ImguiLayer::RenderDefMaterial();

  Renderer::Present();
}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  Application app;
  app.Init(TEXT("Load model [house]"));
  app.RenderCallback = Render;

  Context::CameraPos = DirectX::XMFLOAT3{ 0.0f,5.0f,-5.0f };
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

    for (float x = -2.0f; x <= 2.0; x += 0.5f)
    {
      for (float z = -2.0f; z <= 2.0f; z += 0.5f)
      {
        plane.Create(XMFLOAT3{ x,0,z }, XMFLOAT3{ 0.3,0,0.3 });
        BatchRender2D<VertexPosColorNormalUv>::Draw(plane.Vertices.data(), 1, pcubeTex);
      }
    }
  }

  gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfxLayout<VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());


  //gfxContext::Get().m_pDeviceContext->PSSetSamplers(0,1,renderstate.GetSampler(SamplerState::LinearWrap).GetAddressOf());

  BatchRender2D<VertexPosColorNormalUv>::End();
  app.Run();
}
