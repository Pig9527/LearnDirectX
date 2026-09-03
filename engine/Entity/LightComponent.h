#pragma once
#include "Component.h"
#include "core/Context.h"
namespace gfx
{
  class LightComponet
    :public Component
  {
    public:
    enum class eLightType
    {
      Directional,Point,Spot,Ambient
    };

    LightComponet();
    LightComponet(eLightType type);

    std::string GetTypeName() const override;
    eLightType Type;
    sDirectLight DirectialLight;
    sSpotLight SpotLight;
    sPointLight PointLight;
  };
} // namespace gfx
