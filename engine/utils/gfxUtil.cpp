#include "gfxUtil.h"

std::wstring utf82WString(std::string_view str)
{
  if (str.empty())
    return std::wstring();

  int cbMultiByte = static_cast<int>(str.size());
  int req = MultiByteToWideChar(65001, 0, str.data(), cbMultiByte, nullptr, 0);
  std::wstring res(req, 0);
  MultiByteToWideChar(65001, 0, str.data(), cbMultiByte, &res[0], req);
  return res;
}

std::string WString2utf8(std::wstring_view wstr)
{
  if (wstr.empty())
    return std::string();

  int cbMultiByte = static_cast<int>(wstr.size());
  int req = WideCharToMultiByte(65001, 0, wstr.data(), cbMultiByte, nullptr, 0, nullptr, nullptr);
  std::string res(req, 0);
  WideCharToMultiByte(65001, 0, wstr.data(), cbMultiByte, &res[0], req, nullptr, nullptr);
  return res;
}

XID String2ID(std::string_view str)
{
  static std::hash<std::string_view> hash;
  return hash(str);
}
