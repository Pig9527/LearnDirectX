#pragma once
#include "pheader.h"
#include "gfxConstantBuffer.h"
namespace gfx
{

  enum class BufferGroup : int
  {
    PerFrame = 0,
    PerObject,
    PerMaterial,
    PerPass,
    Custom
  };
#pragma pack(push, 16)
  struct PerFrameData
  {
    DirectX::XMMATRIX mvp;
  };

  struct MaterialData
  {
    DirectX::XMFLOAT4 color;
  };
#pragma pack(pop)

  class gfxConstacntBufferManager
  {
    
    public:
      gfxConstacntBufferManager();
      ~gfxConstacntBufferManager();
      gfxConstacntBufferManager(const gfxConstacntBufferManager& rhs) = delete;
      gfxConstacntBufferManager& operator=(const gfxConstacntBufferManager& rhs) = delete;

      void Bind();

      void UploadPerFrameToVS(const PerFrameData& data);
      void UploadMaterialToPS(const MaterialData& data);
    private:
      gfxConstantBuffer<PerFrameData> m_perFrameBuffer;
      gfxConstantBuffer<MaterialData> m_materialBuffer;
  };
} // namespace gfx
