cbuffer cColor :register(b1)
{
  float3 gColor;
};

struct pixelIn
{
  float4 position: SV_POSITION;
  float4 color: COLOR;
};

float4 psMain(pixelIn pIn):SV_TARGET
{
  return pIn.color * float4(gColor,1.0f);
}