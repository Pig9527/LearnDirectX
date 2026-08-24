
#include "core/Application.h"
#include "Graphic/gfxLayout.h"
#include "Graphic/gfxShaderVertex.h"
#include "Graphic/gfxShaderPixel.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxIndexBuffer.h"
#include "Graphic/gfxConstantBuffer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"

struct sPixelConst
{
  DirectX::XMFLOAT3 color;
  float pad;
};

static sPixelConst pixelColor;
gfx::gfxConstantBuffer<sPixelConst>* pConstBuffer;
void Render()
{

  pConstBuffer->Upload(pixelColor);
  gfx::gfxContext::Get().m_pDeviceContext->DrawIndexed(6, 0, 0);

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();
  ImGui::Begin("settting");
  ImGui::ColorEdit3("color",&pixelColor.color.x);
  ImGui::End();
  ImGui::Render();
  
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

}

int WINAPI WinMain(HINSTANCE hPreinstance, HINSTANCE hInstacne, PTSTR cmdline, int show)
{
  pixelColor.color = DirectX::XMFLOAT3{ 0.0f,0.3f,0.5f };
  gfx::Application app;
  app.Init(TEXT("Draw A Cube"));
  app.RenderCallback = Render;
  using namespace DirectX;
  gfx::VertexPosColor vertices[] = {
    { XMFLOAT3(-0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f,1.0f, 1.0f) },
    { XMFLOAT3(-0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(0.5f, 0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(0.5f, -0.5f, -0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(0.5f, 0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(0.5f, -0.5f, 0.5f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) }
  };

  gfx::gfxVertexBuffer<gfx::VertexPosColor> vertexBuffer;
  vertexBuffer.Create(sizeof(vertices),vertices);
  vertexBuffer.Bind();

  uint32_t indices[] = {
    // 正面
    0, 1, 2,
    2, 3, 0,
    // 左面
    4, 5, 1,
    1, 0, 4,
    // 顶面
    1, 5, 6,
    6, 2, 1,
    // 背面
    7, 6, 5,
    5, 4, 7,
    // 右面
    3, 2, 6,
    6, 7, 3,
    // 底面
    4, 0, 3,
    3, 7, 4
  };
  gfx::gfxIndexBuffer indexBuffer;
  indexBuffer.Create(ARRAYSIZE(indices),indices);
  indexBuffer.Bind();

  gfx::gfxShaderVertex vertex;
  vertex.CompileFromFile("assets/shader/constV.hlsl");
  vertex.Bind();

  gfx::gfxShaderPixel pixel;
  pixel.CompileFromFile("assets/shader/constP.hlsl");
  pixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColor> layout;
  layout.CreateLayout(vertex.GetByteBlod());


  pConstBuffer = new gfx::gfxConstantBuffer<sPixelConst>();
  pConstBuffer->Create();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(0,1,pConstBuffer->GetBuffer().GetAddressOf());

  app.Run();
}
