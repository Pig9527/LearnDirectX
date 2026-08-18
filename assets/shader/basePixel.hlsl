cbuffer cMaterial:register(b1)
{
    float4 gMaterialAmbient;
    float4 gMaterialDiffuse;
    float4 gMaterialSpecular;
    float gSpecularPower;
    float pad[3];
}

cbuffer cLight:register(b2)
{
    float3 gLightDir;
    float3 gLightColor;
    float3 gEyePos;
    float pad1[3];
}

struct vertexOut
{
    float4 position:SV_POSITION;
    float3 posW:POSITION;
    float4 color:COLOR;
    float3 normal: NORMAL;
    float2 tex: TEXCOORD0;
};

Texture2D tex2d:register(t0);
SamplerState tsampler:register(s0);

float4 psMain(vertexOut pOut):SV_TARGET
{
    float3 normal = normalize(pOut.normal);
    float3 lightDir = normalize(gLightDir);
    float3 viewDir = normalize(gEyePos - pOut.posW);

    //环境光
    float3 ambient = gMaterialAmbient * pOut.color.rgb;

    //漫发射
    float diff = max(dot(normal,lightDir),0.0f);
    float3 diffuse = gLightColor * pOut.color.rgb * gMaterialDiffuse;

    //高光
    float3 halfDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal,halfDir),0.0f),gMaterialSpecular);
    float3 specular = gLightDir*spec;
    float3 final = ambient + diffuse + specular;

    return  tex2d.Sample(tsampler,pOut.tex) * pOut.color * float4(final,1.0f);
}
