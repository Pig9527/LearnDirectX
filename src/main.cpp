#include "pheader.h"

#include "GameApp.h"
#include "Renderer.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance, LPSTR cmdLine,int show)
{

  gfx::GameApp* app = new gfx::GameApp();
  app->Init();



  // gfx::RenderTriangle* triangle = new gfx::RenderTriangle();

  // triangle->Init();

  // app->Add(triangle);

  app->Run();

  return 0;
}
