#include "core.h"
using namespace gfx;
using namespace DirectX;


void Render()
{
  Renderer::Clear();

  DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();

  DirectX::XMMATRIX project = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
    static_cast<float>(gfx::Context::sWindowWidth) / static_cast<float>(gfx::Context::sWindowHeight), 1.0f, 1000.0f));
  
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMVectorSet(0.0f,0.0f,-10.0f,1.0f),
    DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
  ));

  Renderer::VertexConstantBuffer.mvp = project* view * world;
  Renderer::VertexConstantBuffer.World = world;
  Renderer::VertexConstantBuffer.View = view;
  Renderer::VertexConstantBuffer.Project = project;
  Renderer::VertexConstantBuffer.WorldInvTranspose = DirectX::XMMatrixTranspose(
      DirectX::XMMatrixInverse(nullptr,world)
  );

  BatchRender::DrawQuadNormalUv();

  ImguiLayer::RenderDefMaterial();

  Renderer::Present();
}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  Application app;
  app.Init(TEXT("Load model [house]"));
  app.RenderCallback = Render;

  Renderer::Init();
  BatchRender::Init();

  {
    GemotryCube cube;
    cube.Create(10.0f);

    BatchRender::Draw(cube.Vertices);
  }

  gfx::gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfx::gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());

  gfxTexture* pcubeTex;
  pcubeTex->Create(L"assets/texture/WireFence.dds");

  BatchRender::End();
  app.Run();
}
