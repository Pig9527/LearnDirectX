#include "LightComponent.h"

namespace gfx
{
  LightComponet::LightComponet()
    :Type(eLightType::Directional)
  {
  }
  LightComponet::LightComponet(eLightType type)
    :Type(type)
  {
  }
  std::string LightComponet::GetTypeName() const
  {
      return "LightComponent";
  }
} // namespace gfx
