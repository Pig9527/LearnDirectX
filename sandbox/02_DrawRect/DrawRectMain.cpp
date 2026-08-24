
#include "core/Application.h"
#include "Graphic/gfxLayout.h"
#include "Graphic/gfxShaderVertex.h"
#include "Graphic/gfxShaderPixel.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxIndexBuffer.h"

void Render()
{
  gfx::gfxContext::Get().m_pDeviceContext->DrawIndexed(6,0,0);
}

int WINAPI WinMain(HINSTANCE hPreinstance, HINSTANCE hInstacne, PTSTR cmdline, int show)
{
  gfx::Application app;
  app.Init(TEXT("Draw A Rectangle"));
  app.RenderCallback = Render;

  gfx::VertexPosColor vertices[] = {
      DirectX::XMFLOAT3{-0.5f, -0.5f, 0.0f}, DirectX::XMFLOAT4{1.0f, 0.0f, 0.0f, 1.0f},
      DirectX::XMFLOAT3{-0.5f, 0.5f, 0.0f}, DirectX::XMFLOAT4{1.0f, 0.0f, 0.0f, 1.0f},
      DirectX::XMFLOAT3{0.5f, 0.5f, 0.0f}, DirectX::XMFLOAT4{0.0f, 1.0f, 0.0f, 1.0f},
      DirectX::XMFLOAT3{0.5f, -0.5f, 0.0f}, DirectX::XMFLOAT4{0.0f, 1.0f, 1.0f, 1.0f}};

  gfx::gfxVertexBuffer<gfx::VertexPosColor> vertexBuffer;
  vertexBuffer.Create(sizeof(vertices),vertices);
  vertexBuffer.Bind();

  uint32_t indices[] = {0, 1, 2, 2, 3, 0};
  gfx::gfxIndexBuffer indexBuffer;
  indexBuffer.Create(ARRAYSIZE(indices),indices);
  indexBuffer.Bind();

  gfx::gfxShaderVertex vertex;
  vertex.CompileFromFile("assets/shader/baseVertex.hlsl");
  vertex.Bind();

  gfx::gfxShaderPixel pixel;
  pixel.CompileFromFile("assets/shader/basePixel.hlsl");
  pixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColor> layout;
  layout.CreateLayout(vertex.GetByteBlod());

  app.Run();
}
