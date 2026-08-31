#pragma once
#include "core/Context.h"
#include "gfxConstantBuffer.h"


namespace gfx
{
  class gfxConstBufferMag
  {
    public:
    gfxConstBufferMag() = default;
    ~gfxConstBufferMag() = default;

    gfxConstBufferMag(const gfxConstBufferMag& rhs) = delete;
    gfxConstBufferMag& operator=(const gfxConstBufferMag& rhs)= delete;

    void Init();
    void Upload2VS();
    void Upload2PS();
    void UploadTex();

    void SetConstMVP(Camera* camera);
    private:
    gfxConstantBuffer<sVertexConstant> m_MvpConstant;
    gfxConstantBuffer<sPsLightMaterial> m_DirectLightConstant;
    gfxConstantBuffer<sTexTell> m_TexRepeatConstant;
  };
}
