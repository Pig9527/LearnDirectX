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
    MouseButtonEvent(int button)
        : m_button(button)
    {
    }
    inline int GetButton() const { return m_button; }

    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
  private:
    int m_button;
  };

  class MouseButtonPressedEvent
      : public MouseButtonEvent
  {
  public:
    MouseButtonPressedEvent(int button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
  };

  class MouseButtonReleasedEvent
      : public MouseButtonEvent
  {
  public:
    MouseButtonReleasedEvent(int button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
  };
} // namespace gfx
