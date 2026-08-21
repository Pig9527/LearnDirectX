#include "gfxPixelShader.h"
#include "gfxContext.h"
namespace gfx
{
  void gfxPixelShader::Compile(const std::string &source, ShaderCompileOptions &options)
  {
    options.EntryPoint = "psMain";
    options.TargetProfile = "ps_5_0";
    std::string error;
    if (!CompileShaderFromSource(source, options, m_pByteBlod, error))
    {
      return;
    }

    if (m_pByteBlod == nullptr)
    {
      return;
    }

    gfxContext::Get().m_pDevice->CreatePixelShader(
        m_pByteBlod->GetBufferPointer(),
        m_pByteBlod->GetBufferSize(),
        nullptr,
        m_pShader.GetAddressOf());
  }

  void gfxPixelShader::CompileFromFile(const std::string &fileName, ShaderCompileOptions &options)
  {
    options.EntryPoint = "psMain";
    options.TargetProfile = "ps_5_0";
    std::string error;
    if (!CompileShaderFromFile(fileName, options, m_pByteBlod, error))
    {
      return;
    }
    if (m_pByteBlod == nullptr)
    {
      return;
    }
    gfxContext::Get().m_pDevice->CreatePixelShader(
        m_pByteBlod->GetBufferPointer(),
        m_pByteBlod->GetBufferSize(),
        nullptr,
        m_pShader.GetAddressOf());
  }

  void gfxPixelShader::Bind()
  {
    gfxContext::Get().m_pDeviceContext->PSSetShader(m_pShader.Get(), nullptr, 0);
  }

  void gfxPixelShader::UnBind()
  {
    gfxContext::Get().m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);
  }

} // namespace  gfx
