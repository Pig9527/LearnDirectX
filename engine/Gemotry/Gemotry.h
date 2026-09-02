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
  
  struct GemotryPlane
  {
    std::vector<VertexPosColorNormalUv> Vertices;
    std::vector<uint32_t> Indices;

    void Create(DirectX::XMFLOAT3 position, DirectX::XMFLOAT3 size, DirectX::XMFLOAT3 rotate = DirectX::XMFLOAT3{ 0.0f,0.0f,0.0f }, DirectX::XMFLOAT3& transform = DirectX::XMFLOAT3{0.0f,0.0f,0.0f}, const DirectX::XMFLOAT4& color = DirectX::XMFLOAT4{ 1.0f,1.0f,1.0f,1.0f })
    {
      Vertices.resize(4);
      Indices.resize(6);
      //float w2 = size.x / 2.0f;
      //float h2 = size.y / 2.0f;
      //float d2 = size.z / 2.0f;
#if 1

#if 0
      Vertices[0].position = DirectX::XMFLOAT3{position.x + w2,position.y - h2,position.z - d2 };
      Vertices[1].position = DirectX::XMFLOAT3{position.x + w2,position.y - h2,position.z + d2};
      Vertices[2].position = DirectX::XMFLOAT3{position.x - w2,position.y - h2,position.z + d2};
      Vertices[3].position = DirectX::XMFLOAT3{position.x - w2,position.y - h2,position.z - d2};
#else
      /*
        1    2
        |----|
        |    |
        |----|
        4    3
      */
      Vertices[0].position = DirectX::XMFLOAT3{ position.x,position.y,position.z};
      Vertices[1].position = DirectX::XMFLOAT3{ position.x + size.x,position.y,position.z };
      Vertices[2].position = DirectX::XMFLOAT3{ position.x + size.x,position.y,position.z - size.z};
      Vertices[3].position = DirectX::XMFLOAT3{ position.x,position.y,position.z - size.z};

#endif
      DirectX::XMMATRIX translation = DirectX::XMMatrixTranslation(transform.x, transform.y, transform.z);

      DirectX::XMMATRIX rotateMatrix = DirectX::XMMatrixRotationRollPitchYaw(rotate.x, rotate.y, rotate.z);
      
      DirectX::XMMATRIX world = rotateMatrix * translation;
     
      for (int i =0;i<4;i++)
      {
        DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&Vertices[i].position);
        pos = DirectX::XMVector3Transform(pos, world);
        DirectX::XMStoreFloat3(&Vertices[i].position, pos);
#if 0
        
        DirectX::XMVECTOR translate = DirectX::XMVector3Transform(pos, translation);
        DirectX::XMVECTOR rotateVec = DirectX::XMLoadFloat3(&rotate);

        DirectX::XMVECTOR quat = DirectX::XMQuaternionRotationAxis(rotateVec, DirectX::XMConvertToRadians(angle));
        DirectX::XMVECTOR result = DirectX::XMVector3Rotate(translate, quat);

        //DirectX::XMVECTOR result = DirectX::XMVectorMultiply(rotate,translate);
        DirectX::XMStoreFloat3(&Vertices[i].position, result);
#endif

      }

#else 
      Vertices[0].position = DirectX::XMFLOAT3{ -50.0f, 10.0f, -50.0f }; // 左上
      Vertices[1].position = DirectX::XMFLOAT3{ 50.0f, 10.0f, -50.0f }; // 右上
      Vertices[2].position = DirectX::XMFLOAT3{ 50.0f, 10.0f,  50.0f }; // 右下
      Vertices[3].position = DirectX::XMFLOAT3{ -50.0f, 10.0f,  50.0f }; // 左下

#endif
      // Vertices[0].position =
      // DirectX::XMMatrixTranslation()
      // DirectX::XMMatrixIdentity() * DirectX::XMFLOAT3(1.0f,1.0f,0.0f);
     
      Vertices[0].color = color;
      Vertices[1].color = color;
      Vertices[2].color = color;
      Vertices[3].color = color;

      Vertices[0].normal = DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f };
      Vertices[1].normal = DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f };
      Vertices[2].normal = DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f };
      Vertices[3].normal = DirectX::XMFLOAT3{ 0.0f, 1.0f, 0.0f };
#if 0
      Vertices[0].uv = DirectX::XMFLOAT2{0.0f,0.0f};
      Vertices[1].uv = DirectX::XMFLOAT2{1.0f,0.0f};
      Vertices[2].uv = DirectX::XMFLOAT2{1.0f,1.0f};
      Vertices[3].uv = DirectX::XMFLOAT2{0.0f,1.0f};
#else
      Vertices[0].uv = DirectX::XMFLOAT2{ 0.0f,1.0f };
      Vertices[1].uv = DirectX::XMFLOAT2{ 1.0f,1.0f };
      Vertices[2].uv = DirectX::XMFLOAT2{ 1.0f,0.0f };
      Vertices[3].uv = DirectX::XMFLOAT2{ 0.0f,0.0f };
#endif
      Indices[0] = 0;Indices[1] = 1;Indices[2] = 2;
      Indices[3] = 2;Indices[4] = 3;Indices[5] = 0;
    }
  };




  struct GeometrySphere
  {
    std::vector<VertexPosColorNormalUv> Verteices;
    std::vector<uint32_t> Indices;
    float radius = 2.0f;
    int slices = 32;
    int stacks = 32;
    void Create()
    {
        // 1. 生成顶点
      for (int i = 0; i <= stacks; ++i)
      {
        float phi = i * DirectX::XM_PI / stacks;  // 从0到PI（北极到南极）
        float y = radius * cosf(phi);
        float r = radius * sinf(phi);
        
        for (int j = 0; j <= slices; ++j)
        {
            float theta = j * 2.0f * DirectX::XM_PI / slices;  // 从0到2PI（环绕一周）
            float x = r * sinf(theta);
            float z = r * cosf(theta);
            
            VertexPosColorNormalUv vertex;
            vertex.position = DirectX::XMFLOAT3(x, y, z);
            
            // 纹理坐标（用于可能需要的贴图）
            vertex.uv = DirectX::XMFLOAT2(
                (float)j / slices,
                (float)i / stacks
            );
            
            vertex.color = DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f};

            // 法线（归一化的位置向量）
            DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&vertex.position);
            DirectX::XMVECTOR norm = DirectX::XMVector3Normalize(pos);
            DirectX::XMStoreFloat3(&vertex.normal, norm);
            
            Verteices.push_back(vertex);
        }
      }

      // 2. 生成索引
      for (int i = 0; i < stacks; ++i)
      {
        for (int j = 0; j < slices; ++j)
        {
            int a = i * (slices + 1) + j;
            int b = a + slices + 1;
            
            // 两个三角形组成一个四边形
            Indices.push_back(a);
            Indices.push_back(b);
            Indices.push_back(a + 1);
            
            Indices.push_back(b);
            Indices.push_back(b + 1);
            Indices.push_back(a + 1);
        }
      }
    }
  };
} // namespace gfx
