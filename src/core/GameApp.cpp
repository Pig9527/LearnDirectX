#include "GameApp.h"
#include "Context.h"
#include "gfxConstantBufferManager.h"
#include "Renderer.h"
#include "nativeWindow.h"

#define BIND_EVENT_FN(X) std::bind(&gfx::GameApp::X,this,std::placeholders::_1)

gfx::GameApp::GameApp()
{
}

gfx::GameApp::~GameApp()
{
}

void gfx::GameApp::Init()
{

  gfx::WindowInfo info;
  info.hinstance = GetModuleHandle(0);
  info.title = "cube";
  m_window = std::make_unique<NativeWindow>(info);
  m_window->Initialize();
  m_window->SetEventCallback(BIND_EVENT_FN(OnEvent));


  gfx::Renderer::Init();

  m_renderState = std::make_unique<gfxRenderStateCache>();
  m_renderState->Init();

  std::wostringstream vertexPath(TEXT("assets/shader/baseVertex.hlsl"));
  std::wostringstream PixelPath(TEXT("assets/shader/basePixel.hlsl"));
  m_shader = std::make_shared<gfxShaderProgram>();
  m_shader->Init("assets/shader/baseVertex.hlsl", "assets/shader/basePixel.hlsl");
  m_shader->Bind();

  m_layout = std::make_unique<gfxLayout<VertexPosPosNormalUv>>();
  m_layout->CreateLayout(m_shader->GetVertexShader()->GetBlod());

  m_model = std::make_unique<Model<VertexPosPosNormalUv>>();
 // m_model->LoadModelFromFile("assets/model/BOSS_model_final.fbx");
  m_model->LoadModelFromFile("assets/model/dragon.obj");
  m_model->Create();


  TextureDesc desc;
  desc.filePath = "assets/backpack/diffuse1.jpg";
  m_texture = std::make_unique<gfxTexture>(desc);
  m_texture->Create();

  auto& sampler =  m_renderState->GetSampler(SamplerState::LinearClamp);
  gfxContext::Get().m_pDeviceContext->PSSetSamplers(0,1,sampler.GetAddressOf());


  m_update2GPU = std::make_shared<gfxConstacntBufferManager>();
  m_update2GPU->Bind();

  m_camera = std::make_shared<Camera>();
  m_camera->Init();

  m_layer = std::make_shared<ImguiLayer>();
  m_layer->Attach();
}



void gfx::GameApp::OnEvent(Event &e)
{
  EventDispatcher dispatcher(e);
  dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonDown));
  dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FN(OnKeyDown));
}

void gfx::GameApp::Run()
{
  MSG msg;
  while (Context::sbRunning)
  {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      this->Render();
      //m_camera->Update(0.016f);
    }
  }
}

void gfx::GameApp::Render()
{

  this->Begin();

  DirectX::XMMATRIX mod = DirectX::XMMatrixIdentity();
  mod = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(m_layer->scale)) *
    DirectX::XMMatrixRotationY(m_layer->theta));

  DirectX::XMMATRIX mvp = m_camera->GetProjectVeiwMatrix() * mod;
  PerFrameData data;
  data.mvp = mvp;
  data.viewProject = m_camera->GetProjectVeiwMatrix();
  data.world = mod;
  data.worldInvTranspone = DirectX::XMMatrixTranspose(mod);
  data.view = m_camera->GetViewMatrix();
  data.project = m_camera->GetProjectMatrix();

  m_update2GPU->UploadPerFrameToVS(data);
  MaterialData material;
  material.diffuse = m_layer->diffuse;
  material.specular = m_layer->specular;
  material.specularPower = m_layer->specularPower;

  material.ambient = m_layer->ambient;

  m_update2GPU->UploadMaterialToPS(material);


  LightData light;
  light.lightDir = m_layer->lightDir;
  light.lightColor = m_layer->lightColor;
  light.eyePos = m_layer->eyePos;

  m_update2GPU->UploadLightToPS(light);
  uint32_t indexCnt = m_model->GetIndexCnt();
  Renderer::DrawIndex(indexCnt);

  // for (RenderTriangle *cube : m_shapes)
  // {
  //   DirectX::XMMATRIX mvp = m_camera->GetProjectVeiwMatrix() * cube->m_mode;
  //   m_update2GPU->uploadMVP(mvp);
  //   m_update2GPU->uploadFloat4(m_layer->GetColor());
  //   gfxRenderer::DrawIndex(6);
  // }

  m_layer->Render();
  this->end();
}

void gfx::GameApp::Begin()
{
  Renderer::Clear();
}

void gfx::GameApp::end()
{
  Renderer::Present();
}

bool gfx::GameApp::OnMouseButtonDown(MouseButtonPressedEvent &e)
{
  return true;
}

bool gfx::GameApp::OnKeyDown(KeyPressedEvent &e)
{
  int keycode = e.GetKeyCode();
  switch (keycode)
  {
  case 'w':
    m_camera->MoveForward(0.01f);
    break;
  case 's':
    m_camera->MoveForward(-0.01f);
    break;
  case 'a':
    m_camera->MoveRight(-0.01f);
    break;
  case 'd':
    m_camera->MoveRight(0.01f);
    break;

  }
  return true;
}
