#pragma once
#include "pheader.h"
namespace  gfx
{
  class Entity;
  class Component
  {
    public:
    virtual ~Component() =default;

    void SetOwner(Entity* ownder) {m_Owner = ownder;}

    virtual void Update() {}
    virtual void OnAttach(){}
    virtual void OnDetach(){}

    virtual std::string GetTypeName() const{return "Compoennt";}
    protected:
    Entity* m_Owner;
  };
} // namespace  gfx
