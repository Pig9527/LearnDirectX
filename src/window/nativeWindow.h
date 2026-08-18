#pragma once

#include "pheader.h"

namespace gfx
{

  struct WindowInfo
  {
    char* title;
    HINSTANCE hinstance;
    int width;
    int height;
  };

  class NativeWindow
  {
    public:
      NativeWindow(const WindowInfo& info);
      ~NativeWindow();

      bool Initialize();

      LRESULT CALLBACK WindowHandleProc(HWND hwnd, UINT msg,WPARAM wParam,LPARAM lParam);
    private:
      HWND m_hwnd;
      WindowInfo m_windowInfo;
  };
}
