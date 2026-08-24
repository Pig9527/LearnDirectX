
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
#include "core/Context.h"
#include "Gemotry/Model.h"
struct sPixelConst
{
  DirectX::XMFLOAT3 color;
  float pad;
};

struct sVertexConst
{
  DirectX::XMMATRIX mvp;
};

static sPixelConst pixelColor;
gfx::gfxConstantBuffer<sPixelConst>* pConstBuffer;
gfx::gfxConstantBuffer<sVertexConst>* pVertexConstBuffer;

static uint32_t indexCnt = 0;
void Render()
{

  static float phi = 0.0f, theta = 0.0f;
  phi+= 0.3f *0.0016; theta += 0.3f*0.0016f;

  static sVertexConst mvp;
  //DirectX::XMMATRIX mod = DirectX::XMMatrixIdentity();
  DirectX::XMMATRIX world  = DirectX::XMMatrixTranspose(
       DirectX::XMMatrixRotationX(phi) * DirectX::XMMatrixRotationY(theta)
   );

  DirectX::XMMATRIX project = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
    static_cast<float>(gfx::Context::sWindowWidth)/ static_cast<float>(gfx::Context::sWindowHeight),1.0f,1000.0f));
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMVectorSet(0.0f,0.0f,-5.0f,1.0f),
    DirectX::XMVectorSet(0.0f,0.0f,0.0f,1.0f),
    DirectX::XMVectorSet(0.0f,1.0f,0.0f,1.0f)
  ));
  mvp.mvp = project * view* world;

  pVertexConstBuffer->Upload(mvp);

  pConstBuffer->Upload(pixelColor);
  gfx::gfxContext::Get().m_pDeviceContext->DrawIndexed(indexCnt, 0, 0);

  

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
  pixelColor.color = DirectX::XMFLOAT3{ 0.3f,0.3f,0.5f };
  gfx::Application app;
  app.Init(TEXT("Draw A Cube"));
  app.RenderCallback = Render;

  gfx::Model<gfx::VertexPosColor> slid;
  slid.LoadModelFromFile("assets/model/cone.fbx");

  gfx::gfxVertexBuffer<gfx::VertexPosColor> vertexBuffer;
  vertexBuffer.Create(slid.GetVertices().size() *sizeof(gfx::VertexPosColor),slid.GetVertices().data());
  vertexBuffer.Bind();

  gfx::gfxIndexBuffer indexBuffer;
  indexBuffer.Create(slid.GetIndexCnt(),slid.GetIndices().data());

  indexCnt = slid.GetIndexCnt();
  indexBuffer.Bind();
  
  gfx::gfxShaderVertex vertex;
  vertex.CompileFromFile("assets/shader/cubeV.hlsl");
  vertex.Bind();

  gfx::gfxShaderPixel pixel;
  pixel.CompileFromFile("assets/shader/cubeP.hlsl");
  pixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColor> layout;
  layout.CreateLayout(vertex.GetByteBlod());


  pConstBuffer = new gfx::gfxConstantBuffer<sPixelConst>();
  pConstBuffer->Create();


  pVertexConstBuffer = new gfx::gfxConstantBuffer<sVertexConst>;
  pVertexConstBuffer->Create();

  gfx::gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0, 1, pVertexConstBuffer->GetBuffer().GetAddressOf());
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(1,1,pConstBuffer->GetBuffer().GetAddressOf());
  app.Run();
}
