#pragma once
#include "pheader.h"
#include "Core/Camera.h"

namespace gfx
{
  template<size_t s> struct ValidateConstantBufferSize
  {
    static_assert(s%16 == 0,"constant buffer size must be a mulitple of 16 byte");
  };
  

  template<typename T>
  class gfxConstantBuffer
  {
    public:
      gfxConstantBuffer();
      ~gfxConstantBuffer();
      gfxConstantBuffer(const gfxConstantBuffer& rhs) = delete;
      gfxConstantBuffer& operator=(const gfxConstantBuffer& rhs) = delete;
      
      void Create();

      void Upload(const T& data);

      comptr<ID3D11Buffer>& GetBuffer(){return m_pBuffer;}

    private:
      comptr<ID3D11Buffer> m_pBuffer;
  };
} // namespace gfx
#include "gfxConstantBuffer.inl"
