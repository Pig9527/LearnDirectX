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
#include "Graphic/gfxRenderState.h"

struct sDirectLight
{
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;

  DirectX::XMFLOAT3 direction;
  float  pad;
};

struct sSpotLight
{
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;

  DirectX::XMFLOAT3 position;
  float range;

  DirectX::XMFLOAT3 direction;
  float spot;
  
  DirectX::XMFLOAT3 att;
  float pad;
};


struct sPointLight
{

  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;

  DirectX::XMFLOAT3 position;
  float range;

  DirectX::XMFLOAT3 att;
  float pad;
};

struct sMatrial
{
  DirectX::XMFLOAT4 ambient;
  DirectX::XMFLOAT4 diffuse;
  DirectX::XMFLOAT4 specular;
  DirectX::XMFLOAT4 reflect;
};

struct sPixelConst
{
  sDirectLight light;
  sPointLight pointLight;
  sSpotLight spotLight;
  sMatrial material;
  DirectX::XMFLOAT3 eye;
  float pad;
};

struct sVertexConst
{
  DirectX::XMMATRIX mvp;
  DirectX::XMMATRIX world;
  DirectX::XMMATRIX view;
  DirectX::XMMATRIX project;
  DirectX::XMMATRIX worldInvTranspose;
};

static sPixelConst pixelColor;
gfx::gfxConstantBuffer<sPixelConst>* pConstBuffer;
gfx::gfxConstantBuffer<sVertexConst>* pVertexConstBuffer;
gfx::gfxRenderStateCache rendreState;

struct sModelVertexPixel
{
  gfx::gfxVertexBuffer<gfx::VertexPosColorNormal>* pVertexBuffer;
  gfx::gfxIndexBuffer* pIndex;
  gfx::Model* pModel;
  uint32_t indexCnt;
};

sModelVertexPixel models[4];

static int currItem = 0;
static int currLightItem = 0;
static char* meshStrs[] = { "Box","Sphere","Cone","Cylinder"};
static char* lightStrs[] = { "Direct","Point","Spot"};
static float phi = 0.0f, theta = 0.0f;
static bool bAnimation = true;
static bool bWire = false;

void Render()
{
  static sVertexConst mvp;
  //DirectX::XMMATRIX mod = DirectX::XMMatrixIdentity();
  DirectX::XMMATRIX world = DirectX::XMMatrixTranspose(
     DirectX::XMMatrixRotationX(phi) * DirectX::XMMatrixRotationY(theta)
  );

  DirectX::XMMATRIX project = DirectX::XMMatrixTranspose(DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2,
    static_cast<float>(gfx::Context::sWindowWidth) / static_cast<float>(gfx::Context::sWindowHeight), 1.0f, 1000.0f));
  DirectX::XMMATRIX view = DirectX::XMMatrixTranspose(DirectX::XMMatrixLookAtLH(
    DirectX::XMLoadFloat3(&pixelColor.eye),
    DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
    DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f)
  ));
  mvp.world = world;
  mvp.project = project;
  mvp.view = view;
  mvp.worldInvTranspose = DirectX::XMMatrixInverse(nullptr, mvp.world);
  mvp.mvp = project * view * world;

  pVertexConstBuffer->Upload(mvp);

  pConstBuffer->Upload(pixelColor);
  gfx::gfxContext::Get().m_pDeviceContext->DrawIndexed(models[currItem].indexCnt, 0, 0);

  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();
  ImGui::Begin("settting");

  ImGui::Combo("Mesh", &currItem, meshStrs, ARRAYSIZE(meshStrs));

  models[currItem].pVertexBuffer->Bind(); models[currItem].pIndex->Bind();


  
  ImGui::Checkbox("animation", &bAnimation);
  if (bAnimation)
  {
    phi += 0.27f * 0.0016f; theta += 0.2f * 0.0016f;
  }
  if (ImGui::Checkbox("wire frame", &bWire))
  {
    gfx::gfxContext::Get().m_pDeviceContext->RSSetState(bWire ? rendreState.GetRasterizerState(gfx::RasterizerState::WireFrame).Get():nullptr);
  }

  ImGui::Text("material");
  ImGui::ColorEdit4("ambient##1", &pixelColor.material.ambient.x);
  ImGui::ColorEdit4("diffuse##1", &pixelColor.material.diffuse.x);
  ImGui::ColorEdit4("specular##1", &pixelColor.material.specular.x);

  ImGui::Text("Light");
  ImGui::Combo("Light", &currLightItem, lightStrs, ARRAYSIZE(lightStrs));
  ImGui::PushID(currLightItem);
  if (currLightItem == 0)
  {
    ImGui::ColorEdit4("ambient", &pixelColor.light.ambient.x);
    ImGui::ColorEdit4("diffuse", &pixelColor.light.diffuse.x);
    ImGui::ColorEdit4("specular", &pixelColor.light.specular.x);
    ImGui::SliderFloat3("direct", &pixelColor.light.direction.x, -10.0f, 10.0f, "%.02f");
  }
  else if (currLightItem == 1)
  {
    ImGui::ColorEdit4("ambient", &pixelColor.pointLight.ambient.x);
    ImGui::ColorEdit4("diffuse", &pixelColor.pointLight.diffuse.x);
    ImGui::ColorEdit4("specular", &pixelColor.pointLight.specular.x);
    ImGui::SliderFloat3("position", &pixelColor.pointLight.position.x, -10.0f, 10.0f, "%.02f");
    ImGui::SliderFloat3("range", &pixelColor.pointLight.range, 0.0f, 100.0f, "%.02f");
    ImGui::SliderFloat3("att", &pixelColor.pointLight.att.x, -10.0f, 10.0f, "%.02f");
  }
  else if (currLightItem == 2)
  {
    ImGui::ColorEdit4("ambient", &pixelColor.spotLight.ambient.x);
    ImGui::ColorEdit4("diffuse", &pixelColor.spotLight.diffuse.x);
    ImGui::ColorEdit4("specular", &pixelColor.spotLight.specular.x);
    ImGui::SliderFloat3("position", &pixelColor.spotLight.position.x, -10.0f, 10.0f, "%.02f");
    ImGui::SliderFloat3("direction", &pixelColor.spotLight.direction.x, -10.0f, 10.0f, "%.02f");
    ImGui::SliderFloat3("spot", &pixelColor.spotLight.spot, 0.0f, 100.0f, "%.02f");
    ImGui::SliderFloat3("range", &pixelColor.spotLight.range, 0.0f, 1000000.0f, "%.02f");
    ImGui::SliderFloat3("att", &pixelColor.spotLight.att.x, -10.0f, 10.0f, "%.02f");
  }
  ImGui::PopID();

  ImGui::Text("Camera");
  ImGui::SliderFloat3("eyePosition", &pixelColor.eye.x,-10.0f,10.0f,"%0.2f");
  //ImGui::ColorEdit3("color",&pixelColor.color.x);
  ImGui::End();
  ImGui::Render();

  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void CreateModel()
{

  rendreState.Init();

  models[0].pModel = new gfx::ModelNormal;
  models[0].pModel->LoadModelFromFile("assets/model/cube.fbx");
  models[0].pIndex = new gfx::gfxIndexBuffer();
  models[0].pIndex->Create(models[0].pModel->GetIndexCnt(), models[0].pModel->GetIndices().data());
  models[0].pVertexBuffer = new gfx::gfxVertexBuffer<gfx::VertexPosColorNormal>;
  models[0].pVertexBuffer->Create(models[0].pModel->GetVertexSize(),(gfx::VertexPosColorNormal*)models[0].pModel->GetVertex());
  models[0].indexCnt = models[0].pModel->GetIndexCnt();

  models[1].pModel = new gfx::ModelNormal;
  models[1].pModel->LoadModelFromFile("assets/model/Sphere.fbx");
  models[1].pIndex = new gfx::gfxIndexBuffer();
  models[1].pIndex->Create(models[1].pModel->GetIndexCnt(), models[1].pModel->GetIndices().data());
  models[1].pVertexBuffer = new gfx::gfxVertexBuffer<gfx::VertexPosColorNormal>;
  models[1].pVertexBuffer->Create(models[1].pModel->GetVertexSize(), (gfx::VertexPosColorNormal*)models[1].pModel->GetVertex());
  models[1].indexCnt = models[1].pModel->GetIndexCnt();

  models[2].pModel = new gfx::ModelNormal;
  models[2].pModel->LoadModelFromFile("assets/model/cone.fbx");
  models[2].pIndex = new gfx::gfxIndexBuffer();
  models[2].pIndex->Create(models[2].pModel->GetIndexCnt(), models[2].pModel->GetIndices().data());
  models[2].pVertexBuffer = new gfx::gfxVertexBuffer<gfx::VertexPosColorNormal>;
  models[2].pVertexBuffer->Create(models[2].pModel->GetVertexSize(), (gfx::VertexPosColorNormal*)models[2].pModel->GetVertex());
  models[2].indexCnt = models[2].pModel->GetIndexCnt();

  models[3].pModel = new gfx::ModelNormal;
  models[3].pModel->LoadModelFromFile("assets/model/Cylinder.fbx");
  models[3].pIndex = new gfx::gfxIndexBuffer();
  models[3].pIndex->Create(models[3].pModel->GetIndexCnt(), models[3].pModel->GetIndices().data());
  models[3].pVertexBuffer = new gfx::gfxVertexBuffer<gfx::VertexPosColorNormal>;
  models[3].pVertexBuffer->Create(models[3].pModel->GetVertexSize(), (gfx::VertexPosColorNormal*)models[3].pModel->GetVertex());
  models[3].indexCnt = models[3].pModel->GetIndexCnt();
}

int WINAPI WinMain(HINSTANCE hPreinstance, HINSTANCE hInstacne, PTSTR cmdline, int show)
{
  pixelColor.material.ambient = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  pixelColor.material.diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
  pixelColor.material.specular = DirectX::XMFLOAT4{ 0.3f,0.3f,0.5f,1.0f };
  pixelColor.material.reflect = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f,5.0f };

  pixelColor.eye = DirectX::XMFLOAT3{ 0.0f,0.0f,-5.0f };
  pixelColor.light.ambient = DirectX::XMFLOAT4{ 0.2f, 0.2f, 0.2f, 1.0f };
  pixelColor.light.diffuse = DirectX::XMFLOAT4{ 0.8f, 0.8f, 0.8f, 1.0f };
  pixelColor.light.specular = DirectX::XMFLOAT4{ 0.5f, 0.5f, 0.5f, 1.0f };
  pixelColor.light.direction = DirectX::XMFLOAT3{ -0.577f, -0.577f, 0.577f };

  pixelColor.pointLight.ambient = DirectX::XMFLOAT4{ 0.2f, 0.2f, 0.2f, 1.0f };
  pixelColor.pointLight.diffuse = DirectX::XMFLOAT4{ 0.3f, 0.3f, 0.3f, 1.0f };
  pixelColor.pointLight.specular = DirectX::XMFLOAT4{ 0.7f, 0.7f, 0.7f, 1.0f };
  pixelColor.pointLight.position = DirectX::XMFLOAT3{ 0.0f, 0.0f, -10.0f };
  pixelColor.pointLight.att = DirectX::XMFLOAT3{ 0.0f, 0.1f, 0.0f };
  pixelColor.pointLight.range = 25.0f;

  pixelColor.spotLight.position = DirectX::XMFLOAT3{ 0.0f, 0.0f, -10.0f };
  pixelColor.spotLight.direction = DirectX::XMFLOAT3{ 0.0f, 0.0f, 1.0f };

  pixelColor.spotLight.ambient = DirectX::XMFLOAT4{ 0.0f, 0.0f, 0.0f, 1.0f };
  pixelColor.spotLight.diffuse = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };
  pixelColor.spotLight.specular = DirectX::XMFLOAT4{ 1.0f, 1.0f, 1.0f, 1.0f };

  pixelColor.spotLight.att = DirectX::XMFLOAT3{ 1.0f, 0.1f, 0.0f };
  pixelColor.spotLight.range = 10000.0f;
  pixelColor.spotLight.spot = 12.0f;

  gfx::Application app;
  app.Init(TEXT("light"));
  app.RenderCallback = Render;

  CreateModel();
  models[0].pVertexBuffer->Bind(); models[0].pIndex->Bind();

  gfx::gfxShaderVertex vertex;
  vertex.CompileFromFile("assets/shader/lightV.hlsl");
  vertex.Bind();

  gfx::gfxShaderPixel pixel;
  pixel.CompileFromFile("assets/shader/lightP.hlsl");
  pixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorNormal> layout;
  layout.CreateLayout(vertex.GetByteBlod());

  pConstBuffer = new gfx::gfxConstantBuffer<sPixelConst>();
  pConstBuffer->Create();

  pVertexConstBuffer = new gfx::gfxConstantBuffer<sVertexConst>;
  pVertexConstBuffer->Create();

  gfx::gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0, 1, pVertexConstBuffer->GetBuffer().GetAddressOf());
  gfx::gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(1, 1, pConstBuffer->GetBuffer().GetAddressOf());
  app.Run();
}
