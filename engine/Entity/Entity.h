#pragma once
#include "pheader.h"
#include "Component.h"
namespace gfx
{
  
  class Entity
  {

    public:
    Entity() = default;
    ~Entity(){}

    void Update()
    {
      for(auto& component:m_components)
      {
        component->Update();
      }
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args)
    {
      T* component = new T(std::forward<Args>(args)...);
      m_components.push_back(component);
      return component;
    }

    private:
    std::vector<Component*> m_components;
  };
} // namespace gfx

