#pragma once
#include "pheader.h"
namespace  gfx
{
  class Component
  {
    public:
    virtual ~Component() =default;

    virtual void Update() {}
  };


  class ColorComponent
    :public Component
  { 
    public:
    
    DirectX::XMFLOAT4 Color;
  };

} // namespace  gfx
