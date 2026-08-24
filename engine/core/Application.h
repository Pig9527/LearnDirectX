#pragma once
#include "pheader.h"
#include "Camera.h"
#include "ImguiLayer.h"
#include "gfxRenderState.h"
#include "Event/Event.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "gfxWhiteTexture.h"

namespace gfx
{
  class NativeWindow;

  using RenderFunc  = std::function<void()>;
  class Application
  {
    public:
    Application();
    ~Application();
    
    void Init(LPTSTR title);
    void OnEvent(Event& e);
    void Run();
    RenderFunc RenderCallback;
    private:
    
      bool OnMouseButtonDown(MouseButtonPressedEvent& e);
      bool OnKeyDown(KeyPressedEvent& e);
    private:
      
       std::shared_ptr<Camera> m_camera;
       std::unique_ptr<NativeWindow> m_window;
      // std::shared_ptr<gfxConstacntBufferManager> m_update2GPU;
      // std::shared_ptr<ImguiLayer> m_layer;
      // std::shared_ptr<gfxShaderProgram> m_shader;
      // std::shared_ptr<gfxLayout<VertexPosPosNormalUv>> m_layout;

      // std::unique_ptr<NativeWindow> m_window;
      // std::unique_ptr<gfxTexture> m_texture;
      // std::unique_ptr<gfxWhiteTexture> m_Deftexture;
      // std::unique_ptr<gfxRenderStateCache> m_renderState;
      // std::unique_ptr<Model<VertexPosPosNormalUv>> m_model;
   };
} // namespace gfx
