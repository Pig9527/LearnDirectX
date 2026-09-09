#pragma once
#include "pheader.h"
#include "gfxTexture.h"
#include "Component.h"
#include "gfxTexture.h"

namespace gfx
{
  class MaterialTextureComponent
    :public Component
  {
    
    public:

    enum class eTextureMaterialType
    {
      Material,Normal,Diffuse,Specular
    };

    MaterialTextureComponent();
    explicit MaterialTextureComponent(const std::string& filePath,float repeat = 1.0f, int slot = 1 ,eTextureMaterialType type = eTextureMaterialType::Material);
    explicit MaterialTextureComponent(const std::wstring& wfilePath, float repeat = 1.0f, int slot = 1, eTextureMaterialType type = eTextureMaterialType::Material);

    void Update();
    void OnAttach() override;

    eTextureType Type = eTextureType::DDS;
    eTextureMaterialType MaterialType;
    float TextureRepeat = 1.0f;
    int Slot = 1;
    std::string FilePath;
    std::wstring wFilePath;
    std::shared_ptr<gfxTexture> m_pTexture;
  };

}
