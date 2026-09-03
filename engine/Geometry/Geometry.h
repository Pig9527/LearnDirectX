#pragma once
#include "pheader.h"
#include "vertex.h"
namespace gfx
{
  struct GeometryCube
  {

    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;
    
   void GenerateCube(int width, DirectX::XMFLOAT4& color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f});
  };
  
  struct GeometryPlane
  {
    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;
    DirectX::XMFLOAT3 Position{0.0f,0.0f,0.0f};
    DirectX::XMFLOAT3 Size{1.0f,1.0f,1.0f};

    void GeneratePlane();
  };

  struct GeometrySphere
  {
    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;
    float radius = 2.0f;
    int slices = 32;
    int stacks = 32;
     void GenerateSphere();
  };

  struct GeometryCylinder
  {
    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;

    float Radius = 1.0f;
    float Height = 1.0f;
    float Slices = 32.0f;
    float Stacks = 32.0f;
    void GenerateCylinder();
  };
} // namespace gfx
