
TextureCube gTex:register(t0);
SamplerState gSampler:register(s0);

struct PixelIn{
  float4 posH : SV_POSITION;
  float3 posW : POSITION;
  float4 color :COLOR;
  float3 normal:NORMAL;
  float2 uv : TEXCOORD;
};

float4 psMain(PixelIn pIn):SV_TARGET
{
  float3 dir = normalize(pIn.posW);
  float4 texColor = gTex.Sample(gSampler,pIn.posW);
  return texColor;
}
