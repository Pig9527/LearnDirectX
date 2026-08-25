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
      
      comptr<ID2D1Factory> m_pD2dFactory;
      comptr<ID2D1RenderTarget> m_pD2dRenderTarget;
      comptr<IDWriteFactory> m_pDwriteFactory;
      comptr<IDWriteTextFormat> m_pDwriteFormat;
      comptr<ID2D1SolidColorBrush> m_pColorBrush;
    protected:
      gfxContext();
      ~gfxContext();
  };
}
