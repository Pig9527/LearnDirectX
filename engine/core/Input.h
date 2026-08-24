#pragma once

#include "pheader.h"

namespace gfx
{
  class Input
  {
  public:
    static bool IsKeyPressed(int keycode)
    {
      for (int i = 0; i < 256; i++)
      {
        if (GetAsyncKeyState(keycode) & 0x8000)
        {
          return true;
        }
      }
      return false;
    }

  private:
    static std::array<bool, 256> s_keys;
  };

  std::array<bool, 256> Input::s_keys = {false};
}