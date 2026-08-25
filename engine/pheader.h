#define NOMINMAX
#include <Windows.h>
#include <windowsx.h>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>

#include <d2d1.h>
#include <dwrite.h>

#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

#include <vector>
#include <set>
#include <array>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <cmath>

#include <chrono>
#include <mutex>
#include <iomanip>

#define HR(x) {HRESULT hr = (x);if(FAILED(hr)){ DebugBreak();}}


namespace gfx
{
  template<typename T>
  using comptr = Microsoft::WRL::ComPtr<T>;
}

