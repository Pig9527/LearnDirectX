#pragma once
#include "pheader.h"

namespace gfx
{
    struct VertexPos
  {
    DirectX::XMFLOAT3 position;
    static inline D3D11_INPUT_ELEMENT_DESC sLayout[1] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}};

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };

  struct VertexPosColor
  {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;

    static inline D3D11_INPUT_ELEMENT_DESC sLayout[2] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };

  struct VertexPosUv
  {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT2 uv;

    static inline D3D11_INPUT_ELEMENT_DESC sLayout[2] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };

  struct VertexPosColorUv
  {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT4 color;
    DirectX::XMFLOAT2 uv;

    static inline D3D11_INPUT_ELEMENT_DESC sLayout[3] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    };

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };
  struct VertexPosUvNormal
  {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;

    static inline D3D11_INPUT_ELEMENT_DESC sLayout[3] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}};

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };

  struct VertexPosUvNormalTarget
  {
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 normal;
    DirectX::XMFLOAT2 uv;
    DirectX::XMFLOAT3 target;

    static inline D3D11_INPUT_ELEMENT_DESC sLayout[4] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TARGET", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}};

    static inline const uint32_t sLayoutNum = ARRAYSIZE(sLayout);
  };
}
