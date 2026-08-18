
cbuffer ConstantBuffer:register(b0)
{
    matrix mvp;
}

struct vertexIn
{
  float3 position: POSITION;
  float4 color:COLOR;
  float2 tex: TEXCOORD0;
};

struct vertexOut
{
    float4 position:SV_POSITION;
    float4 color:COLOR;
    float2 tex: TEXCOORD0;
};
vertexOut vsMain(vertexIn pIn)
{
  vertexOut pOut;
  pOut.position = mul(float4(pIn.position,1.0f),mvp);
  pOut.color = pIn.color;
  pOut.tex = pIn.tex;
  return pOut;

}
