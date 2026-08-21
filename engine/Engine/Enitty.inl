#pragma once
#include "Entity.h"
namespace gfx
{
  template <typename T, typename... Args>
  T *Entity::AddComponent(Args &&...args)
  {
    T* component = new T(std::forward<Args>(args)...);
    m_components.push_back(component);
    return component;
  }

  template <typename T>
  T * Entity::GetComponent()
  {
    for (IComponent* component:m_components)
    {
      if (component->GetType() == T)
      {
        return (T*)component;
      }
    }
  }

  template <typename T>
  bool Entity::HasComponent()
  {
   for (IComponent* component:m_components)
    {
      if (component->GetType() == T)
      {
        return true;
      }
    }
    return false;
  }

  template <typename T>
  bool Entity::RemoveComponent()
  {
    IComponent* temp = nullptr;
    for (IComponent* component:m_components)
    {
      if (component->GetType() == T)
      {
        temp = component;
      }
    }
    if (temp)
    {
      m_components.pop_back(temp);
      return true;
    }
    return false;
  }
} // namespace gfx
