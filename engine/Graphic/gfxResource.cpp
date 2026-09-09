#include "gfxResource.h"

namespace gfx
{
  void  gfxResource::AddShader(const std::string &name, const sShader_desc& desc)
  {
    auto it = m_shaderMaps.find(name);
    if (it != m_shaderMaps.end())
    {
      return;
    }
    auto shader = std::make_shared<gfxShaderVSPS>(desc);
    shader->Ceate();
    m_shaderMaps.emplace(name,shader);
  }

  std::shared_ptr<gfxShaderVSPS> gfxResource::FindShader(const std::string &name)
  {
    auto it = m_shaderMaps.find(name);
    if (it != m_shaderMaps.end())
    {
      return it->second;
    }
    return nullptr;
  }
}
