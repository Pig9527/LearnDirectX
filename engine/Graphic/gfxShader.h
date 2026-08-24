#pragma once
#include "pheader.h"

namespace gfx
{
  struct ShaderCompileOptions
  {
    std::string EntryPoint;
    std::string TargetProfile;
    uint32_t Flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    bool EnableDebug = true;
  };


  static bool CompileShaderFromSource(const std::string& source,const ShaderCompileOptions& options,comptr<ID3DBlob>& blod,std::string& error)
  {
    uint32_t flags = options.Flags;

    std::string profile = options.TargetProfile;

    std::vector<D3D_SHADER_MACRO> macro;
    // for(const auto& define: options.Defines)
    // {
    //   D3D_SHADER_MACRO macro = {define};
    // }

    comptr<ID3DBlob> err;
    HRESULT hr = D3DCompile(
      source.c_str(),
      source.length(),
      nullptr,
      macro.data(),
      D3D_COMPILE_STANDARD_FILE_INCLUDE,
      options.EntryPoint.c_str(),
      profile.c_str(),
      flags,
      0,
      blod.GetAddressOf(),
      err.GetAddressOf()
    );

    if(FAILED(hr))
    {
      OutputDebugStringA((LPCSTR)err->GetBufferPointer());
      return false;
    }
    return true;
  }

  static bool CompileShaderFromFile(const std::string& fileName,const ShaderCompileOptions& options,comptr<ID3DBlob>& blod,std::string& error)
  {
    std::ifstream file(fileName);
    if(!file.is_open())
    {
      return false;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return CompileShaderFromSource(buffer.str(),options,blod,error);
  }
  class gfxShader
  {
    public:
      gfxShader() = default;
      virtual ~gfxShader() = default;

      virtual void Compile(const std::string& source) = 0;
      virtual void CompileFromFile(const std::string& fileName) = 0;
      virtual void Bind() = 0;
      virtual void UnBind() = 0;

      comptr<ID3DBlob>& GetBlod() {return m_pByteBlod;}
    protected:
      comptr<ID3DBlob> m_pByteBlod;
      std::string m_Name;
  };
} // namespace gfx
