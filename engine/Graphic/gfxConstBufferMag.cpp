#include "gfxConstBufferMag.h"
#include "camera.h"
namespace gfx
{
    void gfxConstBufferMag::Init()
    {
      gfxContext& context = gfxContext::Get();
      m_MvpConstant.Create();
      context.m_pDeviceContext->VSSetConstantBuffers(0, 1, m_MvpConstant.GetBuffer().GetAddressOf());

      m_DirectLightConstant.Create();
      context.m_pDeviceContext->PSSetConstantBuffers(1, 1, m_DirectLightConstant.GetBuffer().GetAddressOf());
      m_TexRepeatConstant.Create();
      context.m_pDeviceContext->PSSetConstantBuffers(2, 1, m_TexRepeatConstant.GetBuffer().GetAddressOf());
    }

    void gfxConstBufferMag::Upload2VS()
    {
      m_MvpConstant.Upload(Context::sVertexConstantMVP);
  
    }

    void gfxConstBufferMag::Upload2PS()
    {
      Context::sDirectLightConst.material = Context::arrMaterial[0];
      Context::sDirectLightConst.directLight = Context::arrDirectLight[0];
      Context::sDirectLightConst.eye = Context::CameraPos;
      m_DirectLightConstant.Upload(Context::sDirectLightConst);

    }

    void gfxConstBufferMag::UploadTex()
    {
      m_TexRepeatConstant.Upload(Context::sTextureTell);
    }

    void gfxConstBufferMag::SetConstMVP(Camera *camera)
    {

      Context::sVertexConstantMVP.World = DirectX::XMMatrixIdentity();
      Context::sVertexConstantMVP.View = camera->GetViewMatrix();
      Context::sVertexConstantMVP.Project = camera->GetProjectMatrix();
      Context::sVertexConstantMVP.WorldInvTranspose = DirectX::XMMatrixTranspose(
        DirectX::XMMatrixInverse(nullptr, Context::sVertexConstantMVP.World)
      );

      Context::sVertexConstantMVP.mvp = Context::sVertexConstantMVP.Project *
        Context::sVertexConstantMVP.View * Context::sVertexConstantMVP.World;


    }

} // namespace gfx
