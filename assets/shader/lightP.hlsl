
struct PSDirectLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float3 direction;
  float pad;
};

struct PSPointLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;

  float3 position;
  float range;

  float3 att;
  float pad;
};
struct PSSpotLight
{
  float4 ambient;
  float4 diffuse;
  float4 specular;

  float3 position;
  float range;

  float3 direction;
  float spot;

  float3 att;
  float pad;
};

struct PSMaterial
{
  float4 ambient;
  float4 diffuse;
  float4 specular;
  float4 reflect;
};

cbuffer PSOther:register(b1)
{
  PSDirectLight gDirectLight;
  PSPointLight gPointLight;
  PSSpotLight gSpotLight;
  PSMaterial gMaterial;
  float3 gEyePosition;
  float pad;
};

struct pixelIn
{
  float4 position:SV_POSITION;
  float3 positionWorld:POSITION;
  float4 color: COLOR;
  float3 normal: NORMAL;
};

void ComputeDirectLight(PSMaterial material,PSDirectLight directLight, float3 normal,float3 toEye, 
out float4 ambient,out float4 diffuse, out float4 spec)
{
  ambient = float4(0.0f,0.0f,0.0f,0.0f);
  diffuse = float4(0.0f,0.0f,0.0f,0.0f);
  spec = float4(0.0f,0.0f,0.0f,0.0f);

  float3 lightVec = -directLight.direction;
  ambient = material.ambient * directLight.ambient;
  
  float diffuseFactor = dot(lightVec,normal);

  [flatten]
  if(diffuseFactor > 0.0f)
  {
    float3 v = reflect(-lightVec,normal);
    float specFactor = pow(max(dot(v,toEye),0.0f),material.specular.w);

    diffuse = diffuseFactor * material.diffuse * directLight.diffuse;
    spec = specFactor * material.specular * directLight.specular;
  }
}

void ComputePointLight(PSMaterial mat,PSPointLight L,float3 pos,float normal,float eye,
  out float4 ambient,out float4 diffuse, out float4 spec)
{
  ambient = float4(0.0f,0.0f,0.0f,0.0f);
  diffuse = float4(0.0f,0.0f,0.0f,0.0f);
  spec = float4(0.0f,0.0f,0.0f,0.0f);

  float3 lightVec = L.position - pos;

  float d = length(lightVec);

  if(d>L.range)
  {
    return;
  }
  lightVec /= d;

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
  float att = .0f / dot(L.att,float3(1.0f,d,d*d));

  diffuse *=att;
  spec*= att;
}

void ComputeSpotLight(PSMaterial mat, PSSpotLight L,float3 pos, float3 normal, float3 eye,
  out float4 ambient, out float4 diffuse, out float4 spec)
{
  ambient = float4(0.0f,0.0f,0.0f,0.0f);
  diffuse = float4(0.0f,0.0f,0.0f,0.0f);
  spec = float4(0.0f,0.0f,0.0f,0.0f);

  float3 lightVec = L.position - pos;

  float d = length(lightVec);

  if(d> L.range)
  {return;}

  lightVec /= d;

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
  float spot = pow(max(dot(-lightVec,L.direction),0.0f),L.spot);
  float att = spot / dot(L.att,float3(1.0f,d,d*d));
  ambient *= spot;
  diffuse *= att;
  spec *= att;
}

float4 psMain(pixelIn pIn):SV_TARGET
{
  pIn.normal = normalize(pIn.normal);

  float3 toEyeW = normalize(gEyePosition - pIn.positionWorld);

  float4 ambient,diffuse,specular;
  float4 A,D,S;

  ambient = diffuse = specular= float4(0.0f,0.0f,0.0f,0.0f);
  ComputeDirectLight(gMaterial,gDirectLight,pIn.normal,toEyeW,A,D,S);
  ambient += A;
  diffuse += D;
  specular += S;

  ComputePointLight(gMaterial,gPointLight,pIn.positionWorld,pIn.normal,toEyeW,A,D,S);
  ambient += A;
  diffuse += D;
  specular += S;

  ComputeSpotLight(gMaterial,gSpotLight,pIn.positionWorld, pIn.normal,toEyeW,A,D,S);
  ambient += A;
  diffuse += D;
  specular += S;
  float4 litColor = pIn.color * (ambient + diffuse) + specular;

  litColor.a = gMaterial.diffuse.a * pIn.color.a;
  return litColor;
}
