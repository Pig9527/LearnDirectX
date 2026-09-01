
TextureCube  gTex:register(t0);
SamplerState gSampler:register(s0);

struct PixelIn
{
  float4 posH:SV_POSITION;
  float3 posL:POSITION;
  float4 color:COLOR;
#if 0
 
  float3 normal: NORMAL;
  float2 texCoord:TEXCOORD;
#endif
};

float4 psMain(PixelIn pIn):SV_TARGET
{
  float4  texColor = gTex.Sample(gSampler,pIn.posL);
  return  texColor;
}
