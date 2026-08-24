cbuffer ColorBuffer:register(b0)
{
  float4 gColor;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float4 color:COLOR;
};

float4 psMain(pixelIn pIn):SV_TARGET
{
  return pIn.color * gColor;
}
