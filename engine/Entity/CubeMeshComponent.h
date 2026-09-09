#pragma once
#include "pheader.h"
#include "Component.h"
#include "Vertex.h"
namespace  gfx
{
  class CubeMeshComponent
    :public Component
  {
    public:

    void Create();
    DirectX::XMFLOAT3 Size;
    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;
  };
  
} // namespace  gfx
