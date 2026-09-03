#include "ColorComponent.h"
namespace gfx{
  ColorComponent::ColorComponent()
    :Color(DirectX::XMFLOAT4{1.0f,1.0f,1.0f,1.0f})
  {

  }

  ColorComponent::ColorComponent(const DirectX::XMFLOAT4 &color)
    :Color(color)
  {
    
  }
  std::string ColorComponent::GetTypeName() const
  {
      return "ColorComponent";
  }
}
