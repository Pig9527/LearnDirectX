cbuffer VertexConstBuffer:register(b0)
{
  matrix mvp;
  matrix world;
  matrix view;
  matrix project;
  matrix worldInvTranspose;
};

struct VertexIn
{
  float3 posL:POSITION;
  float4 color:COLOR;
  /*

  float3 normal: NORMAL;
  float2 texCoord:TEXCOORD;
*/
};

struct PixelIn
{
  float4 posH:SV_POSITION;
  float3 posL:POSITION;
  float4 color:COLOR;
  /*

  float3 normal: NORMAL;
  float2 texCoord:TEXCOORD;
*/
};

PixelIn vsMain(VertexIn vIn)
{
  PixelIn pIn;
  matrix worldview = mul(view,world);
  float4 posH = mul(float4(vIn.posL,1.0f),world);
  pIn.color = vIn.color;
  pIn.posH = posH.xyww;
  pIn.posL = vIn.posL;
  #if 0
  pIn.normal = vIn.normal;
  pIn.texCoord = vIn.texCoord;
  #endif

  return pIn;
}
