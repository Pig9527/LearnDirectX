#pragma once
#include "pheader.h"
namespace gfx
{
  struct MeshDataInput
  {
    comptr<ID3D11InputLayout> pInputLayout = nullptr;
    D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
    std::vector<comptr<ID3D11Buffer>> pVertexBuffer;
    std::vector<uint32_t> strides;
    std::vector<uint32_t> offset;
    uint32_t indexCount = 0;  
  };

  class Effect
  {
    public:
      Effect() = default;
      ~Effect() = default;
      Effect(const Effect& rhs) = delete;
      Effect& operator=(const Effect& rhs) = delete;

      Effect(Effect&& rhs) = delete;
      Effect& operator=(Effect&& rhs) = delete;

      virtual void Apply() = 0;
  };
}
