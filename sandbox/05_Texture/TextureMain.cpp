#include "Graphic/gfxContext.h"
#include "Graphic/gfxTexture.h"
#include "Graphic/gfxLayout.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxIndexBuffer.h"
#include "core/Application.h"
#include "Graphic/gfxConstantBuffer.h"
#include "Graphic/gfxRenderState.h"
#include "Gemotry/Vertex.h"
#include "Gemotry/Model.h"
#include "Render/Renderer.h"
#include "Graphic/gfxShaderPixel.h"
#include "Graphic/gfxShaderVertex.h"
#include "gemotry/Gemotry.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"


struct sMvp
{
  DirectX::XMMATRIX mvp;
  DirectX::XMMATRIX world;
  DirectX::XMMATRIX view;
  DirectX::XMMATRIX project;
  DirectX::XMMATRIX worldInvTranspose;
};

struct sDirectLight
{
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;
  DirectX::XMFLOAT3 direction;
  float pad;
};

struct sMaterial
{ 
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;

};

struct PSConstant
{
  sMaterial material;
  sDirectLight light;
  DirectX::XMFLOAT3 eye;
  float pad;
};

sMvp mvp;
PSConstant materialLight;
gfx::gfxConstantBuffer<sMvp> vertexConstant;
gfx::gfxConstantBuffer<PSConstant> psConstant;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> vertexBuffer;
gfx::gfxIndexBuffer indexBuffer;
gfx::Model* pModel;

static float phi,theta;

void Render()
{
  phi += 0.3f *0.0016f; theta += 0.0f *0.0016f;

  DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixRotationY(phi) * DirectX::XMMatrixRotationX(theta)
  );
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixLookAtLH(
      DirectX::XMVectorSet(0.0f,0.0f,-5.0f,1.0f),DirectX::XMVectorSet(0.0f,0.0f,0.0f,1.0f),DirectX::XMVectorSet(0.0f,1.0f,0.0f,1.0f)
    )
  );

  DirectX::XMMATRIX projeect = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,16.0f/9.0f,0.1f,1000.0f)
  );

  mvp.world = world;
  mvp.view = view;
  mvp.project = projeect;
  mvp.worldInvTranspose = DirectX::XMMatrixInverse(nullptr,world);
  mvp.mvp = projeect * view * world;

  vertexConstant.Upload(mvp);

  psConstant.Upload(materialLight);


  gfx::Renderer::DrawIndex(36);

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  ImGui::Begin("setting");
  
  ImGui::PushID(0);
  ImGui::Text("Direct light");
  ImGui::ColorEdit4("ambient",&materialLight.light.ambient.x);
  ImGui::ColorEdit4("diffuse",&materialLight.light.diffuse.x);
  ImGui::ColorEdit4("specular",&materialLight.light.specular.x);
  ImGui::SliderFloat3("direction",&materialLight.light.direction.x,-5.0f,5.0f,"%0.2f");
  ImGui::PopID();

  ImGui::PushID(1);
  ImGui::Text("Material");
  ImGui::ColorEdit4("ambient",&materialLight.material.ambient.x);
  ImGui::ColorEdit4("diffuse",&materialLight.material.diffuse.x);
  ImGui::ColorEdit4("specular",&materialLight.material.specular.x);
  ImGui::PopID();

  ImGui::End();
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.Init(TEXT("texture"));
  app.RenderCallback = Render;

  materialLight.material.ambient = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  materialLight.material.diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
  materialLight.material.specular = DirectX::XMFLOAT4{ 0.3f,0.3f,0.5f,1.0f };

  materialLight.eye = DirectX::XMFLOAT3{ 0.0f,0.0f,-5.0f };
  materialLight.light.ambient = DirectX::XMFLOAT4{ 0.2f, 0.2f, 0.2f, 1.0f };
  materialLight.light.diffuse = DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f };
  materialLight.light.specular = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  materialLight.light.direction = DirectX::XMFLOAT3{ -0.577f, -0.577f, 0.577f };

  gfx::GemotryCube cube;
  cube.Create(2.0f);
  vertexBuffer.Create(cube.Vertices.size() *sizeof(gfx::VertexPosColorNormalUv),
    (gfx::VertexPosColorNormalUv*)cube.Vertices.data());
  vertexBuffer.Bind();
  indexBuffer.Create(cube.Indices.size(),cube.Indices.data());
  indexBuffer.Bind();

  gfx::gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfx::gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());


  gfx::gfxTexture texture;
  texture.Create(L"assets/texture/WoodCrate.dds");
  texture.Bind();

  gfx::gfxRenderStateCache renderState;
  renderState.Init();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetSamplers(0, 1, renderState.GetSampler(gfx::SamplerState::LinearClamp).GetAddressOf());


  //gfx::gfxContext::Get().m_pDeviceContext->OMSetDepthStencilState(renderState.GetDepthStencilState(gfx::DepthStencilState::Default).Get(), 1);

  vertexConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0,1,vertexConstant.GetBuffer().GetAddressOf());
  psConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(1,1,psConstant.GetBuffer().GetAddressOf());
  app.Run();
}
