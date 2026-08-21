#include "Renderer.h"
#include "gfxContext.h"
void gfx::Renderer::Init()
{
  gfxContext::Get().Initialize();
}
void gfx::Renderer::Clear()
{
  gfxContext& context = gfxContext::Get();
  DirectX::XMFLOAT4 back{0.1f,0.1f,0.1f,1.0f};
  context.m_pDeviceContext->ClearRenderTargetView(
    context.m_pRenderView.Get(),
    &back.x
  );

  context.m_pDeviceContext->ClearDepthStencilView(
    context.m_pDepthStencilView.Get(),
    D3D11_CLEAR_DEPTH|D3D10_CLEAR_STENCIL,
    1.0f,0
  );
}

void gfx::Renderer::DrawIndex(uint32_t cnt)
{
  gfxContext::Get().m_pDeviceContext->DrawIndexed(cnt,0,0);
}

void gfx::Renderer::Present()
{
  gfxContext::Get().m_pSwapChain->Present(0,0);
}
