
Texture2D gTex :register(t1);
SamplerState gSampler:register(s0);

struct pixelIn
{
  float4 position:SV_POSITION;
  float4 color : COLOR;
  float2 texCoord:TEXCOORD;
};

float4 psMain(pixelIn pIn):SV_TARGET
{
  //return float4(pIn.texCoord,0.0f,1.0f);
  return pIn.color * gTex.Sample(gSampler,pIn.texCoord);
}