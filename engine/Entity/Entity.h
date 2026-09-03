#pragma once
#include "pheader.h"
#include "Component.h"
namespace gfx
{
  
  class Entity
  {

    public:
    Entity();
    explicit Entity(const std::string& name);

    ~Entity();

    void Update();
    void ClearComponents();

    template<typename T, typename... Args>
    std::shared_ptr<T> AddComponent(Args&&... args);

    template<typename T>
    std::shared_ptr<T> GetComponent() const;

    template<typename T>
    bool HasComponent() const;

    template<typename T>
    bool RemoveComponent();


    private:
      static uint64_t s_nextID;
      std::string m_name ="Unnamed";
      uint64_t m_id;
      std::vector<std::shared_ptr<Component>> m_components;
  };

  inline uint64_t Entity::s_nextID = 1;
  Entity::Entity()
  :m_id(s_nextID++)
  {}
  Entity::Entity(const std::string& name)
  :m_name(name),m_id(s_nextID++)
  {}

  Entity::~Entity()
  {
    ClearComponents();
  }

  void Entity::Update()
  {
    for(auto& comp : m_components)
    {
      comp->Update();
    }
  }
  void Entity::ClearComponents()
  {
    for(auto& comp : m_components)
    {
      comp->OnDetach();
    }
    m_components.clear();
  }


  template <typename T, typename... Args>
  inline std::shared_ptr<T> Entity::AddComponent(Args &&...args)
  {
    static_assert(std::is_base_of<Component,T>::value,"T must be derivered from Component");
    auto component = std::make_shared<T>(std::forward<Args>(args)...);
    component->SetOwner(this);
    m_components.push_back(component);
    component->OnAttach();
    return component;
  }
  template <typename T>
  inline std::shared_ptr<T> Entity::GetComponent() const
  {
    static_assert(std::is_base_of<Component,T>::value,"T must be derivered from Component");
    
    for(auto& component :m_components)
    {
      std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(component);
      if(ptr) return ptr;
    }
    return nullptr;
  }

  template <typename T>
  inline bool Entity::HasComponent() const
  {
    return GetComponent<T>() != nullptr;
  }
  template <typename T>
  inline bool Entity::RemoveComponent()
  {
    static_assert(std::is_base_of<Component,T>::value,"T must be derivered from Component");
    auto it = std::find_if(m_components.begin(),m_components.end(),[](const std::shared_ptr<Component>& comp)
    {
      return dynamic_cast<T*>(comp.get()) != nullptr;
    });

    if(it != m_components.end())
    {
      (*it)->OnDetach();
      m_components.erase(it);
      return true;
    }
    return false;
  }
} // namespace gfx
