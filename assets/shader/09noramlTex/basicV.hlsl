
cbuffer cWorldMatrix:register(b3)
{
  matrix gWorld;
  matrix gWordlInvTranspose;
};

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
  float3 normal :NORMAL;
  float2 texCoord:TEXCOORD;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionW:POSITION;
  float4 color : COLOR;
  float3 normal :NORMAL;
  float2 texCoord:TEXCOORD;
};

pixelIn vsMain(vertexIn vIn)
{

  pixelIn pIn;
  //n.position = mul(float4(vIn.position,1.0f),mvp);
  //float4 worldPos = mul(float4(vIn.position,1.0f),gWorld);
  //float4 viewPos = mul(worldPos,view);
  //float4 clipPos = mul(viewPos,project);
  pIn.position = mul(mul(mul(float4(vIn.position, 1.0), gWorld), view), project);

  pIn.color = vIn.color;
  float4 poW = mul(float4(vIn.position,1.0f),gWorld);
  pIn.positionW = poW.xyz;
  pIn.normal = vIn.normal;
  pIn.texCoord = vIn.texCoord;
  return pIn;

 /*
  pixelIn pIn;
  pIn.position = float4(vIn.position,1.0f);
  pIn.color = vIn.color;
  pIn.normal = vIn.normal;
  pIn.texCoord = vIn.texCoord;
  return pIn;
  */

}
