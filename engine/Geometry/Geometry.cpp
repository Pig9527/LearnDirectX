#include "Geometry.h"

namespace gfx
{

  void GeometryCube::GenerateCube(int width, DirectX::XMFLOAT4 &color /*= DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f}*/)
  {
    using namespace DirectX;
    Vertices.resize(24);
    Indices.resize(36);
    float w2 = width / 1.0f, h2 = width / 1.0f, d2 = width / 1.0f;
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
      // Vertices[i].tangent = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
      Vertices[i].color = color;
      // 左面(-X面)
      Vertices[i + 4].normal = XMFLOAT3(-1.0f, 0.0f, 0.0f);
      // Vertices[i + 4].tangent = XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f);
      Vertices[i + 4].color = color;
      // 顶面(+Y面)
      Vertices[i + 8].normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
      // Vertices[i + 8].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
      Vertices[i + 8].color = color;
      // 底面(-Y面)
      Vertices[i + 12].normal = XMFLOAT3(0.0f, -1.0f, 0.0f);
      // Vertices[i + 12].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
      Vertices[i + 12].color = color;
      // 背面(+Z面)
      Vertices[i + 16].normal = XMFLOAT3(0.0f, 0.0f, 1.0f);
      // Vertices[i + 16].tangent = XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f);
      Vertices[i + 16].color = color;
      // 正面(-Z面)
      Vertices[i + 20].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
      // Vertices[i + 20].tangent = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
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
        0, 1, 2, 2, 3, 0,       // 右面(+X面)
        4, 5, 6, 6, 7, 4,       // 左面(-X面)
        8, 9, 10, 10, 11, 8,    // 顶面(+Y面)
        12, 13, 14, 14, 15, 12, // 底面(-Y面)
        16, 17, 18, 18, 19, 16, // 背面(+Z面)
        20, 21, 22, 22, 23, 20  // 正面(-Z面)
    };
  }

  void GeometryPlane::GeneratePlane()
  {
    Vertices.resize(4);
    Indices.resize(6);
    float width ;
    Size.x == Size.z ? width = std::max(Size.x,Size.z): width = Size.x;
    float halfWidth = width / 2.0f;
    /*
      1    2
      |----|
      |    |
      |----|
      4    3
    */
    Vertices[0].position = DirectX::XMFLOAT3{Position.x - halfWidth, Position.y, Position.z + halfWidth};
    Vertices[1].position = DirectX::XMFLOAT3{Position.x + halfWidth, Position.y, Position.z + halfWidth};
    Vertices[2].position = DirectX::XMFLOAT3{Position.x + halfWidth, Position.y, Position.z - halfWidth};
    Vertices[3].position = DirectX::XMFLOAT3{Position.x - halfWidth, Position.y, Position.z - halfWidth};

    Vertices[0].color = DirectX::XMFLOAT4{1.0f, 1.0f, 1.0f, 1.0f};
    Vertices[1].color = DirectX::XMFLOAT4{1.0f, 1.0f, 1.0f, 1.0f};
    Vertices[2].color = DirectX::XMFLOAT4{1.0f, 1.0f, 1.0f, 1.0f};
    Vertices[3].color = DirectX::XMFLOAT4{1.0f, 1.0f, 1.0f, 1.0f};

    Vertices[0].normal = DirectX::XMFLOAT3{0.0f, 1.0f, 0.0f};
    Vertices[1].normal = DirectX::XMFLOAT3{0.0f, 1.0f, 0.0f};
    Vertices[2].normal = DirectX::XMFLOAT3{0.0f, 1.0f, 0.0f};
    Vertices[3].normal = DirectX::XMFLOAT3{0.0f, 1.0f, 0.0f};

    Vertices[0].uv = DirectX::XMFLOAT2{0.0f, 1.0f};
    Vertices[1].uv = DirectX::XMFLOAT2{1.0f, 1.0f};
    Vertices[2].uv = DirectX::XMFLOAT2{1.0f, 0.0f};
    Vertices[3].uv = DirectX::XMFLOAT2{0.0f, 0.0f};

    Indices[0] = 0;
    Indices[1] = 1;
    Indices[2] = 2;
    Indices[3] = 2;
    Indices[4] = 3;
    Indices[5] = 0;
  }
  void GeometrySphere::GenerateSphere()
  {
    // 1. 生成顶点
    for (int i = 0; i <= stacks; ++i)
    {
      float phi = i * DirectX::XM_PI / stacks; // 从0到PI（北极到南极）
      float y = radius * cosf(phi);
      float r = radius * sinf(phi);

      for (int j = 0; j <= slices; ++j)
      {
        float theta = j * 2.0f * DirectX::XM_PI / slices; // 从0到2PI（环绕一周）
        float x = r * sinf(theta);
        float z = r * cosf(theta);

        VertexPosColorNormalUv vertex;
        vertex.position = DirectX::XMFLOAT3(x, y, z);

        // 纹理坐标（用于可能需要的贴图）
        vertex.uv = DirectX::XMFLOAT2(
            (float)j / slices,
            (float)i / stacks);

        vertex.color = DirectX::XMFLOAT4{1.0f, 1.0f, 1.0f, 1.0f};

        // 法线（归一化的位置向量）
        DirectX::XMVECTOR pos = DirectX::XMLoadFloat3(&vertex.position);
        DirectX::XMVECTOR norm = DirectX::XMVector3Normalize(pos);
        DirectX::XMStoreFloat3(&vertex.normal, norm);

        Vertices.push_back(vertex);
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

  void GeometryCylinder::GenerateCylinder()
  {
    Vertices.clear();
    Indices.clear();
    Height = Radius * 4.0f;
    // 1. 顶点数据生成（包括上下底面和侧面）
    // 顶部圆心
    Vertices.push_back({DirectX::XMFLOAT3(0.0f, Height * 0.5f, 0.0f),
                        DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
                        DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
                        DirectX::XMFLOAT2(0.5f, 1.0f)}); // 索引0

    // 底部圆心
    Vertices.push_back({
        DirectX::XMFLOAT3(0.0f, -Height * 0.5f, 0.0f),
        DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
        DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f),
        DirectX::XMFLOAT2(0.5f, 0.0f),
    }); // 索引1

    // 生成环绕顶点 (侧面 + 上下底面的边缘)
    // 为了UV和法线正确，侧面顶点和底面/顶面边缘顶点需要分开处理
    // 这里采用更清晰的方式：分别生成侧面、顶面、底面的顶点

    // --- 侧面顶点 ---
    int sideStartIndex = (int)Vertices.size();
    for (int i = 0; i <= Slices; ++i)
    {
      float theta = (float)i / Slices * DirectX::XM_2PI;
      float x = Radius * cosf(theta);
      float z = Radius * sinf(theta);

      // 法线：从圆柱轴向外（忽略高度方向）
      DirectX::XMFLOAT3 normal = DirectX::XMFLOAT3(cosf(theta), 0.0f, sinf(theta));

      // UV: u沿环绕方向，v沿高度方向
      float u = (float)i / Slices;
      float vBottom = 0.0f;
      float vTop = 1.0f;

      // 底部边缘顶点
      Vertices.push_back({
          DirectX::XMFLOAT3(x, -Height * 0.5f, z),
          DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
          normal,
          DirectX::XMFLOAT2(u, vBottom),
      });
      // 顶部边缘顶点
      Vertices.push_back({
          DirectX::XMFLOAT3(x, Height * 0.5f, z),
          DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
          normal,
          DirectX::XMFLOAT2(u, vTop),
      });
    }

    // --- 顶面顶点（不包括圆心，边缘顶点与侧面共享位置但法线不同，这里独立生成）---
    // 为了简化，顶面和底面使用独立的边缘顶点（法线朝上/朝下），不与侧面顶点共享
    // 这样法线正确但顶点数稍多
    int topStartIndex = (int)Vertices.size();
    for (int i = 0; i <= Slices; ++i)
    {
      float theta = (float)i / Slices * DirectX::XM_2PI;
      float x = Radius * cosf(theta);
      float z = Radius * sinf(theta);
      float u = 0.5f + 0.5f * cosf(theta);
      float v = 0.5f + 0.5f * sinf(theta);
      // 顶面法线朝上
      Vertices.push_back({
          DirectX::XMFLOAT3(x, Height * 0.5f, z),
          DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
          DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
          DirectX::XMFLOAT2(u, v),
      });
    }

    // --- 底面顶点（不包括圆心）---
    int bottomStartIndex = (int)Vertices.size();
    for (int i = 0; i <= Slices; ++i)
    {
      float theta = (float)i / Slices * DirectX::XM_2PI;
      float x = Radius * cosf(theta);
      float z = Radius * sinf(theta);
      float u = 0.5f + 0.5f * cosf(theta);
      float v = 0.5f + 0.5f * sinf(theta);
      // 底面法线朝下
      Vertices.push_back({DirectX::XMFLOAT3(x, -Height * 0.5f, z),
                          DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
                          DirectX::XMFLOAT3(0.0f, -1.0f, 0.0f),
                          DirectX::XMFLOAT2(u, v)});
    }

    // 2. 索引生成
    // --- 侧面索引 (两个三角形组成一个四边形) ---
    for (int i = 0; i < Slices; ++i)
    {
      int bottomLeft = sideStartIndex + i * 2;
      int topLeft = sideStartIndex + i * 2 + 1;
      int bottomRight = sideStartIndex + (i + 1) * 2;
      int topRight = sideStartIndex + (i + 1) * 2 + 1;

      // 三角形1: 左下-右下-左上
      Indices.push_back(bottomLeft);
      Indices.push_back(bottomRight);
      Indices.push_back(topLeft);

      // 三角形2: 右下-右上-左上
      Indices.push_back(bottomRight);
      Indices.push_back(topRight);
      Indices.push_back(topLeft);
    }

    // --- 顶面索引 (扇形) ---
    // 顶点顺序: 圆心(索引0) -> 边缘顶点 (topStartIndex 到 topStartIndex+Slices)
    for (int i = 0; i < Slices; ++i)
    {
      int center = 0; // 顶部圆心
      int p1 = topStartIndex + i;
      int p2 = topStartIndex + i + 1;
      Indices.push_back(center);
      Indices.push_back(p1);
      Indices.push_back(p2);
    }

    // --- 底面索引 (扇形) ---
    // 顶点顺序: 圆心(索引1) -> 边缘顶点 (bottomStartIndex 到 bottomStartIndex+Slices)
    for (int i = 0; i < Slices; ++i)
    {
      int center = 1; // 底部圆心
      int p1 = bottomStartIndex + i;
      int p2 = bottomStartIndex + i + 1;
      Indices.push_back(center);
      Indices.push_back(p2);
      Indices.push_back(p1); // 注意顺序使法线朝下
    }
  }

} // namespace gfx
