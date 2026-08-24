
#pragma once
#include "pheader.h"
#include "core/Application.h"
#include "Graphic/gfxContext.h"
#include "gemotry/Vertex.h"
#include "Graphic/gfxVertexBuffer.h"
#include "Graphic/gfxIndexBuffer.h"
#include "Graphic/gfxLayout.h"
#include "Graphic/gfxShader.h"
#include "Graphic/gfxShaderPixel.h"
#include "Graphic/gfxShaderVertex.h"

void Render()
{
  gfx::gfxContext::Get().m_pDeviceContext->Draw(3,0);
}

int WINAPI WinMain(HINSTANCE hPreinstance,HINSTANCE hInstacne,PTSTR cmdline, int show)
{
  gfx::Application app;
  app.Init("Render A Triangle");
  app.RenderCallback = Render;

  gfx::VertexPosColor vertices[] ={
    DirectX::XMFLOAT3{-0.5f,-0.5f,0.0f},DirectX::XMFLOAT4{1.0f,0.0f,0.0f,1.0f},
    DirectX::XMFLOAT3{0.0f,0.5f,0.0f},DirectX::XMFLOAT4{0.0f,1.0f,0.0f,1.0f},
    DirectX::XMFLOAT3{0.5f,-0.5f,0.0f},DirectX::XMFLOAT4{0.0f,0.0f,1.0f,1.0f}
  };
  gfx::gfxVertexBuffer<gfx::VertexPosColor> VertexBuff;
  VertexBuff.Create(sizeof(vertices),vertices);
  VertexBuff.Bind();
  
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

