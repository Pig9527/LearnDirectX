
Texture2D gTex :register(t1);
SamplerState gSampler:register(s0);


struct Material
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float4 reflect;
};

struct DirectLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 direction;
  float pad;
};

cbuffer PSConstant:register(b1)
{
  Material gMaterial;
  DirectLight gLight;
  float3 gEye;
  float pad;
};

cbuffer PStexture:register(b2)
{
  float tiling;
  float3 pad2;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionW:POSITION;
  float4 color : COLOR;
  float3 normal:NORMAL;
  float2 texCoord:TEXCOORD;
};

float4 psMain(pixelIn pIn):SV_TARGET
{
  //return float4(pIn.texCoord,0.0f,1.0f);

  float4 ambient,diffuse,specular;
  ambient = diffuse = specular= float4(0.0f,0.0f,0.0f,0.0f);

  float4 texColor = gTex.Sample(gSampler,pIn.texCoord*tiling);
  //return  gLight.ambient * texColor;

  float3 normal = normalize(pIn.normal);
  float eye = normalize(gEye - pIn.positionW);
  float3 lightVec = -gLight.direction;
  ambient = gMaterial.ambient * gLight.ambient;

  float diffuseFactor = dot(lightVec,normal);
  [flatten]
  if(diffuseFactor > 0.0f)
  {
    float3 v = reflect(-lightVec,normal);
    float specFactor = pow(max(dot(v,eye),0.0f),gMaterial.specular.w);
    diffuse = diffuseFactor * gMaterial.diffuse * gLight.diffuse;
    specular = specFactor * gMaterial.specular* gLight.specular;
  }
  float4 litColor = pIn.color * texColor * (ambient+diffuse) +specular;
  litColor.a = gMaterial.diffuse.a * pIn.color.a * texColor.a;
  return litColor;
}
