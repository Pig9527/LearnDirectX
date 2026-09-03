#pragma once
#include "pheader.h"
#include "Component.h"
#include "core/Context.h"
namespace gfx
{
  class MaterialComponent
    :public Component
  {
    public:
    MaterialComponent();
    sMaterial Material;
  };
} // namespace gfx
