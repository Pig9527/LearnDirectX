
Texture2D gDiffuse:register(t1);
Texture2D gNormalMap:register(t2);
SamplerState gSampler:register(s0);

struct DirectLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 direction;
  float pad;
};


struct PointLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 position;
  float range;
  float3 att;
  float pad1;
};

struct Material
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float4 reflect;
};

cbuffer Ph0ngLightMode:register(b2)
{
  DirectLight gDirectLight;
  PointLight gPointLight;
  Material gMaterial;
  matrix gViewProj;
  float3 gEyePos;
  float repeat;
};

struct PixelIn
{
  float4 pos:SV_POSITION;
  float3 posW:POSITION;
  float4 color:COLOR;
  float3 normal:NORMAL;
  float2 uv:TEXCOORD;
  float4 tangent:TANGENT;
};


void ComputePointLight(Material mat,PointLight L,float3 pos,float3 normal,float3 toEye,
  out float4 ambient,out float4 diffuse,out float4 spec)
{
  ambient = float4(0.0f,0.0f,0.0f,0.0f);
  diffuse = float4(0.0f,0.0f,0.0f,0.0f);
  spec = float4(0.0f,0.0f,0.0f,0.0f);

  float3 lightDir = L.position - pos;
  float d = length(lightDir);

  if(d > L.range)
    return;
  lightDir /= d;

  ambient =mat.ambient * L.ambient;

  float diffuseFactor = dot(lightDir,normal);
  [flatten]
  if(diffuseFactor > 0.0f)
  {
    float3 v = reflect(-lightDir,normal);
    float specFactor = pow(max(dot(v,toEye),0.0f),mat.specular.w);
    diffuse = diffuseFactor * mat.diffuse * L.diffuse;
    spec = specFactor  * mat.specular * L.specular;
  }

  float att = 1.0f / dot(L.att,float3(1.0f,d,d*d));
  diffuse *= att;
  spec *= att;

}

void ComputeDirectLight(Material mat,DirectLight L,float3 normal,float3 eye,
  out float4 ambient,out float4 diffuse,out float4 spec)
{
  ambient = float4(0.0f,0.0f,0.0f,0.0f);
  diffuse = float4(0.0f,0.0f,0.0f,0.0f);
  spec = float4(0.0f,0.0f,0.0f,0.0f);

  float3 lightVec = -L.direction;
  ambient = mat.ambient * L.ambient;

  float diffuseFactor = dot(lightVec,normal);
  [flatten]
  if(diffuseFactor > 0.0f)
  {
    float3 v = reflect(-lightVec,normal);
    float specFactor = pow(max(dot(v,eye),0.0f),mat.specular.w);
    diffuse = diffuseFactor * mat.diffuse * L.diffuse;
    spec = specFactor * mat.specular * L.specular;
  }
}

float3 NormalSampleToWorldSpace(float3 normalSample,float3 uintNormalW,float3 tangentW)
{
  float3 normalT = 2.0f * normalSample - 1.0f;
  float3 N = uintNormalW;
  float3 T = normalize(tangentW.xyz - dot(tangentW.xyz,N)*N);
  float3 B = cross(N,T);

  float3x3 TBN = float3x3(T,B,N);

  float3 bumpedNormalW =mul(normalT,TBN);
  return bumpedNormalW;
}

float4 psMain(PixelIn pIn):SV_TARGET
{
  float4 texColor = gDiffuse.Sample(gSampler,pIn.uv * repeat);
  
  clip(texColor.a - 0.1f);

  pIn.normal = normalize(pIn.normal);
  pIn.tangent.xyz = normalize(pIn.tangent.xyz);

  float4 ambient,diffuse,specular;
  float4 A,D,S;
  ambient=float4(0.0f,0.0f,0.0f,0.0f);
  diffuse=float4(0.0f,0.0f,0.0f,0.0f);
  specular=float4(0.0f,0.0f,0.0f,0.0f);
  int i;
  float3 toEye =normalize(gEyePos - pIn.posW);
  float dist = distance(gEyePos,pIn.posW);

  float3 normalMapSample = gNormalMap.Sample(gSampler,pIn.uv * repeat).rgb;
  float3 bumpedNormalW = NormalSampleToWorldSpace(normalMapSample,pIn.normal,pIn.tangent);

  [unroll]
  for(i = 0;i <1; i++)
  {
    ComputeDirectLight(gMaterial,gDirectLight,bumpedNormalW,toEye,A,D,S);
    ambient += A;
    diffuse += D;
    specular += S;
  }

  [unroll]
  for(i = 0;i<1 ;i++)
  {
    ComputePointLight(gMaterial,gPointLight,pIn.posW,bumpedNormalW,toEye,A,D,S);
    ambient += A;
    diffuse += D;
    specular += S;
  }


  float4 litColor = texColor *(ambient + diffuse) + specular;

  litColor.a = texColor.a * gMaterial.diffuse.a;
  return litColor;
}
