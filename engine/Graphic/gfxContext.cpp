#include "gfxContext.h"
#include "Context.h"
void gfx::gfxContext::Initialize()
{

  HR(CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)m_pFactory.GetAddressOf()));

  D3D_FEATURE_LEVEL features[] = {D3D_FEATURE_LEVEL_11_0,D3D_FEATURE_LEVEL_11_1};
  D3D_FEATURE_LEVEL select;

  HR(D3D11CreateDevice(
    nullptr,
    D3D_DRIVER_TYPE_HARDWARE,
    nullptr,
    D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
    features,
    ARRAYSIZE(features),
    D3D11_SDK_VERSION,
    m_pDevice.GetAddressOf(),
    &select,
    m_pDeviceContext.GetAddressOf()));

  DXGI_SWAP_CHAIN_DESC sd ={};
  sd.BufferDesc.Width = Context::sWindowWidth;
  sd.BufferDesc.Height = Context::sWindowHeight;
  sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
  sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
  sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
  sd.BufferDesc.RefreshRate.Denominator = 0;
  sd.BufferDesc.RefreshRate.Numerator = 0;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.Flags = 0;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
  sd.OutputWindow = Context::sHwnd;
  sd.Windowed = true;
  sd.BufferCount = 1;
  HR(m_pFactory->CreateSwapChain(m_pDevice.Get(),&sd,m_pSwapChain.GetAddressOf()));

  HR(m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(void**)m_pBackbuffer.GetAddressOf()));

  HR(m_pDevice->CreateRenderTargetView(m_pBackbuffer.Get(),nullptr,m_pRenderView.GetAddressOf()));

  D3D11_TEXTURE2D_DESC depth = {};
  depth.ArraySize = 1;
  depth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  depth.CPUAccessFlags = 0;
  depth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
  depth.MipLevels = 0;
  depth.MiscFlags = 0;
  depth.SampleDesc.Count = 1;
  depth.SampleDesc.Quality = 0;
  depth.Width =  Context::sWindowWidth;
  depth.Height =  Context::sWindowHeight;
  depth.Usage = D3D11_USAGE_DEFAULT;

  HR(m_pDevice->CreateTexture2D(&depth,nullptr,m_pDepthStencilBuffer.GetAddressOf()));

  HR(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer.Get(), nullptr, m_pDepthStencilView.GetAddressOf()));

  D3D11_VIEWPORT viewport;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  viewport.Width =  Context::sWindowWidth;
  viewport.Height =  static_cast<float>(Context::sWindowHeight);
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;

  m_pDeviceContext->OMSetRenderTargets(1,m_pRenderView.GetAddressOf(),m_pDepthStencilView.Get());
  
  m_pDeviceContext->RSSetViewports(1,&viewport);

  HR(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,m_pD2dFactory.GetAddressOf()));

  comptr<IDXGISurface> surface;
  HR(m_pSwapChain->GetBuffer(0,__uuidof(IDXGISurface),reinterpret_cast<void**>(surface.GetAddressOf())));

  D2D1_RENDER_TARGET_PROPERTIES props;
  ZeroMemory(&props,sizeof(props));
  props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT,
  props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN,D2D1_ALPHA_MODE_PREMULTIPLIED);

  HR(m_pD2dFactory->CreateDxgiSurfaceRenderTarget(surface.Get(),&props,m_pD2dRenderTarget.GetAddressOf()));

  surface.Reset();
  HR(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,__uuidof(IDWriteFactory),reinterpret_cast<IUnknown**>(m_pDwriteFactory.GetAddressOf())));

  HR(m_pDwriteFactory->CreateTextFormat(L"SimSun" ,nullptr,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,
    DWRITE_FONT_STRETCH_NORMAL,20, L"zh-cn",m_pDwriteFormat.GetAddressOf()
  ));

  HR(m_pD2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White),m_pColorBrush.GetAddressOf()));
}

gfx::gfxContext::gfxContext()
{
  
}

gfx::gfxContext::~gfxContext()
{
}

