#pragma once
#include "pheader.h"
#include "Component.h"

namespace gfx
{
  class ColorComponent
   :public Component
  {
    public:
      ColorComponent();
      ColorComponent(const DirectX::XMFLOAT4& color);

      std::string GetTypeName() const override;

    DirectX::XMFLOAT4 Color;
    
  };
} // namespace gfx
