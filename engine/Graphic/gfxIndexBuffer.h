#pragma once
#include "pheader.h"
namespace gfx
{
  class gfxIndex
  {
    public:
      void Create(uint32_t cnt,void* data);

      void Bind();
      inline comptr<ID3D11Buffer>& GetBuffer(){return m_pBuffer;}
    private:
      comptr<ID3D11Buffer> m_pBuffer;
  };
} // namespace gfx
