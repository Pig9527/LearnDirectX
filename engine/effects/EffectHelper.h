#pragma once
#include "../pheader.h"
namespace gfx
{

  struct EffectPassDesc
  {
    std::string_view nameVS;
    std::string_view nameDS;
    std::string_view nameHS;
    std::string_view nameGS;
    std::string_view namePS;
    std::string_view nameCS;
  };

  struct EffectConstantBufferVariable
  {
    virtual void SetUint(uint32_t val) = 0;
    virtual void SetSint(int val) = 0;
  
    virtual void SetFloat(float val) =0;

    virtual void SetUintVector(uint32_t num,const uint32_t* data) = 0;
    virtual void SetSintVector(uint32_t num, const int* data) = 0;
    virtual void SetFloatVector(uint32_t num,const float* data) = 0;

    virtual void SetFloatMatrix(const DirectX::FXMMATRIX& matrix) = 0;
  };

  class EffectHelper;
  struct EffectPass
  {

    virtual void SetRasterizerState(ID3D11RasterizerState* pRs) = 0;
    virtual void SetBlendState(ID3D11BlendState* pBs,const float blendFactor[4],uint32_t mask) = 0;
  };

  class EffectHelper
  {
    public:
    EffectHelper();
    ~EffectHelper();

    EffectHelper(const EffectHelper& rhs) = delete;
    EffectHelper& operator=(const EffectHelper& rhs) = delete;

    EffectHelper(EffectHelper&& rhs) =delete;
    EffectHelper& operator=(EffectHelper&& rhs) = delete;

    HRESULT AddShader(std::string_view name,ID3DBlob* blob);

    HRESULT AddEffectPass(std::string_view name,const EffectPassDesc* pPassDesc);
    private:
    class Impl;
    std::unique_ptr<Impl> m_pImpl;
  };
}
