struct DirectLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 direction;
  float pad;
};

struct Material
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float4 reflect;
};


cbuffer PhongLightMode:register(b2)
{
  DirectLight gDirectLight;
  Material gMaterial;
  matrix gVeiwProject;
  float3 gEyePos;
  float repeat;
};

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


  float4 texColor = gTex.Sample(gSampler,pIn.texCoord*repeat);
  
  //direct light
  float3 toEye = normalize(gEyePos - pIn.positionW);
  float3 lightVec = -gDirectLight.direction;
  ambient = gMaterial.ambient * gDirectLight.ambient;
  pIn.normal = normalize(pIn.normal);
  //return float4(pIn.normal * 0.5 + 0.5, 1.0);
  float diffuseFactor = dot(lightVec,pIn.normal);
  [flatten]
  if(diffuseFactor> 0.0f)
  {
    float3 v = reflect(-lightVec,pIn.normal);
    float specFact = pow(max(dot(v,toEye),0.0f),gMaterial.specular.w);
    diffuse = diffuseFactor * gMaterial.diffuse * gDirectLight.diffuse;
    specular = specFact* gMaterial.specular * gDirectLight.specular;
  }
  float4 litColor = texColor * (ambient + diffuse) + specular;
  litColor.a = texColor.a *gMaterial.diffuse.a;
  return litColor;
}
