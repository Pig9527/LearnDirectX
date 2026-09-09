#pragma once
#include "pheader.h"
#include "Component.h"
namespace gfx
{
  class ShaderComponent
    :public Component
  {
    public:
    ShaderComponent(const std::string& name)
    :Name(name){}
    std::string Name;
  };
}
