#pragma once
#include "pheader.h"
#include "Event.h"
namespace gfx
{
  class KeyEvent
      : public Event
  {
  public:
    KeyEvent(int keycode)
        : m_keyCode(keycode)
    {
    }

    inline int GetKeyCode() const { return m_keyCode; }

    EVENT_CLASS_CATEGORY(EventCategoryKeyBoard | EventCategoryInput);

  private:
    int m_keyCode;
  };

  class KeyPressedEvent
      : public KeyEvent
  {
  public:
    KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), m_repeatCount(repeatCount)
    {
    }

    EVENT_CLASS_TYPE(KeyPressed)

    inline int GetRepeatCount() const {return m_repeatCount;}
  private:
    int m_repeatCount;
  };

  class KeyReleasedEvent
      : public KeyEvent
  {
  public:
    KeyReleasedEvent(int keycode)
    :KeyEvent(keycode)
    {

    }
    EVENT_CLASS_TYPE(KeyReleased)
  private:
  };

} // namespace gfx
