#pragma once

#include "pheader.h"
#include "gfxShaderVSPS.h"

namespace gfx
{
  class gfxResource
  {
    protected:
      gfxResource() = default;
      ~gfxResource() = default;
      gfxResource(const gfxResource& rhs) = delete;
      gfxResource& operator=(const gfxResource& rhs) = delete;
      
      gfxResource(gfxResource&& rhs) = delete;
      gfxResource& operator=(gfxResource&& rhs) = delete;

    public:
      static gfxResource& Get() { static gfxResource resource;return resource;}
    
      void AddShader(const std::string& name,const sShader_desc& desc);

      std::shared_ptr<gfxShaderVSPS> FindShader(const std::string& name);
      private:
        std::unordered_map<std::string,std::shared_ptr<gfxShaderVSPS>> m_shaderMaps;
  };
}
