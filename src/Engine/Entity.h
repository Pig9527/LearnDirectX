#pragma once
#include "pheader.h"
#include "Component.h"
namespace gfx
{
  class Entity
  {
  public:
    Entity();
    ~Entity();

    void Update();

    template <typename T, typename... Args>
    T *AddComponent(Args &&...args);

    template <typename T>
    T *GetComponent();

    template <typename T>
    bool HasComponent();

    template <typename T>
    bool RemoveComponent();

  private:
    std::vector<IComponent*> m_components;
  };

} // namespace gfx

#include "Enitty.inl"
