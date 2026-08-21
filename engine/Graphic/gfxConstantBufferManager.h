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
    DirectX::XMMATRIX world;
    DirectX::XMMATRIX worldInvTranspone;
    DirectX::XMMATRIX view;
    DirectX::XMMATRIX project;
    DirectX::XMMATRIX viewProject;
    DirectX::XMMATRIX mvp;
  };

  struct MaterialData
  {
    DirectX::XMFLOAT4 ambient;
    DirectX::XMFLOAT4 diffuse;
    DirectX::XMFLOAT4 specular;
    float specularPower;
    float pad[3];
  };

  struct LightData
  {
    DirectX::XMFLOAT3 lightDir;
    DirectX::XMFLOAT3 lightColor;
    DirectX::XMFLOAT3 eyePos;
    float pad[3];
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
      void UploadLightToPS(const LightData& data);
    private:
      gfxConstantBuffer<PerFrameData> m_perFrameBuffer;
      gfxConstantBuffer<MaterialData> m_materialBuffer;
      gfxConstantBuffer<LightData> m_lightBuffer;
  };
} // namespace gfx
