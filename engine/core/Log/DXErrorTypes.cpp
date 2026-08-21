#include "DXErrorTypesh"

namespace gfx
{
  DXErrorInfo::DXErrorInfo(HRESULT hr_, const std::string &msg_, const std::string &file_, const std::string &func_, int line_)
      : hr(hr_), message(msg_), file(file_), function(func_), line(line_)
  {
  }

  DXErrorCategory DXErrorInfo::GetCategory(HRESULT hr)
  {
    if (hr >= DXGI_ERROR_DEVICE_HUNG && hr <= DXGI_ERROR_ACCESS_DENIED)
    {
      return DXErrorCategory::Device;
    }
    if (hr >= D3D11_ERROR_FILE_NOT_FOUND /*&& hr <= D3D11_ERROR_UNSUPPORTED_VIDEO_DEVICE*/)
    {
      return DXErrorCategory::Driver;
    }
    return DXErrorCategory::Unknown;
  }

  DXErrorSeverity DXErrorInfo::GetSeverity(HRESULT hr)
  {
    switch (hr)
    {
    case E_FAIL:
    case E_OUTOFMEMORY:
    case DXGI_ERROR_DEVICE_HUNG:
    case DXGI_ERROR_DEVICE_REMOVED:
    case DXGI_ERROR_DEVICE_RESET:
      return DXErrorSeverity::Fatal;
    case E_INVALIDARG:
    case E_NOINTERFACE:
    case E_POINTER:
      return DXErrorSeverity::Error;
    case S_FALSE:
      return DXErrorSeverity::Warning;
    default:
      return SUCCEEDED(hr) ? DXErrorSeverity::Info : DXErrorSeverity::Error;
    }
  }
 } // namespace gfx
