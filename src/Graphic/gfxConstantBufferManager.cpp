#include "gfxConstantBufferManager.h"
#include "gfxContext.h"
namespace gfx
{
    gfxConstacntBufferManager::gfxConstacntBufferManager()
    {
      m_perFrameBuffer.Create();
      m_materialBuffer.Create();
    }

    gfxConstacntBufferManager::~gfxConstacntBufferManager()
    {
    }

    void gfxConstacntBufferManager::Bind()
    {
      gfxContext& context = gfxContext::Get();
      context.m_pDeviceContext->VSSetConstantBuffers(0,1,m_perFrameBuffer.GetBuffer().GetAddressOf());
      context.m_pDeviceContext->PSSetConstantBuffers(1,1,m_materialBuffer.GetBuffer().GetAddressOf());
    }

    void gfxConstacntBufferManager::UploadPerFrameToVS(const PerFrameData& data)
    {
      m_perFrameBuffer.Upload(data);
    }

    void gfxConstacntBufferManager::UploadMaterialToPS(const MaterialData& data)
    {
      m_materialBuffer.Upload(data);
    }

} // namespace gfx
