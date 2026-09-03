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
    explicit MaterialTextureComponent(const std::string& filePath);
    explicit MaterialTextureComponent( const std::wstring& wfilePath);

    void Update();
    void OnAttach() override;

    eTextureType Type = eTextureType::DDS;
    eTextureMaterialType MaterialType;
    int Slot = 1;
    std::string FilePath;
    std::wstring wFilePath;
    std::shared_ptr<gfxTexture> m_pTexture;
  };

}
