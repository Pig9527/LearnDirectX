
TextureCube  gTex:register(t0);
SamplerState gSampler:register(s0);

struct PixelIn
{
  float4 posH:SV_POSITION;
  float3 posL:POSITION;
  float4 color:COLOR;
  float3 normal: NORMAL;
  float2 texCoord:TEXCOORD;

};

float4 psMain(PixelIn pIn):SV_TARGET
{
   float3 dir = normalize(pIn.posL);
  float4  texColor = gTex.Sample(gSampler,pIn.posL);

 
  //return float4(dir * 0.5f + 0.5f, 1.0f);
  return  texColor;
}
