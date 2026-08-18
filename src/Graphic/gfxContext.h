#pragma once
#include "pheader.h"

namespace gfx
{

  class gfxContext
  {
    public:
      static gfxContext& Get()
      {
        static gfxContext gfxcontext;
        return gfxcontext;
      }

      void Initialize();
      comptr<ID3D11Device> m_pDevice;
      comptr<ID3D11DeviceContext> m_pDeviceContext;
      comptr<IDXGIFactory> m_pFactory;
      comptr<IDXGISwapChain> m_pSwapChain;
      comptr<ID3D11RenderTargetView> m_pRenderView;
      comptr<ID3D11Texture2D> m_pBackbuffer;
      comptr<ID3D11Texture2D> m_pDepthStencilBuffer;
      comptr<ID3D11DepthStencilView> m_pDepthStencilView;

    protected:
      gfxContext();
      ~gfxContext();
  };
}
