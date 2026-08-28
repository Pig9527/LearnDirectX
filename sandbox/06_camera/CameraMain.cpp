#pragma once

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
#include "core/Context.h"
#include "core/Camera.h"

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

struct PStexture
{
  float tiling;
  DirectX::XMFLOAT3 pad;
};


sMvp mvp;
PSConstant materialLight;
PStexture textureConstant;

gfx::gfxTexture cubeTexture;
gfx::gfxTexture floorTexture;
gfx::gfxTexture wallTexture;
gfx::gfxTexture waterTexture;
gfx::gfxRenderStateCache renderState;

gfx::gfxConstantBuffer<sMvp> vertexConstant;
gfx::gfxConstantBuffer<PSConstant> psConstant;
gfx::gfxConstantBuffer<PStexture> psTextureConstant;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> cubeVertexBuffer;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> floorVertexBuffer;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> wallVertexBuffer;
gfx::gfxVertexBuffer<gfx::VertexPosColorNormalUv> waterVertexBuffer;
gfx::gfxIndexBuffer cubeIndexBuffer;
gfx::gfxIndexBuffer floorIndexBuffer;
gfx::gfxIndexBuffer wallIndexBuffer;
gfx::gfxIndexBuffer waterIndexBuffer;
gfx::Model* pModel;

gfx::Camera* pCamera;

static float phi,theta;


void Reset()
{
  materialLight.material.ambient = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  materialLight.material.diffuse = DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f };
  materialLight.material.specular = DirectX::XMFLOAT4{ 0.5f,0.5f,0.5f,1.0f };

  materialLight.eye = DirectX::XMFLOAT3{ 0.0f,5.0f, -10.0f };
  materialLight.light.ambient = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  materialLight.light.diffuse = DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f };
  materialLight.light.specular = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  materialLight.light.direction = DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f);

  pCamera->SetPosition(materialLight.eye);
}

void Render()
{
  phi += 0.3f *0.0016f; theta += 0.0f *0.0016f;
#if 1
  DirectX::XMMATRIX world = DirectX::XMMatrixIdentity(); 

#else
  DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixTranslationFromVector(DirectX::XMVectorSet(-phi, 0.0, 0.0, 0.0))
  );
#endif

  // DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(
  //   DirectX::XMMatrixLookAtLH(
  //     DirectX::XMVectorSet(materialLight.eye.x,materialLight.eye.y,materialLight.eye.z,1.0f),
  //     DirectX::XMVectorSet(0.0f,0.0f,0.0f,1.0f),
  //     DirectX::XMVectorSet(0.0f,1.0f,0.0f,1.0f)
  //   )
  // );

  //camera.GetViewMatrix()

#if 1
  // float aspect = static_cast<float>(gfx::Context::sWindowWidth) / static_cast<float>(gfx::Context::sWindowHeight);

  // DirectX::XMMATRIX projeect = DirectX::XMMatrixTranspose(
  //   DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, aspect,0.1f,1000.0f)
  // );

#else
  DirectX::XMMATRIX projeect = DirectX::XMMatrixOrthographicLH(
    gfx::Context::sWindowWidth,
    gfx::Context::sWindowHeight,
    0.1f,
    500.0f
  );

#endif
  materialLight.eye = pCamera->GetPosition();
  mvp.world = world;
  mvp.view = pCamera->GetViewMatrix();
  mvp.project = pCamera->GetProjectMatrix();
  mvp.worldInvTranspose = DirectX::XMMatrixInverse(nullptr,world);
  mvp.mvp =  mvp.project * mvp.view * world;

  vertexConstant.Upload(mvp);

  psConstant.Upload(materialLight);




  gfx::gfxContext::Get().m_pDeviceContext->RSSetState(nullptr);
  gfx::gfxContext::Get().m_pDeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);

  textureConstant.tiling = 5;


  floorTexture.Bind();
  psTextureConstant.Upload(textureConstant);
  floorVertexBuffer.Bind();
  floorIndexBuffer.Bind();
  gfx::Renderer::DrawIndex(6);

  wallTexture.Bind();
  wallVertexBuffer.Bind();
  wallIndexBuffer.Bind();
  gfx::Renderer::DrawIndex(18);





  textureConstant.tiling = 1;
  cubeTexture.Bind();
  cubeVertexBuffer.Bind();
  cubeIndexBuffer.Bind();
  psTextureConstant.Upload(textureConstant);
  gfx::Renderer::DrawIndex(36);

  gfx::gfxContext::Get().m_pDeviceContext->RSSetState(renderState.GetRasterizerState(gfx::RasterizerState::CullNone).Get());
  gfx::gfxContext::Get().m_pDeviceContext->OMSetBlendState(renderState.GetBlendState(gfx::BlendState::Opaque).Get(), nullptr, 0xffffffff);

  textureConstant.tiling = 1;
  waterTexture.Bind();
  psTextureConstant.Upload(textureConstant);
  waterVertexBuffer.Bind();
  waterIndexBuffer.Bind();
  gfx::Renderer::DrawIndex(6);

  float d1 = 0.0f,d2 = 0.0f;
  if(ImGui::IsKeyDown(ImGuiKey_W))
  {
    d1+=0.016;
  }
  if (ImGui::IsKeyDown(ImGuiKey_S))
  {
    d1 -= 0.016;
  }
  if (ImGui::IsKeyDown(ImGuiKey_A))
  {
    d2 -= 0.016;
  }
  if (ImGui::IsKeyDown(ImGuiKey_D))
  {
    d2 += 0.016;
  }
  pCamera->MoveForward(d1 * 0.16f);
  pCamera->MoveRight(d2 * 0.16f);
  ImGuiIO& io = ImGui::GetIO();
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
  {

    pCamera->Rotate(io.MouseDelta.y * 0.01f,io.MouseDelta.x * 0.01f);
  }



  pCamera->Update(0.016);
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();
  ImGui::NewFrame();

  if (io.MouseWheel != 0.0f)
  {
    pCamera->Zoom(-io.MouseWheel * 1.0f);
  }
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

  ImGui::SliderFloat3("eye", &materialLight.eye.x, -100.0f, 100.0f, "%0.2f");

  if (ImGui::Button("reset"))
  {
    Reset();
  }
  ImGui::End();
  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.Init(TEXT("texture"));
  app.RenderCallback = Render;

  pCamera = new gfx::Camera;

  Reset();

  pCamera->Init();

  {
    gfx::GemotryCube cube;
    cube.Create(5.0f);
    cubeVertexBuffer.Create(cube.Vertices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)cube.Vertices.data());

    cubeVertexBuffer.Bind();
    cubeIndexBuffer.Create(cube.Indices.size(), cube.Indices.data());
    cubeIndexBuffer.Bind();
  }

  {
    gfx::GemotryPlane plane;
    plane.Create(DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3{ 100.0f,5.0f,100.0f },
      DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3{0.0f,0.0f,0.0f});
    floorVertexBuffer.Create(plane.Vertices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)plane.Vertices.data(), 0);
    floorVertexBuffer.Bind();

    floorIndexBuffer.Create(plane.Indices.size(), plane.Indices.data());
    floorIndexBuffer.Bind();
  }


  std::vector<gfx::VertexPosColorNormalUv> wallVertices;
  //std::vector<uint32_t> wallIndices;
 
  wallVertices.resize(3 * 4);
  //wallIndices.reserve(3 * 6);
  DirectX::XMFLOAT3 rotates[] = {
    DirectX::XMFLOAT3{DirectX::XM_PIDIV2,0.0f,-DirectX::XM_PIDIV2},
    DirectX::XMFLOAT3{DirectX::XM_PIDIV2,0.0f,DirectX::XM_PIDIV2},
    DirectX::XMFLOAT3{-DirectX::XM_PIDIV2,0.0f,.0f},
  };
  float angles[] = { -90.0f,90.0f,-90.0f };
  DirectX::XMFLOAT3 transforms[] = {
    DirectX::XMFLOAT3{-50.0f,7.5f,0.0f},
    DirectX::XMFLOAT3{50.0f,7.5f,0.0f},
    DirectX::XMFLOAT3{0.0f,7.5f,50.0f}
  };
  float yPOs[] = { 0.0f,0.0f,0.0f };
  for (uint32_t i=0;i<3;i++)
  {

    gfx::GemotryPlane plane;
    plane.Create(DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3{ 100.0f,yPOs[i],20.0f },rotates[i],transforms[i]);
    
    wallVertices[i *4 + 0 ].position = plane.Vertices[0].position;
    wallVertices[i *4 + 1 ].position = plane.Vertices[1].position;
    wallVertices[i *4 + 2 ].position = plane.Vertices[2].position;
    wallVertices[i *4 + 3 ].position = plane.Vertices[3].position;

    wallVertices[i * 4 + 0].color = plane.Vertices[0].color;
    wallVertices[i * 4 + 1].color = plane.Vertices[1].color;
    wallVertices[i * 4 + 2].color = plane.Vertices[2].color;
    wallVertices[i * 4 + 3].color = plane.Vertices[3].color;

    wallVertices[i * 4 + 0].normal = plane.Vertices[0].normal;
    wallVertices[i * 4 + 1].normal = plane.Vertices[1].normal;
    wallVertices[i * 4 + 2].normal = plane.Vertices[2].normal;
    wallVertices[i * 4 + 3].normal = plane.Vertices[3].normal;

    wallVertices[i * 4 + 0].uv = plane.Vertices[0].uv;
    wallVertices[i * 4 + 1].uv = plane.Vertices[1].uv;
    wallVertices[i * 4 + 2].uv = plane.Vertices[2].uv;
    wallVertices[i * 4 + 3].uv = plane.Vertices[3].uv;
  }
  uint32_t* wallIndices = new uint32_t[3 * 6]();
  uint32_t offset = 0;
  for (uint32_t i = 0;i < 3 ;i++)
  {
    wallIndices[i * 6 + 0] = (offset + 0);
    wallIndices[i * 6 + 1] = (offset + 1);
    wallIndices[i * 6 + 2] = (offset + 2);

    wallIndices[i * 6 + 3] =( offset + 2);
    wallIndices[i * 6 + 4] =( offset + 3);
    wallIndices[i * 6 + 5] =( offset + 0);
    offset += 4;
  }

  wallVertexBuffer.Create(wallVertices.size() * sizeof(gfx::VertexPosColorNormalUv), (gfx::VertexPosColorNormalUv*)wallVertices.data());
  wallIndexBuffer.Create(18, wallIndices);

  delete[] wallIndices;

  {
    gfx::GemotryPlane plane;
    plane.Create(DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3{ 100.0f,-2.0f,100.0f },
      DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3{0.0f,0.0f,0.0f});
    waterVertexBuffer.Create(plane.Vertices.size() * sizeof(gfx::VertexPosColorNormalUv),
      (gfx::VertexPosColorNormalUv*)plane.Vertices.data(), 0);
    waterVertexBuffer.Bind();

    waterIndexBuffer.Create(plane.Indices.size(), plane.Indices.data());
    waterIndexBuffer.Bind();
  }
  gfx::gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfx::gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorNormalUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());



  cubeTexture.Create(L"assets/texture/WireFence.dds");
  //cubeTexture.Bind();

  floorTexture.Create(L"assets/texture/floor.dds");

  wallTexture.Create(L"assets/texture/brick.dds");

  waterTexture.Create(L"assets/texture/water.dds");


  renderState.Init();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetSamplers(0, 1, renderState.GetSampler(gfx::SamplerState::LinearWrap).GetAddressOf());

  float blendFactor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
  UINT sampleMask = 0xFFFFFFFF;
  gfx::gfxContext::Get().m_pDeviceContext->OMSetBlendState(renderState.GetBlendState(gfx::BlendState::Opaque).Get(),nullptr,sampleMask);

  gfx::gfxContext::Get().m_pDeviceContext->OMSetDepthStencilState(renderState.GetDepthStencilState(gfx::DepthStencilState::Default).Get(), 1);

  vertexConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0,1,vertexConstant.GetBuffer().GetAddressOf());

  psTextureConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(2,1, psTextureConstant.GetBuffer().GetAddressOf());
  psConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(1,1,psConstant.GetBuffer().GetAddressOf());
  app.Run();
}
