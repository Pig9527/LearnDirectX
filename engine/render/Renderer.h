#pragma once

#include "pheader.h"
#include "gfxConstantBuffer.h"

namespace gfx
{

  struct sVertexConstant
  {
    DirectX::XMMATRIX mvp;
    DirectX::XMMATRIX World;
    DirectX::XMMATRIX View;
    DirectX::XMMATRIX Project;
    DirectX::XMMATRIX WorldInvTranspose;
  };

  class Renderer
  {
    public:
      static void Init();
      static void Clear();
      static void DrawIndex(uint32_t cnt);
      static void Draw(uint32_t cnt);
      static void Present();

      static void UploadMvp();
      static sVertexConstant VertexConstantBuffer;
      static gfxConstantBuffer<sVertexConstant> VertexShaderConstantTransformObj;
    };
} // namespace gfx
