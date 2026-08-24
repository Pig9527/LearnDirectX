#include "gfxShaderVertex.h"
#include "gfxContext.h"
void gfx::gfxShaderVertex::Compile(const std::string &source)
{
  ShaderCompileOptions option;
  option.EntryPoint = "vsMain";
  option.TargetProfile = "vs_5_0";
  std::string error;
  if (!CompileShaderFromSource(source, option, m_pByteBlod, error))
  {
    return;
  }

  if (m_pByteBlod == nullptr)
  {
    return;
  }
  gfxContext::Get().m_pDevice->CreateVertexShader(m_pByteBlod->GetBufferPointer(), m_pByteBlod->GetBufferSize(), nullptr, m_pShader.GetAddressOf());
}

void gfx::gfxShaderVertex::CompileFromFile(const std::string &fileName)
{
  ShaderCompileOptions option;
  option.EntryPoint = "vsMain";
  option.TargetProfile = "vs_5_0";
  std::string error;
  if (!CompileShaderFromFile(fileName, option, m_pByteBlod, error))
  {
    return;
  }

  if (m_pByteBlod == nullptr)
  {
    return;
  }
  gfxContext::Get().m_pDevice->CreateVertexShader(m_pByteBlod->GetBufferPointer(), m_pByteBlod->GetBufferSize(), nullptr, m_pShader.GetAddressOf());
}

void gfx::gfxShaderVertex::Bind()
{
  gfxContext &context = gfxContext::Get();
  context.m_pDeviceContext->VSSetShader(m_pShader.Get(), nullptr, 0);
}

void gfx::gfxShaderVertex::UnBind()
{
  gfxContext &context = gfxContext::Get();
  context.m_pDeviceContext->VSSetShader(nullptr, nullptr, 0);
}
