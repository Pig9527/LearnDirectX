#include "gfxIndexBuffer.h"
#include "gfxContext.h"
void gfx::gfxIndexBuffer::Create(uint32_t cnt, void *data)
{
  gfxContext& context = gfxContext::Get();
  D3D11_BUFFER_DESC desc = {};
  desc.ByteWidth = cnt * sizeof(uint32_t);
  desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
  desc.Usage = D3D11_USAGE_IMMUTABLE;
  D3D11_SUBRESOURCE_DATA db = {};
  db.pSysMem = data;

  m_IndexCnt = cnt;
  HR(context.m_pDevice->CreateBuffer(&desc,&db,m_pBuffer.GetAddressOf()));

}

void gfx::gfxIndexBuffer::Bind()
{
  gfxContext::Get().m_pDeviceContext->IASetIndexBuffer(m_pBuffer.Get(),DXGI_FORMAT_R32_UINT,0);
}
