
Texture2D gTex :register(t1);
SamplerState gSampler:register(s0);

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionW:POSITION;
  float4 color : COLOR;
  float3 normal :NORMAL;
  float2 texCoord:TEXCOORD;
};

float4 psMain(pixelIn pIn):SV_TARGET
{
  //return float4(pIn.texCoord,0.0f,1.0f);

  float4 ambient,diffuse,specular;
  ambient = diffuse = specular= float4(0.0f,0.0f,0.0f,0.0f);

  float4 texColor = gTex.Sample(gSampler,pIn.texCoord*1);
 
  return texColor;
}
