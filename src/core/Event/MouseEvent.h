#pragma once

#include "Event.h"

namespace gfx
{
  class MouseMoveEvent
      : public Event
  {
  public:
    MouseMoveEvent(float x, float y)
        : m_MouseX(x), m_MouseY(y)
    {
    }

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    EVENT_CLASS_TYPE(MouseMoved)
  private:
    float m_MouseX, m_MouseY;
  };

  class MouseScrolledEvent
      : public Event
  {
  public:
    MouseScrolledEvent(float xoffset, float yoffset)
        : m_xOffset(xoffset), m_yOffset(yoffset)
    {
    }

    inline float GetxOffset() const { return m_xOffset; }
    inline float GetyOffset() const { return m_yOffset; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    EVENT_CLASS_TYPE(MouseScrolled)
  private:
    float m_xOffset, m_yOffset;
  };

  class MouseButtonEvent
      : public Event
  {
  public:
    MouseButtonEvent(int button,int x,int y)
        : m_button(button)
        ,m_x(x)
        ,m_y(y)
    {
    }

    inline int GetMouseX()  const {return m_x;}
    inline int GetMouseY() const {return m_y;}
    inline int GetButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  private:
    int m_button;
    int m_x, m_y;
  };

  class MouseButtonPressedEvent
      : public MouseButtonEvent
  {
  public:
    MouseButtonPressedEvent(int button,int x,int y)
        : MouseButtonEvent(button,x,y)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent
      : public MouseButtonEvent
  {
  public:
    MouseButtonReleasedEvent(int button,int x,int y)
        : MouseButtonEvent(button,x,y)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
  };
} // namespace gfx
