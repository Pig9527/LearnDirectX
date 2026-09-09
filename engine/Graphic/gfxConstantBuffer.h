#pragma once
#include "pheader.h"
#include "Core/Camera.h"

namespace gfx
{
  template<size_t s> struct ValidateConstantBufferSize
  {
    static_assert(s%16 == 0,"constant buffer size must be a mulitple of 16 byte");
  };
  

  enum class CONST_BUFFER_TYPE
  {
    VS,
    PS,
  };

  struct CONST_BUFFER_DESC_STRUCT
  {
    CONST_BUFFER_TYPE type;
    int slot = 0; 
  };

  template<typename T>
  class gfxConstantBuffer
  {
    public:

      gfxConstantBuffer(int slot = 1);
      gfxConstantBuffer(const CONST_BUFFER_DESC_STRUCT& desc);



      ~gfxConstantBuffer();
      gfxConstantBuffer(const gfxConstantBuffer& rhs) = delete;
      gfxConstantBuffer& operator=(const gfxConstantBuffer& rhs) = delete;
      
      void Create();
      void SetSlot(int slot) { m_Desc.slot = slot; }
      void Upload(const T& data);

      comptr<ID3D11Buffer>& GetBuffer(){return m_pBuffer;}

    private:
      CONST_BUFFER_DESC_STRUCT m_Desc;
      int m_Slot;

      comptr<ID3D11Buffer> m_pBuffer;
  };
} // namespace gfx
#include "gfxConstantBuffer.inl"
