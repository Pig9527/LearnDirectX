#include "Renderer.h"
#include "Graphic/gfxContext.h"

gfx::sVertexConstant gfx::Renderer::VertexConstantBuffer;
gfx::gfxConstantBuffer<gfx::sVertexConstant> gfx::Renderer::VertexShaderConstantTransformObj;
void gfx::Renderer::Init()
{
  gfxContext::Get().Initialize();

  VertexShaderConstantTransformObj.Create();
  gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(0,1,VertexShaderConstantTransformObj.GetBuffer().GetAddressOf());
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

void gfx::Renderer::Draw(uint32_t cnt)
{
  gfxContext::Get().m_pDeviceContext->Draw(cnt, 0);
}

void gfx::Renderer::Present()
{
  gfxContext::Get().m_pSwapChain->Present(0,0);
}

void gfx::Renderer::UploadMvp()
{
  VertexShaderConstantTransformObj.Upload(VertexConstantBuffer);
}
