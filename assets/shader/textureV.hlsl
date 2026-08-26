
cbuffer vertexConstant:register(b0)
{
  matrix mvp;
  matrix world;
  matrix view;
  matrix project;
  matrix worldInvTranspose;
};

struct vertexIn
{
  float3 position:POSITION;
  float4 color:COLOR;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionW:POSITION;
  float4 color : COLOR;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

pixelIn vsMain(vertexIn vIn)
{
  pixelIn pIn;
  pIn.position = mul(float4(vIn.position,1.0f),mvp);
  pIn.color = vIn.color;
  //pIn.normal = vIn.normal;
  float4 poW = mul(float4(vIn.position,1.0f),world);
  pIn.positionW = poW.xyz;
  pIn.normal = mul(vIn.normal,(float3x3)worldInvTranspose);
  pIn.texCoord = vIn.texCoord;
  return pIn;

}
