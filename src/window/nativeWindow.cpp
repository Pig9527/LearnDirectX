
#include "nativeWindow.h"
#include "Context.h"
#include "imgui.h"
#include "KeyEvent.h"
#include "MouseEvent.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

static gfx::NativeWindow* sptrNativeWindow = nullptr;
LRESULT CALLBACK NativeWindowHandleProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (msg == WM_CREATE)
  {
    sptrNativeWindow = (gfx::NativeWindow*)(((LPCREATESTRUCT)(lParam))->lpCreateParams);
  }
  if (sptrNativeWindow)
  {
    return sptrNativeWindow->WindowHandleProc(hwnd,msg,wParam,lParam);
  }
  else
  {
    return DefWindowProc(hwnd,msg,wParam,lParam);
  }
}

gfx::NativeWindow::NativeWindow(const WindowInfo &info)
{
  m_windowInfo = info;

}

gfx::NativeWindow::~NativeWindow()
{
}

bool gfx::NativeWindow::Initialize()
{
  LPTSTR wndclassName = TEXT("gfxWndClass");
  WNDCLASS wnd = {};
  wnd.cbClsExtra = 0;
  wnd.cbWndExtra = 0;
  wnd.lpfnWndProc = NativeWindowHandleProc;
  wnd.hCursor = LoadCursor(nullptr,IDC_ARROW);
  wnd.hIcon = LoadIcon(nullptr,IDI_APPLICATION);
  wnd.lpszClassName = wndclassName;
  wnd.hInstance = GetModuleHandle(nullptr);
  wnd.lpszMenuName = 0; 
  wnd.style = CS_VREDRAW | CS_HREDRAW;
  wnd.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

  if (!RegisterClass(&wnd))
  {
    return false;
  }
  
  m_hwnd = CreateWindow(
    wndclassName,
    TEXT("DirectX-gfx"),
    WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,
    CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
    0,0,GetModuleHandle(nullptr),this
  );
  if (!m_hwnd)
  {
    return false;
  }
  Context::sHwnd = m_hwnd;
  ShowWindow(m_hwnd,SW_SHOW);
  UpdateWindow(m_hwnd);
  return true;
}

LRESULT CALLBACK gfx::NativeWindow::WindowHandleProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if(ImGui_ImplWin32_WndProcHandler(hwnd,msg,wParam,lParam))
  {
    return true;
  }
  switch (msg)
  {
  case WM_SIZE:
    Context::sWindowWidth = LOWORD(lParam);
    Context::sWindowHeight = HIWORD(lParam);
    return 0;
  case WM_LBUTTONDOWN:
  {
    MouseButtonPressedEvent event(1);
    m_callback(event);
  }
  case WM_LBUTTONUP:

  case WM_MOUSEMOVE:
  {
    int x = GET_X_LPARAM(lParam);
    int y = GET_Y_LPARAM(lParam);
    MouseMoveEvent event(x,y);
    m_callback(event);
  }
  case WM_MOUSEWHEEL:
  {
    
  }
  return 0;
  case WM_CHAR:
  {
    KeyPressedEvent e((int)wParam,1);
    m_callback(e);
  }
  return 0;
  case WM_DESTROY:
    Context::sbRunning = false;
    PostQuitMessage(0);
    return 0;
  }

  return DefWindowProc(hwnd,msg,wParam,lParam);
}
