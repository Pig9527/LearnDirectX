#pragma once

#include "pheader.h"

namespace gfx
{
  class Renderer
  {
    public:
      static void Init();
      static void Clear();
      static void DrawIndex(uint32_t cnt);
      static void Present();

  };
} // namespace gfx
