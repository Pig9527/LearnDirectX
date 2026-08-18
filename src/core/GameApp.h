#pragma once
#include "pheader.h"
#include "Camera.h"
#include "gfxConstantBufferManager.h"
#include "ImguiLayer.h"
#include "Gemotry/Geometry.h"
#include "gfxShaderProgram.h"
#include "gfxLayout.h"
#include "Model.h"
#include "gfxTexture.h"
#include "gfxRenderState.h"
namespace gfx
{
  class GameApp
  {
    public:
    GameApp();
    ~GameApp();
    
    void Init();
    void Run();
    void Render();

    void Begin();

    void end();
    private:
      std::shared_ptr<Camera> m_camera;
      std::shared_ptr<gfxConstacntBufferManager> m_update2GPU;
      std::shared_ptr<ImguiLayer> m_layer;
      std::shared_ptr<gfxShaderProgram> m_shader;
      std::shared_ptr<gfxLayout<VertexPosPosNormalUv>> m_layout;

      std::unique_ptr<gfxTexture> m_texture;
      std::unique_ptr<gfxRenderStateCache> m_renderState;
      std::unique_ptr<Model<VertexPosPosNormalUv>> m_model;
   };
} // namespace gfx
