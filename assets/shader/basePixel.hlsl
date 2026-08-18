
cbuffer ConstantBuffer:register(b1)
{
  float4 color;
};

struct vertexOut
{
    float4 position:SV_POSITION;
    float4 color:COLOR;
    float2 tex: TEXCOORD0;
};

Texture2D tex2d:register(t0);
SamplerState tsampler:register(s0);

float4 psMain(vertexOut pOut):SV_TARGET
{
    return color * tex2d.Sample(tsampler,pOut.tex) * pOut.color;
}
