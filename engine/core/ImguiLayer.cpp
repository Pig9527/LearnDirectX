#include "ImguiLayer.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/backends/imgui_impl_win32.h"
#include "Context.h"
#include "gfxContext.h"

void gfx::ImguiLayer::Attach()
{
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;

  ImGui::StyleColorsDark();

  gfxContext &context = gfxContext::Get();
  ImGui_ImplDX11_Init(context.m_pDevice.Get(), context.m_pDeviceContext.Get());
  ImGui_ImplWin32_Init(Context::sHwnd);
}

void gfx::ImguiLayer::Detach()
{
}

void gfx::ImguiLayer::Render()
{
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();
  static bool bAnimate = true;
  if (bAnimate)
  {
    phi += 0.003f * 0.16f;
    theta += 0.037f * 0.16f;
    phi = DirectX::XMScalarModAngle(phi);
    theta = DirectX::XMScalarModAngle(theta);
  }

  ImGui::Begin("setting");

  ImGui::Checkbox("animate", &bAnimate);
  ImGui::SameLine(0.0f, 25.0f);
  ImGui::SliderFloat("Scale", &scale, 0.2f, 2.0f);

  ImGui::Text("Phi: %.2f degrees", DirectX::XMConvertToDegrees(phi)); // 显示文字，用于描述下面的控件
  ImGui::SliderFloat("##1", &phi, -DirectX::XM_PI, DirectX::XM_PI, "");

  ImGui::Text("Theta: %.2f degrees", DirectX::XMConvertToDegrees(theta));
  ImGui::SliderFloat("##2", &theta, -DirectX::XM_PI, DirectX::XM_PI, "");

  ImGui::Text("Position: (%.1f, %.1f, 0.0)", tx, ty);

  ImGui::Text("FOV: %.2f degrees", DirectX::XMConvertToDegrees(fov));
  ImGui::SliderFloat("##3", &fov, DirectX::XM_PIDIV4, DirectX::XM_PI / 3 * 2, "");

  ImGui::Text("Material");
  ImGui::SliderFloat3("ambient",&ambient.x,0.0,1.0);
  ImGui::SliderFloat3("diffuse",&diffuse.x, 0.0, 1.0);
  ImGui::SliderFloat3("specular",&specular.x, 0.0, 1.0);
  ImGui::SliderFloat("speuclarPower",&specularPower,0.001f,10.0f,"");
  
  ImGui::Text("light");
  ImGui::DragFloat3("Dir",&lightDir.x);
  ImGui::ColorEdit3("color",&lightColor.x);
  ImGui::SliderFloat3("eyePos",&eyePos.x,-10.0,10.0);
  ImGui::End();

  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
