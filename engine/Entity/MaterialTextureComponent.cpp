#include "MaterialTextureComponent.h"

namespace gfx
{
    MaterialTextureComponent::MaterialTextureComponent()
      :MaterialType(eTextureMaterialType::Material)
      ,Type(eTextureType::DDS)
      ,Slot(1)
    {
    }

    MaterialTextureComponent::MaterialTextureComponent(const std::wstring &wfilePath)
      :MaterialType(eTextureMaterialType::Material)
      ,Type(eTextureType::DDS)
      ,wFilePath(wfilePath)
    {
    }

    MaterialTextureComponent::MaterialTextureComponent(const std::string &filePath)
      :MaterialType(eTextureMaterialType::Material)
      ,Type(eTextureType::other)
      ,FilePath(filePath)
    {
    }

    void MaterialTextureComponent::Update()
    {
      m_pTexture->Bind();
    }

    void MaterialTextureComponent::OnAttach()
    {
      m_pTexture = std::make_shared<gfxTexture>(Slot);
      if(Type == eTextureType::DDS)
        m_pTexture->Create(wFilePath.c_str());
      else if(Type == eTextureType::other)
        m_pTexture->Create(FilePath.c_str());
    }
}
