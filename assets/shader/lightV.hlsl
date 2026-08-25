cbuffer vMvpConstant :register(b0)
{
  matrix gMvp;
  matrix gWorld;
  matrix gView;
  matrix gProject;
  matrix gWorldInvTranspose;
};

struct vertexIn
{
  float3 position:POSITION;
  float4 color :COLOR;
  float3 normal:NORMAL;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionWorld:POSITION;
  float4 color: COLOR;
  float3 normal: NORMAL;
};

pixelIn vsMain(vertexIn vIn)
{
  pixelIn pIn;
  pIn.position = mul(float4(vIn.position,1.0f),gMvp);

  float4 posW = mul(float4(vIn.position,1.0f),gWorld);
  pIn.positionWorld = posW.xyz;
  pIn.normal = mul(vIn.normal,(float3x3)gWorldInvTranspose);
  pIn.color = vIn.color;
  return pIn;
}

