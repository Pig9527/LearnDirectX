#include "gfxVetexShader.h"
#include "gfxContext.h"
void gfx::gfxVertexShader::Compile(const std::string &source, ShaderCompileOptions &options)
{
  options.EntryPoint = "vsMain";
  options.TargetProfile = "vs_5_0";
  std::string error;
  if (!CompileShaderFromSource(source, options, m_pByteBlod, error))
  {
    return;
  }

  if (m_pByteBlod == nullptr)
  {
    return;
  }
  gfxContext::Get().m_pDevice->CreateVertexShader(m_pByteBlod->GetBufferPointer(), m_pByteBlod->GetBufferSize(), nullptr, m_pShader.GetAddressOf());
}

void gfx::gfxVertexShader::CompileFromFile(const std::string &fileName, ShaderCompileOptions &options)
{
  options.EntryPoint = "vsMain";
  options.TargetProfile = "vs_5_0";
  std::string error;
  if (!CompileShaderFromFile(fileName, options, m_pByteBlod, error))
  {
    return;
  }

  if (m_pByteBlod == nullptr)
  {
    return;
  }
  gfxContext::Get().m_pDevice->CreateVertexShader(m_pByteBlod->GetBufferPointer(), m_pByteBlod->GetBufferSize(), nullptr, m_pShader.GetAddressOf());
}

void gfx::gfxVertexShader::Bind()
{
  gfxContext &context = gfxContext::Get();
  context.m_pDeviceContext->VSSetShader(m_pShader.Get(), nullptr, 0);
}

void gfx::gfxVertexShader::UnBind()
{
  gfxContext &context = gfxContext::Get();
  context.m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);
}
