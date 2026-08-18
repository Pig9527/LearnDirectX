#include "GameApp.h"
#include "Context.h"
#include "gfxConstantBufferManager.h"
#include "Renderer.h"


gfx::GameApp::GameApp()
{
}

gfx::GameApp::~GameApp()
{
}

void gfx::GameApp::Init()
{

  m_renderState = std::make_unique<gfxRenderStateCache>();
  m_renderState->Init();

  std::wostringstream vertexPath(TEXT("assets/shader/baseVertex.hlsl"));
  std::wostringstream PixelPath(TEXT("assets/shader/basePixel.hlsl"));
  m_shader = std::make_shared<gfxShaderProgram>();
  m_shader->Init("assets/shader/baseVertex.hlsl", "assets/shader/basePixel.hlsl");
  m_shader->Bind();

  m_layout = std::make_unique<gfxLayout<VertexPosColorUv>>();
  m_layout->CreateLayout(m_shader->GetVertexShader()->GetBlod());

  m_model = std::make_unique<Model<VertexPosColorUv>>();
 // m_model->LoadModelFromFile("assets/model/BOSS_model_final.fbx");
  m_model->LoadModelFromFile("assets/backpack/backpack.obj");
  m_model->Create();


  TextureDesc desc;
  desc.filePath = "assets/backpack/diffuse.jpg";
  m_texture = std::make_unique<gfxTexture>(desc);
  m_texture->Create();

  auto& sampler =  m_renderState->GetSampler(SamplerState::LinearClamp);
  gfxContext::Get().m_pDeviceContext->PSSetSamplers(0,1,sampler.GetAddressOf());


  m_update2GPU = std::make_shared<gfxConstacntBufferManager>();
  m_update2GPU->Bind();

  m_camera = std::make_shared<Camera>();
  m_camera->CalculateProjectView();

  m_layer = std::make_shared<ImguiLayer>();
  m_layer->Attach();
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
    }
  }
}

void gfx::GameApp::Render()
{

  this->Begin();

  DirectX::XMMATRIX mod = DirectX::XMMatrixIdentity();
  mod = DirectX::XMMatrixTranspose(
    DirectX::XMMatrixScalingFromVector(DirectX::XMVectorReplicate(m_layer->scale))*
    DirectX::XMMatrixRotationX(m_layer->phi) *
    DirectX::XMMatrixRotationY(m_layer->theta)*
    DirectX::XMMatrixTranslation(m_layer->tx,m_layer->ty,0.0f)
  );

  DirectX::XMMATRIX mvp = m_camera->GetProjectVeiwMatrix() * mod;
  PerFrameData data;
  data.mvp = mvp;
  m_update2GPU->UploadPerFrameToVS(data);
  MaterialData material;
  material.color = m_layer->GetColor();

  m_update2GPU->UploadMaterialToPS(material);

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
