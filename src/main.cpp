#include "pheader.h"

#include "GameApp.h"
#include "Renderer.h"
#include "window/nativeWindow.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance, LPSTR cmdLine,int show)
{

  gfx::WindowInfo info;
  info.hinstance = hInstance;
  info.title = "cube";
  gfx::NativeWindow window(info);
  window.Initialize();
  
  gfx::Renderer::Init();

  gfx::GameApp* app = new gfx::GameApp();
  app->Init();


  // gfx::RenderTriangle* triangle = new gfx::RenderTriangle();

  // triangle->Init();

  // app->Add(triangle);

  app->Run();

  return 0;
}
