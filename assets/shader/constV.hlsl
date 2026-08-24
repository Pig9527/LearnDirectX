
struct vertexIn
{
  float3 position:POSITION;
  float4 color:COLOR;
};
struct pixelIn
{
  float4 position:SV_POSITION;
  float4 color:COLOR;
};

pixelIn vsMain(vertexIn vIn)
{
  pixelIn pIn;
  pIn.position = float4(vIn.position,1.0f);
  pIn.color = vIn.color;
  return pIn;
}
