#pragma once
#include "pheader.h"
namespace gfx
{
  class ImguiLayer
  {
    public:
      void Attach();
      void Detach();

      void Render();

      static void Begin(char* title = "setting");
      static void End();

      static void RenderDefDirectLight();
      static void RenderDefPointLight();
      static void RenderDefSpotLight();
      static void RenderDefMaterial();

      static void RenderDefScene();


    private:
  };
} // namespace gfx
