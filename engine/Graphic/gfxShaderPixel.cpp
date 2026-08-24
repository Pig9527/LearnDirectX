#include "gfxShaderPixel.h"
#include "gfxContext.h"
namespace gfx
{
  void gfxShaderPixel::Compile(const std::string &source)
  {
    ShaderCompileOptions option;
    option.EntryPoint = "psMain";
    option.TargetProfile = "ps_5_0";
    std::string error;
    if (!CompileShaderFromSource(source, option, m_pByteBlod, error))
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

  void gfxShaderPixel::CompileFromFile(const std::string &fileName)
  {
    ShaderCompileOptions option;
    option.EntryPoint = "psMain";
    option.TargetProfile = "ps_5_0";
    std::string error;
    if (!CompileShaderFromFile(fileName, option, m_pByteBlod, error))
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

  void gfxShaderPixel::Bind()
  {
    gfxContext::Get().m_pDeviceContext->PSSetShader(m_pShader.Get(), nullptr, 0);
  }

  void gfxShaderPixel::UnBind()
  {
    gfxContext::Get().m_pDeviceContext->PSSetShader(nullptr, nullptr, 0);
  }

} // namespace  gfx
