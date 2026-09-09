
cbuffer WorldMvp :register(b0)
{
  matrix mvp;
  matrix gWorld;
  matrix gView;
  matrix gProject;
  matrix gWorldInvTranspose;
};

struct VertexIn
{
  float3 pos :POSITION;
  float4 color :COLOR;
  float3 normal :NORMAL;
  float2 uv :TEXCOORD;
  float4 tangent :TANGENT;
};

struct PixelIn
{
  float4 pos:SV_POSITION;
  float3 posW:POSITION;
  float4 color:COLOR;
  float3 normal:NORMAL;
  float2 uv:TEXCOORD;
  float4 tangent:TANGENT;
};


PixelIn vsMain(VertexIn vIn)
{
  PixelIn pIn;

  vector posW = mul(float4(vIn.pos,1.0f),gWorld);
  pIn.posW = posW.xyz;

  pIn.pos = mul(float4(vIn.pos,1.0f),mvp);
  pIn.color = vIn.color;
  pIn.normal = mul(vIn.normal,(float3x3)gWorldInvTranspose);
  pIn.tangent = float4(mul(vIn.tangent.xyz,(float3x3)gWorld),vIn.tangent.w);
  pIn.uv = vIn.uv;

  return pIn;
}
