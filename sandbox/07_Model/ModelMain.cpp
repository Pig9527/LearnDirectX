#include "core.h"
using namespace gfx;
using namespace DirectX;


void Render()
{
  Renderer::Clear();

  DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

  DirectX::XMMATRIX project = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4,
    static_cast<float>(gfx::Context::sWindowWidth) / static_cast<float>(gfx::Context::sWindowHeight), 0.1f, 1000.0f));

  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMVectorSet(0.0f, 0.0f, -10.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
  ));

  Renderer::VertexConstantBuffer.mvp = project * view * world;
  Renderer::VertexConstantBuffer.World = world;
  Renderer::VertexConstantBuffer.View = view;
  Renderer::VertexConstantBuffer.Project = project;
  Renderer::VertexConstantBuffer.WorldInvTranspose = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixInverse(nullptr, world)
  );

  Renderer::UploadMvp();

  BatchRender::DrawQuadNormalUv();


  ImguiLayer::RenderDefMaterial();

  Renderer::Present();
}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  Application app;
  app.Init(TEXT("Load model [house]"));
  app.RenderCallback = Render;

  BatchRender::Init();

  gfxTexture* pcubeTex = new gfxTexture();
  pcubeTex->Create(L"assets/texture/WoodCrate.dds");

  {
    GemotryCube cube;
    cube.Create(1.0f);

    BatchRender::Draw(cube.Vertices,1,pcubeTex);
  }

  gfx::gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfx::gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());

  gfx::gfxRenderStateCache renderstate;
  renderstate.Init();
  gfxContext::Get().m_pDeviceContext->PSSetSamplers(0,1,renderstate.GetSampler(SamplerState::LinearWrap).GetAddressOf());

  BatchRender::End();
  app.Run();
}
