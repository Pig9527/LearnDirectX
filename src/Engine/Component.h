#pragma once

namespace gfx
{
  enum class ComponentType
  {
    Transform,
    StaticMesh,
    Camera,
    DirectionalLight,
    PointLight,
    SpotLight,
    Invalid
  };


  class IComponent
  {
    public:
      virtual void Update(){}
      virtual ComponentType GetType() const = 0;
  };

  template<ComponentType T>
  class BaseComponent:public IComponent
  {
    public:
    static inline constexpr ComponentType s_type = T;
    virtual ComponentType GetType() {return s_type;}
  };


} // namespace gfx
