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


  
}

void gfx::ImguiLayer::Begin(char *title)
{
  ImGui_ImplDX11_NewFrame();
  ImGui_ImplWin32_NewFrame();

  ImGui::NewFrame();
  ImGui::Begin(title);

}

void gfx::ImguiLayer::End()
{
  
  ImGui::End();

  ImGui::Render();
  ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void gfx::ImguiLayer::RenderDefDirectLight()
{
  ImguiLayer::Begin("DirectLightSetting");

  ImGui::ColorEdit4("ambient",&Context::arrDirectLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrDirectLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrDirectLight[0].Specular.x);
  ImGui::ColorEdit4("direction",&Context::arrDirectLight[0].Direction.x);

  ImguiLayer::End();
}

void gfx::ImguiLayer::RenderDefPointLight()
{
  ImguiLayer::Begin("PointLightSetting");
  
  ImGui::ColorEdit4("ambient",&Context::arrPointLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrPointLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrPointLight[0].Specular.x);
  ImGui::ColorEdit3("position",&Context::arrPointLight[0].Position.x);
  ImGui::ColorEdit3("att",&Context::arrPointLight[0].Att.x);

  ImGui::SliderFloat("att",&Context::arrPointLight[0].Range,-100.0,100.0,"%0.2f");

  ImguiLayer::End();
}

void gfx::ImguiLayer::RenderDefSpotLight()
{
  ImguiLayer::Begin("SpotLightSetting");
  
  ImGui::ColorEdit4("ambient",&Context::arrSpotLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrSpotLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrSpotLight[0].Specular.x);

  ImGui::ColorEdit3("position",&Context::arrSpotLight[0].Position.x);
  ImGui::ColorEdit3("direction",&Context::arrSpotLight[0].Direction.x);
  ImGui::ColorEdit3("att",&Context::arrSpotLight[0].Att.x);

  ImGui::SliderFloat("att",&Context::arrSpotLight[0].Range,-100.0,100.0,"%0.2f");
  ImGui::SliderFloat("att",&Context::arrSpotLight[0].Spot,-100.0,100.0,"%0.2f");

  ImguiLayer::End();
}

void gfx::ImguiLayer::RenderDefMaterial()
{

  ImguiLayer::Begin("Material");
  
  ImGui::ColorEdit4("ambient",&Context::arrMaterial[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrMaterial[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrMaterial[0].Specular.x);
  ImGui::ColorEdit4("specular",&Context::arrMaterial[0].Reflect.x);

  ImGui::PushID(1);
  ImGui::Text("DirectLight");
  ImGui::ColorEdit4("ambient",&Context::arrDirectLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrDirectLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrDirectLight[0].Specular.x);
  ImGui::ColorEdit4("direction",&Context::arrDirectLight[0].Direction.x);
  ImGui::PopID();

  ImGui::PushID(2);
  ImGui::Text("PointLight");
  ImGui::ColorEdit4("ambient",&Context::arrPointLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrPointLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrPointLight[0].Specular.x);
  ImGui::ColorEdit3("position",&Context::arrPointLight[0].Position.x);
  ImGui::ColorEdit3("att",&Context::arrPointLight[0].Att.x);

  ImGui::SliderFloat("att",&Context::arrPointLight[0].Range,-100.0,100.0,"%0.2f");

  ImGui::PopID();

  ImGui::PushID(4);
  ImGui::Text("SpotLight");
  ImGui::ColorEdit4("ambient",&Context::arrSpotLight[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrSpotLight[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrSpotLight[0].Specular.x);

  ImGui::ColorEdit3("position",&Context::arrSpotLight[0].Position.x);
  ImGui::ColorEdit3("direction",&Context::arrSpotLight[0].Direction.x);
  ImGui::ColorEdit3("att",&Context::arrSpotLight[0].Att.x);

  ImGui::SliderFloat("att",&Context::arrSpotLight[0].Range,-100.0,100.0,"%0.2f");
  ImGui::SliderFloat("att",&Context::arrSpotLight[0].Spot,-100.0,100.0,"%0.2f");
  ImGui::PopID();

  ImguiLayer::End();

}

void gfx::ImguiLayer::RenderDefScene()
{
  ImguiLayer::Begin("setting");

  ImGui::PushID(0);
  ImGui::Text("Material");
  ImGui::ColorEdit4("ambient",&Context::arrMaterial[0].Ambient.x);
  ImGui::ColorEdit4("diffuse",&Context::arrMaterial[0].Diffuse.x);
  ImGui::ColorEdit4("specular",&Context::arrMaterial[0].Specular.x);
  ImGui::ColorEdit4("specular",&Context::arrMaterial[0].Reflect.x);
  ImGui::PopID();


  ImguiLayer::End();
}
