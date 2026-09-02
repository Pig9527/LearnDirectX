#pragma once
#include "pheader.h"
#include "gfxVertexBuffer.h"
#include "gfxIndexBuffer.h"
#include "gfxTexture.h"

namespace gfx
{

  struct sMeshCreateDesc
  {
    // stand normal diffuse spcular
    wchar_t* wTexFilePath[4];
    char* texFilePath[4];
    eTextureType type = eTextureType::DDS;

  };


  template<typename T>
  class Mesh
  {
    public:
      Mesh() = default;
      ~Mesh() = default;

      Mesh(const Mesh& rsh) = delete;
      Mesh& operator=(const Mesh& rsh) = delete;


    private:
  };
} // namespace gfx
