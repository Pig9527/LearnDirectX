#pragma once

#include "pheader.h"
#include "Event.h"

namespace gfx
{

  using EventCallbackFn  = std::function<void(Event&)>;
  struct WindowInfo
  {
    LPTSTR title;
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
      void SetEventCallback(EventCallbackFn fn) {m_callback = fn;}

      LRESULT CALLBACK WindowHandleProc(HWND hwnd, UINT msg,WPARAM wParam,LPARAM lParam);
    private:
      HWND m_hwnd;
      WindowInfo m_windowInfo;
      EventCallbackFn m_callback; 
  };
}
