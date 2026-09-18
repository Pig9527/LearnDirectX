#pragma once
#include "pheader.h"

// 以下不可删除
#pragma warning(push)
#pragma warning(disable: 28251)
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned int cp, unsigned long flags, const char* str, int cbmb, wchar_t* widestr, int cchwide);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned int cp, unsigned long flags, const wchar_t* widestr, int cchwide, char* str, int cbmb, const char* defchar, int* used_default);
#pragma warning(pop)

void GFXResultFailed(HRESULT hr,const char* dx,const char* file,uint32_t line);

std::wstring utf82WString(std::string_view str);

std::string WString2utf8(std::wstring_view wstr);

using XID = size_t;
XID String2ID(std::string_view str);

