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


struct sMvp
{
  DirectX::XMMATRIX mvp;
};
sMvp mvp;
gfx::gfxConstantBuffer<sMvp> vertexConstant;
gfx::gfxVertexBuffer<gfx::VertexPosColorUv> vertexBuffer;
gfx::gfxIndexBuffer indexBuffer;
gfx::Model* pModel;

static float phi,theta;

void Render()
{
  phi += 0.0f *0.0016f; theta += 0.0f *0.0016f;

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
  mvp.mvp = projeect * view * world;

  vertexConstant.Upload(mvp);

  gfx::Renderer::DrawIndex(36);
}

int WINAPI wWinMain(HINSTANCE hInstacne, HINSTANCE hPreinstance, LPTSTR cmdline, int show)
{
  gfx::Application app;
  app.Init(TEXT("texture"));
  app.RenderCallback = Render;


  pModel = new gfx::ModelTexCoord();
  pModel->LoadModelFromFile("assets/model/cube.fbx");

#if 0
  using namespace DirectX;
  gfx::VertexPosColorUv vertices[] = {
    //font
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),XMFLOAT2{0.0f,1.0f}},
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,0.0f} },
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{1.0f,0.0f} },
    //back
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,1.0f} },
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{0.0f,0.0f}},
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) ,  XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT2{1.0f,0.0f} },

    //left
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,1.0f} },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{0.0f,0.0f}},
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) ,  XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT2{1.0f,0.0f} },

    //right
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,1.0f} },
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{0.0f,0.0f}},
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) ,  XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT2{1.0f,0.0f} },

    //top
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,1.0f} },
    { XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{0.0f,0.0f}},
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) ,  XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT2{1.0f,0.0f} },

    //down
    { XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2{0.0f,1.0f} },
    { XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) , XMFLOAT2{0.0f,0.0f}},
    { XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) ,  XMFLOAT2{1.0f,1.0f}},
    { XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),  XMFLOAT2{1.0f,0.0f} }
  };

 uint32_t indices[] = {
      0, 1, 2, 2, 3, 0,		// 右面(+X面)
      4, 5, 6, 6, 7, 4,		// 左面(-X面)
      8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
      12, 13, 14, 14, 15, 12,	// 底面(-Y面)
      16, 17, 18, 18, 19, 16, // 背面(+Z面)
      20, 21, 22, 22, 23, 20	// 正面(-Z面)
    };

#endif
 std::vector<gfx::VertexPosColorUv> vertices;
 vertices.resize(24);

 // 正方体的半边长
 float halfSize = 1.0f;

 // 顶点索引
 int index = 0;

 // 前面 (Z正方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 后面 (Z负方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 左面 (X负方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 右面 (X正方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 上面 (Y正方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize,  halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 下面 (Y负方向) - 4个顶点
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(-halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(0.0f, 0.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize, -halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 1.0f) };
 vertices[index++] = { DirectX::XMFLOAT3(halfSize, -halfSize,  halfSize), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT2(1.0f, 0.0f) };

 // 生成索引数组（36个索引，12个三角形，每个面2个三角形）
 std::vector<DWORD> indices;
 indices.resize(36);

 // 每个面的4个顶点构成2个三角形（共6个面，每个面6个索引）
 int triIndex = 0;
 for (int face = 0; face < 6; face++)
 {
   int baseIndex = face * 4;

   // 第一个三角形 (顶点0, 1, 2)
   indices[triIndex++] = baseIndex;
   indices[triIndex++] = baseIndex + 1;
   indices[triIndex++] = baseIndex + 2;

   // 第二个三角形 (顶点1, 3, 2)
   indices[triIndex++] = baseIndex + 1;
   indices[triIndex++] = baseIndex + 3;
   indices[triIndex++] = baseIndex + 2;
 }
  vertexBuffer.Create(vertices.size() *sizeof(gfx::VertexPosColorUv),vertices.data());
  vertexBuffer.Bind();
  indexBuffer.Create(indices.size(),indices.data());
  indexBuffer.Bind();

  gfx::gfxShaderVertex shaderVertex;
  shaderVertex.CompileFromFile("assets/shader/textureV.hlsl");
  shaderVertex.Bind();
  gfx::gfxShaderPixel shaderPixel;
  shaderPixel.CompileFromFile("assets/shader/textureP.hlsl");
  shaderPixel.Bind();

  gfx::gfxLayout<gfx::VertexPosColorUv> layout;
  layout.CreateLayout(shaderVertex.GetByteBlod());

  gfx::TextureDesc desc;
  desc.filePath = "assets/texture/container.jpg";
  gfx::gfxTexture texture(desc);
  texture.Create();
  texture.Bind();

  gfx::gfxRenderStateCache renderState;
  renderState.Init();
  gfx::gfxContext::Get().m_pDeviceContext->PSSetSamplers(0, 1, renderState.GetSampler(gfx::SamplerState::LinearClamp).GetAddressOf());


  //gfx::gfxContext::Get().m_pDeviceContext->OMSetDepthStencilState(renderState.GetDepthStencilState(gfx::DepthStencilState::Default).Get(), 1);

  vertexConstant.Create();
  gfx::gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0,1,vertexConstant.GetBuffer().GetAddressOf());
  
  app.Run();
}
