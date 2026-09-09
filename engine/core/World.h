#pragma once

#include "pheader.h"
#include "Entity/Entity.h"
#include "gfxShaderVSPS.h"
#include "gfxResource.h"
#include "camera.h"
#include "SkyBoxMesh.h"
#include "Context.h"
#include "gfxConstantBuffer.h"
#include "gfxRenderState.h"

namespace gfx
{

  struct sChangeEveryFrame
  {
    sDirectLight light;
    sPointLight pointLight;
    sMaterial material;
    DirectX::XMMATRIX viewPorject;
    DirectX::XMFLOAT3 eye;
    float repeat;
  };

  struct WORLD_DESC
  {
    bool bEnableSkyBox = TRUE;
    char* pSkyBoxTexturePath[6];
    char* pSkyBoxShaderPath[2];
    bool bCamera = TRUE;
    bool bLight = TRUE;
    bool bDirectLight = TRUE;
    bool bPointLight = FALSE;
    bool bSpotLight = FALSE;
  };

  class World
  {
    public:
      World(const WORLD_DESC& desc);
      ~World() = default;
      World(const World& rhs) = delete;
      World& operator=(const World& rhs) = delete;
      World(World&& rhs) = delete;
      World& operator=(World&& rhs) = delete;

      void Create();

      void Add(std::shared_ptr<Entity>& entity);
      void Update();
    private:
      WORLD_DESC m_desc;
      std::vector<std::shared_ptr<Entity>> m_entities;
      Camera m_camera;

      std::unique_ptr<SkyBoxMesh<VertexPosColorNormalUv>> m_pSkybox;
      std::unique_ptr<gfxConstantBuffer<sDirectLight>> m_pDirectLightConstant;
      std::unique_ptr<gfxConstantBuffer<sVertexConstant>> m_pVertexConstant;
      std::unique_ptr<gfxConstantBuffer<sChangeEveryFrame>> m_pPixelConstant;
  
      sChangeEveryFrame m_everyFrame;
      std::unique_ptr<gfxRenderStateCache> m_renderState;
    };
} // namespace gfx

