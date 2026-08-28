#include "Context.h"

namespace gfx
{
  HWND Context::sHwnd = 0;
  int Context::sWindowWidth = 0;
  int Context::sWindowHeight = 0;
  bool Context::sbRunning = true;

  sMaterial  Context::arrMaterial[32];
  sDirectLight  Context::arrDirectLight[32];
  sSpotLight  Context::arrSpotLight[32];
  sPointLight  Context::arrPointLight[32];
} // namespace gfx
