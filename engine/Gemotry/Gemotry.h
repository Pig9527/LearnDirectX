#pragma once
#include "pheader.h"
#include "vertex.h"
namespace gfx
{
  struct GemotryCube
  {

    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;
    
    inline void Create(int width, DirectX::XMFLOAT4& color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f})
    {
      using namespace DirectX;
      Vertices.resize(24);
      Indices.resize(36);
      float w2 = width / 2.0f,h2 = width / 2.0f,d2 = width / 2.0f;
       // 右面(+X面)
      Vertices[0].position = XMFLOAT3(w2, -h2, -d2);
      Vertices[1].position = XMFLOAT3(w2, h2, -d2);
      Vertices[2].position = XMFLOAT3(w2, h2, d2);
      Vertices[3].position = XMFLOAT3(w2, -h2, d2);
      // 左面(-X面)
      Vertices[4].position = XMFLOAT3(-w2, -h2, d2);
      Vertices[5].position = XMFLOAT3(-w2, h2, d2);
      Vertices[6].position = XMFLOAT3(-w2, h2, -d2);
      Vertices[7].position = XMFLOAT3(-w2, -h2, -d2);
      // 顶面(+Y面)
      Vertices[8].position = XMFLOAT3(-w2, h2, -d2);
      Vertices[9].position = XMFLOAT3(-w2, h2, d2);
      Vertices[10].position = XMFLOAT3(w2, h2, d2);
      Vertices[11].position = XMFLOAT3(w2, h2, -d2);
      // 底面(-Y面)
      Vertices[12].position = XMFLOAT3(w2, -h2, -d2);
      Vertices[13].position = XMFLOAT3(w2, -h2, d2);
      Vertices[14].position = XMFLOAT3(-w2, -h2, d2);
      Vertices[15].position = XMFLOAT3(-w2, -h2, -d2);
      // 背面(+Z面)
      Vertices[16].position = XMFLOAT3(w2, -h2, d2);
      Vertices[17].position = XMFLOAT3(w2, h2, d2);
      Vertices[18].position = XMFLOAT3(-w2, h2, d2);
      Vertices[19].position = XMFLOAT3(-w2, -h2, d2);
      // 正面(-Z面)
      Vertices[20].position = XMFLOAT3(-w2, -h2, -d2);
      Vertices[21].position = XMFLOAT3(-w2, h2, -d2);
      Vertices[22].position = XMFLOAT3(w2, h2, -d2);
      Vertices[23].position = XMFLOAT3(w2, -h2, -d2);
      for (UINT i = 0; i < 4; ++i)
      {
          // 右面(+X面)
          Vertices[i].normal = XMFLOAT3(1.0f, 0.0f, 0.0f);
          //Vertices[i].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
          Vertices[i].color = color;
          // 左面(-X面)
          Vertices[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
          //Vertices[i + 4].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
          Vertices[i + 4].color = color;
          // 顶面(+Y面)
          Vertices[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
          //Vertices[i + 8].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
          Vertices[i + 8].color = color;
          // 底面(-Y面)
          Vertices[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
          //Vertices[i + 12].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
          Vertices[i + 12].color = color;
          // 背面(+Z面)
          Vertices[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
          //Vertices[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
          Vertices[i + 16].color = color;
          // 正面(-Z面)
          Vertices[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
          //Vertices[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
          Vertices[i + 20].color = color;
      }
      for (UINT i = 0; i < 6; ++i)
      {
          Vertices[i * 4].uv = XMFLOAT2(0.0f, 1.0f);
          Vertices[i * 4 + 1].uv = XMFLOAT2(0.0f, 0.0f);
          Vertices[i * 4 + 2].uv = XMFLOAT2(1.0f, 0.0f);
          Vertices[i * 4 + 3].uv = XMFLOAT2(1.0f, 1.0f);
      }
      Indices = {
          0, 1, 2, 2, 3, 0,		// 右面(+X面)
          4, 5, 6, 6, 7, 4,		// 左面(-X面)
          8, 9, 10, 10, 11, 8,	// 顶面(+Y面)
          12, 13, 14, 14, 15, 12,	// 底面(-Y面)
          16, 17, 18, 18, 19, 16, // 背面(+Z面)
          20, 21, 22, 22, 23, 20	// 正面(-Z面)
      };
    }
  };
  
} // namespace gfx
