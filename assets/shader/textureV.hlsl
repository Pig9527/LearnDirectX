
cbuffer vertexConstant:register(b0)
{
  matrix mvp;
};

struct vertexIn
{
  float3 position:POSITION;
  float4 color:COLOR;
  float2 texCoord:TEXCOORD;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float4 color : COLOR;
  float2 texCoord:TEXCOORD;
};

pixelIn vsMain(vertexIn vIn)
{
  pixelIn pIn;
  pIn.position = mul(float4(vIn.position,1.0f),mvp);
  pIn.color = vIn.color;
  //pIn.normal = vIn.normal;
  pIn.texCoord = vIn.texCoord;
  return pIn;

}