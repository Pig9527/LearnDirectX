
cbuffer VSConstantBuffer:register(b0)
{
  matrix mvp;
  matrix world;
  matrix view;
  matrix project;
  matrix worldInvTranspose;
};

struct VertexIn
{
  float3 pos:POSITION;
  float4 color:COLOR;
  float3 normal:NORMAL;
  float2 uv : TEXCOORD;
};
struct PixelIn
{
  float4 posH : SV_POSITION;
  float3 posW : POSITION;
  float4 color :COLOR;
  float3 normal:NORMAL;
  float2 uv : TEXCOORD;
};

PixelIn vsMain(VertexIn vIn)
{
  PixelIn pIn;
  float4x4 viewNoTranslation = view;
  viewNoTranslation._41 = 0.0f;
  viewNoTranslation._42 = 0.0f;
  viewNoTranslation._43 = 0.0f;

  float4 pos = float4(vIn.pos,1.0f);
  pos = mul(pos,viewNoTranslation);
  pos = mul(pos,project);

  pIn.posH = pos.xyww;
  pIn.posW = vIn.pos;

  pIn.color = vIn.color;
  pIn.normal = vIn.normal;
  pIn.uv = vIn.uv;

  return pIn;
}

