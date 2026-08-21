#include "Entity.h"

namespace gfx
{
  void Entity::Update()
  {
    for (IComponent *component : m_components)
    {
      component->Update();
    }
  }

} // namespace  gfx
