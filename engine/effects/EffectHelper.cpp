#include "EffectHelper.h"
#include "gfxContext.h"
#include "../utils/gfxUtil.h"
namespace gfx
{

  enum eShaderFlag
  {
    PixelShader = 0x01,
    VertexShader = 0x02,
    GeometryShader = 0x04,
    HullShader = 0x08,
    DomainShader = 0x10,
    ComputeShader = 0x20
  };

  struct SHADER_STRUCT_RESOURCE_DESC
  {
    std::string name;
    D3D11_SRV_DIMENSION dim;
    comptr<ID3D11ShaderResourceView> pShaderResoureceView;
  };
  
  struct SHADER_STRUCT_SAMPLE_STATE_DESC
  {
    std::string name;
    comptr<ID3D11SamplerState> pSamplerState;
  };

  struct SHADER_STRUCT_READ_WRITE_RESOURCE_DESC
  {
    std::string name;
    D3D11_UAV_DIMENSION dim;
    comptr<ID3D11UnorderedAccessView> pUnorderAccessView;
    uint32_t initialCount;
    bool enableCounter;
    bool firstInit;
  };

  struct CBufferData
  {
    bool isDirty = false;
    comptr<ID3D11Buffer> pCbuffer;
    std::vector<uint8_t> cBufferDatas;
    std::string cBufferName;
    uint32_t startSlot = 0;

    CBufferData() = default;
    CBufferData(const std::string& name,uint32_t startslot,uint32_t byteWidth,byte* initData = nullptr)
    :cBufferDatas(byteWidth),cBufferName(name),startSlot(startslot)
    {
      if(initData) memcpy_s(cBufferDatas.data(),byteWidth,initData,byteWidth);
    }

    HRESULT CreateBuffer()
    {
      if(pCbuffer != nullptr)
        return E_INVALIDARG;
      D3D11_BUFFER_DESC desc;
      ZeroMemory(&desc,sizeof(desc));
      desc.Usage = D3D11_USAGE_DYNAMIC;
      desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
      desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
      desc.ByteWidth = (uint32_t)cBufferDatas.size();
      return gfxContext::Get().m_pDevice->CreateBuffer(&desc,nullptr,pCbuffer.GetAddressOf());
    }

    void UpdataBuffer()
    {
      if(isDirty)
      {
        gfxContext& context = gfxContext::Get();
        isDirty = false;
        D3D11_MAPPED_SUBRESOURCE mapped;
        context.m_pDeviceContext->Map(pCbuffer.Get(),0,D3D11_MAP_WRITE_DISCARD,0,&mapped);
        memcpy_s(mapped.pData,cBufferDatas.size(),cBufferDatas.data(),cBufferDatas.size());
        context.m_pDeviceContext->Unmap(pCbuffer.Get(),0);
      }
    }
    void BindVS()
    {
      gfxContext::Get().m_pDeviceContext->VSSetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }
    void BindPS()
    {
      gfxContext::Get().m_pDeviceContext->PSSetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }
    void BindHS()
    {
      gfx::gfxContext::Get().m_pDeviceContext->HSGetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }
    void BindCS()
    {
      gfxContext::Get().m_pDeviceContext->CSGetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }
    void BindDS()
    {
      gfxContext::Get().m_pDeviceContext->DSGetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }

    void BindGS()
    {
      gfxContext::Get().m_pDeviceContext->GSSetConstantBuffers(startSlot,1,pCbuffer.GetAddressOf());
    }


  };
  struct ConstantBufferVariable
    :public EffectConstantBufferVariable
  {
    std::string_view name;
    uint32_t startByteOffset = 0;
    uint32_t byteWidth = 0;
    std::shared_ptr<CBufferData> pCbufferData;
    //CBufferData* pCbufferData = nullptr;
    ConstantBufferVariable()= default;
    ~ConstantBufferVariable(){}

    ConstantBufferVariable(std::string_view name,uint32_t offset,uint32_t size,std::shared_ptr<CBufferData> bufferdata)
    :name(name)
    ,startByteOffset(offset)
    ,byteWidth(size)
    ,pCbufferData(bufferdata)
    {

    }

    void SetUint(uint32_t val) override
    {
      SetRaw(&val,0,4);
    }

    void SetSint(int val) override
    {
      SetRaw(&val,0,4);
    }
    void SetFloat(float val) override
    {
      SetRaw(&val,0,4);
    }

    void SetUintVector(uint32_t num,const uint32_t* data) override
    {
      if(num > 4)
      {
        num = 4;
      }
      uint32_t byteCount = num + sizeof(uint32_t);
      if(byteCount > byteWidth)
      {
        byteCount = byteWidth;
      }
      SetRaw(data,0,byteCount);
    }


    void SetRaw(const void* data,uint32_t byteOffset = 0,uint32_t byteCount = 0xffffffff)
    {
      if(!data || byteOffset > byteWidth)
      {
        return;
      }
      if (byteOffset + byteCount > byteWidth)
      {
          byteCount = byteWidth - byteOffset;
      }
      if(memcpy(pCbufferData->cBufferDatas.data() + startByteOffset + byteOffset,data,byteCount))
      {
        memcpy_s(pCbufferData->cBufferDatas.data()+startByteOffset+byteOffset,byteCount,data,byteCount);
        pCbufferData->isDirty = true;
      }
    }
  };

  struct SHADER_STRUCT_VERTEX_DESC
  {
    std::string name;
    comptr<ID3D11VertexShader> pVS;
    uint32_t cbUseMask = 0;
    uint32_t ssUseMask = 0;
    uint32_t unused = 0;
    uint32_t srUseMask[4] ={};
    std::unique_ptr<CBufferData> pParamDataBufferData = nullptr;
    std::unordered_map<size_t,std::shared_ptr<ConstantBufferVariable>> pParams;
  };

  struct SHADER_STRUCT_PIXEL_DESC
  {
    std::string name;
    comptr<ID3D11PixelShader> pPS;
    uint32_t cbUseMask = 0;
    uint32_t ssUseMask = 0;
    uint32_t unused = 0;
    uint32_t srUseMask[4] ={};
    std::unique_ptr<CBufferData> pParamDataBufferData = nullptr;
    std::unordered_map<size_t,std::shared_ptr<ConstantBufferVariable>> pParams;
  };

  struct EffectPassImpl
  :public EffectPass
  {
    EffectPassImpl(
      EffectHelper* phelper,
      std::string_view name,
      std::unordered_map<uint32_t,CBufferData>& pCbuffer,
      std::unordered_map<uint32_t,SHADER_STRUCT_RESOURCE_DESC>& ShaderResouce,
      std::unordered_map<uint32_t,SHADER_STRUCT_SAMPLE_STATE_DESC>& sampler ,
      std::unordered_map<uint32_t,SHADER_STRUCT_READ_WRITE_RESOURCE_DESC>& unorderView
    )
    :pEffectHelper(phelper)
    ,passName(name)
    ,cBuffers(pCbuffer)
    ,shaderResources(ShaderResouce)
    ,samplers(sampler)
    ,undoredAccessViews(unorderView)
    {}

    EffectHelper* pEffectHelper = nullptr;
    std::string passName;
    std::unordered_map<uint32_t, CBufferData>& cBuffers;
    std::unordered_map<uint32_t, SHADER_STRUCT_RESOURCE_DESC>& shaderResources;
    std::unordered_map<uint32_t, SHADER_STRUCT_SAMPLE_STATE_DESC>& samplers;
    std::unordered_map<uint32_t, SHADER_STRUCT_READ_WRITE_RESOURCE_DESC>& undoredAccessViews;
    
    std::unique_ptr<CBufferData> pVSParamData = nullptr;
    std::unique_ptr<CBufferData> pPSParamData = nullptr;

    virtual void SetRasterizerState(ID3D11RasterizerState* pRs) override
    {

    }
    virtual void SetBlendState(ID3D11BlendState* pBs, const float blendFactor[4], uint32_t mask) override
    {

    }
  };

  class EffectHelper::Impl
  {
    public:
    Impl();
    ~Impl() = default;

    HRESULT CreateShaderFromBlob(std::string_view name,uint32_t flags,ID3DBlob* blob);
    HRESULT UpdateShaderReflection(std::string_view name,ID3D11ShaderReflection* shaderReflection,uint32_t flags);
    void Clear();
    std::unordered_map<size_t,std::shared_ptr<EffectPassImpl>> m_effectPasses;
    std::unordered_map<uint32_t,std::shared_ptr<ConstantBufferVariable>> m_constantBufferVariables;
    std::unordered_map<uint32_t, CBufferData> m_pCbufferData;
    std::unordered_map<uint32_t, SHADER_STRUCT_RESOURCE_DESC> m_shaderResources;
    std::unordered_map<uint32_t,SHADER_STRUCT_SAMPLE_STATE_DESC> m_samplers;
    std::unordered_map<uint32_t,SHADER_STRUCT_READ_WRITE_RESOURCE_DESC> m_unorderAccessResource;

    std::unordered_map<size_t,std::shared_ptr<SHADER_STRUCT_VERTEX_DESC>> m_VertexShaders;
    std::unordered_map<size_t,std::shared_ptr<SHADER_STRUCT_PIXEL_DESC>> m_PixelShaders;
  };
  HRESULT EffectHelper::Impl::CreateShaderFromBlob(std::string_view name, uint32_t flags, ID3DBlob *blob)
  {
      HRESULT hr = S_OK;
      comptr<ID3D11VertexShader> pVs;
      comptr<ID3D11PixelShader> pPs;

      size_t nameID = String2ID(name);
      gfxContext& context = gfxContext::Get();
      switch (flags)
      {
        case VertexShader:
        {
          m_VertexShaders[nameID]->name = name;
          hr = context.m_pDevice->CreateVertexShader(blob->GetBufferPointer(),blob->GetBufferSize(),
            nullptr,m_VertexShaders[nameID]->pVS.GetAddressOf());
        }break;
        case PixelShader:
        {
          m_PixelShaders[nameID]->name = name;
          hr =context.m_pDevice->CreatePixelShader(blob->GetBufferPointer(),blob->GetBufferSize(),
            nullptr,m_PixelShaders[nameID]->pPS.GetAddressOf());
        }break;
      }
      return hr;
  }
  HRESULT EffectHelper::Impl::UpdateShaderReflection(std::string_view name, ID3D11ShaderReflection *shaderReflection, uint32_t flags)
  {
    HRESULT hr = S_OK;
    D3D11_SHADER_DESC desc;
    hr = shaderReflection->GetDesc(&desc);
    if(FAILED(hr)) return hr;
    size_t nameID = String2ID(name);

    for(uint32_t i =0;;i++)
    {
      D3D11_SHADER_INPUT_BIND_DESC sibdedc;
      hr = shaderReflection->GetResourceBindingDesc(i,&sibdedc);
      if(FAILED(hr)) break;
      if(sibdedc.Type == D3D_SIT_CBUFFER)
      {
        ID3D11ShaderReflectionConstantBuffer* pcbuffer = shaderReflection->GetConstantBufferByName(sibdedc.Name);
        D3D11_SHADER_BUFFER_DESC cbdesc;
        ZeroMemory(&cbdesc,sizeof(cbdesc));
        hr = pcbuffer->GetDesc(&cbdesc);
        if(FAILED(hr)) return hr;
        bool isParam = !strcmp(sibdedc.Name,"$Params");
        if(!isParam)
        {
          auto it = m_pCbufferData.find(sibdedc.BindPoint);
          if(it == m_pCbufferData.end())
          {
            m_pCbufferData.emplace(std::make_pair(sibdedc.BindPoint,CBufferData(sibdedc.Name,sibdedc.BindPoint,cbdesc.Size,nullptr)));
            m_pCbufferData[sibdedc.BindPoint].CreateBuffer();
          }
          else if(it->second.cBufferDatas.size() < cbdesc.Size)
          {
            m_pCbufferData[sibdedc.BindPoint] = CBufferData(sibdedc.Name,sibdedc.BindPoint,cbdesc.Size,nullptr);
            m_pCbufferData[sibdedc.BindPoint].CreateBuffer();
          }

          if(cbdesc.Variables > 0)
          {
            switch (flags)
            {
              case VertexShader:
              {
                m_VertexShaders[nameID]->cbUseMask |= (1<<sibdedc.BindPoint);
              }break;
              case PixelShader:
              {
                m_PixelShaders[nameID]->cbUseMask |= (1<<sibdedc.BindPoint);
              }break;
            }
          }
        }
        else if(cbdesc.Variables > 0)
        {
          switch (flags)
          {
          case VertexShader:
            m_VertexShaders[nameID]->pParamDataBufferData = std::make_unique<CBufferData>(sibdedc.Name,sibdedc.BindPoint,cbdesc.Size,nullptr);
            break;
          case PixelShader:
            m_PixelShaders[nameID]->pParamDataBufferData = std::make_unique<CBufferData>(sibdedc.Name,sibdedc.BindPoint,cbdesc.Size,nullptr);
            break;
          }
        }

        for (size_t j = 0; j < cbdesc.Variables; j++)
        {
          ID3D11ShaderReflectionVariable* pvar = pcbuffer->GetVariableByIndex(j);
          D3D11_SHADER_VARIABLE_DESC svdesc;
          hr = pvar->GetDesc(&svdesc);
          if(FAILED(hr)) return hr;

          size_t svNameID = String2ID(svdesc.Name);

          if(isParam)
          {
            switch (flags)
            {
            case VertexShader:
              m_VertexShaders[svNameID]->pParams[svNameID]=
                std::make_shared<ConstantBufferVariable>(svdesc.Name,svdesc.StartOffset,svdesc.Size,m_VertexShaders[svNameID]->pParamDataBufferData.get());
                break;
            case PixelShader:
              m_PixelShaders[svNameID]->pParams[svNameID]=
                std::make_shared<ConstantBufferVariable>(svdesc.Name,svdesc.StartOffset,svdesc.Size,m_VertexShaders[svNameID]->pParamDataBufferData.get());
                break;
            }
          }else
          {
            m_constantBufferVariables[svNameID] = std::make_shared<ConstantBufferVariable>(
              svdesc.Name,svdesc.StartOffset,svdesc.Size,&m_pCbufferData[sibdedc.BindPoint]
            );
            if(svdesc.DefaultValue)
              m_constantBufferVariables[svNameID]->SetRaw(svdesc.DefaultValue);
          }
        }
      }
      else if(sibdedc.Type == D3D_SIT_TEXTURE || sibdedc.Type == D3D_SIT_STRUCTURED|| 
        sibdedc.Type == D3D_SIT_BYTEADDRESS || sibdedc.Type == D3D_SIT_TBUFFER)
      {
        auto it = m_shaderResources.find(sibdedc.BindPoint);
        if(it == m_shaderResources.end())
        {
          m_shaderResources.emplace(std::make_pair(sibdedc.BindPoint,
            SHADER_STRUCT_RESOURCE_DESC{sibdedc.Name,sibdedc.Dimension,nullptr}));
        }
        switch (flags)
        {
        case VertexShader:
          m_VertexShaders[nameID]->srUseMask[sibdedc.BindPoint/32] |=(1<<(sibdedc.BindPoint %32));break;
        case PixelShader:
          m_PixelShaders[nameID]->srUseMask[sibdedc.BindPoint/32] |= (1<<(sibdedc.BindPoint %32));break;
        }
      }
      else if(sibdedc.Type == D3D_SIT_SAMPLER)
      {
          auto it = m_samplers.find(sibdedc.BindPoint);
          if(it == m_samplers.end())
          {
            m_samplers.emplace(std::make_pair(sibdedc.BindPoint,
            SHADER_STRUCT_SAMPLE_STATE_DESC{sibdedc.Name,nullptr}));
          }
          switch (flags)
          {
          case VertexShader:
            m_VertexShaders[nameID]->ssUseMask |= (1<<sibdedc.BindPoint);break;
          case PixelShader:
            m_PixelShaders[nameID]->ssUseMask |= (1<<sibdedc.BindPoint);break;
          }
      }
      else if(sibdedc.Type == D3D_SIT_UAV_RWTYPED || 
        sibdedc.Type == D3D_SIT_UAV_RWTYPED ||
        sibdedc.Type == D3D_SIT_UAV_RWSTRUCTURED ||
        sibdedc.Type == D3D_SIT_UAV_RWSTRUCTURED_WITH_COUNTER||
        sibdedc.Type == D3D_SIT_UAV_APPEND_STRUCTURED ||
        sibdedc.Type == D3D_SIT_UAV_CONSUME_STRUCTURED ||
        sibdedc.Type == D3D_SIT_UAV_RWBYTEADDRESS)
      {
        
      }
    }
    return S_OK;
  }

  void EffectHelper::Impl::Clear()
  {
    m_effectPasses.clear();
    m_constantBufferVariables.clear();
    m_pCbufferData.clear();
    m_shaderResources.clear();
    m_samplers.clear();
    m_VertexShaders.clear();
    m_PixelShaders.clear();
  }
  EffectHelper::EffectHelper()
    :m_pImpl(std::make_unique<EffectHelper::Impl>())
  {
  }
  EffectHelper::~EffectHelper()
  {
  }
  HRESULT EffectHelper::AddShader(std::string_view name, ID3DBlob *blob)
  {
    if(name.empty() || blob == nullptr)
      return E_INVALIDARG;
    HRESULT hr = S_OK;
    comptr<ID3D11ShaderReflection> pShaderReflection;
    hr = D3DReflect(blob->GetBufferPointer(),blob->GetBufferSize(),__uuidof(ID3D11ShaderReflection),
      reinterpret_cast<void**>(pShaderReflection.GetAddressOf()));
    if(FAILED(hr)) return hr;

    D3D11_SHADER_DESC sd;
    pShaderReflection->GetDesc(&sd);
    uint32_t flags = static_cast<eShaderFlag>(1<<D3D11_SHVER_GET_TYPE(sd.Version));
    hr = m_pImpl->CreateShaderFromBlob(name,flags,blob);
    if(FAILED(hr)) return hr;

    return m_pImpl->UpdateShaderReflection(name,pShaderReflection.Get(),flags);
  }
  HRESULT EffectHelper::AddEffectPass(std::string_view name, const EffectPassDesc *pPassDesc)
  {
    if(name.empty()) return E_INVALIDARG;
    size_t effectPassID = String2ID(name);
    auto it = m_pImpl->m_effectPasses.find(effectPassID);
    if(it != m_pImpl->m_effectPasses.end())
      return ERROR_OBJECT_ALREADY_EXISTS;

    auto& pEffectPass = m_pImpl->m_effectPasses[effectPassID]=
      std::make_shared<EffectPassImpl>(this,
        name,
        m_pImpl->m_pCbufferData,
        m_pImpl->m_shaderResources,
        m_pImpl->m_samplers,
        m_pImpl->m_unorderAccessResource);
    
    if(pPassDesc->nameVS.empty()) return E_INVALIDARG;
    if(!pPassDesc->nameVS.empty())
    {
      auto it = m_pImpl->m_VertexShaders.find(String2ID(pPassDesc->nameVS));
      if(it != m_pImpl->m_VertexShaders.end())
      {
        auto& pcbuff = it->second->pParamDataBufferData;
        if(pcbuff)
        {
          pEffectPass->pVSParamData = std::make_unique<CBufferData>(pcbuff->cBufferName.c_str(),
            pcbuff->startSlot,(uint32_t)pcbuff->cBufferDatas.size());
          it->second->pParamDataBufferData->CreateBuffer();
        }
      }
    }
  }
}
