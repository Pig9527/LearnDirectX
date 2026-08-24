
struct vertexIn
{
  float3 position:POSITION;
  float4 color: COLOR;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float4 color:COLOR;
};

pixelIn vsMain(vertexIn vIn)
{
  pixelIn pixel;
  pixel.position = float4(vIn.position,1.0f);
  pixel.color = vIn.color;
  return pixel;
}
