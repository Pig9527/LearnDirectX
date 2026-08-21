#pragma once
#include "pheader.h"
namespace  gfx
{
  #define BIT(x) 1<<(x)
  enum class EventType
  {
    None = 0,
    KeyPressed,KeyReleased,
    MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled
  };

  enum EventCategory
  {
    None = 0,
    EventCategoryInput = BIT(0),
    EventCategoryKeyBoard = BIT(1),
    EventCategoryMouse = BIT(2),
    EventCategoryMouseButton = BIT(3)
  };

  #define EVENT_CLASS_TYPE(type)\
    static EventType GetStaticType() {return EventType::##type;} \
    virtual EventType GetEventType() const override {return GetStaticType();} \
    virtual const char* GetName() const override {return #type;}

  #define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override {return category;}

  class Event
  {
    public:
      virtual EventType GetEventType() const = 0;
      virtual const char* GetName() const = 0;
      virtual int GetCategoryFlags() const = 0;
      virtual std::string ToString() const {return GetName();}

      inline bool IsInCategory(EventCategory category)
      {
        return GetCategoryFlags() & category;
      }
      
      bool Handle = 0;
  };

  class EventDispatcher
  {
    public:
      template<typename T>
      using Eventfn = std::function<bool(T&)>;

      EventDispatcher(Event& event)
        :m_event(event)
        {}

        template<typename T>
        bool Dispatch(Eventfn<T> func)
        {
          if (m_event.GetEventType() == T::GetStaticType())
          {
            m_event.Handle = func(*(T*)&m_event);
            return true;
          }
          return false;
        }
    private:
     Event& m_event;
  };
} // namespace  gfx
