
cbuffer ConstantBuffer:register(b0)
{
    matrix gWorld;
    matrix gWorldInvTranspose;
    matrix gView;
    matrix gProject;
    matrix gViewProject;
    matrix mvp;
}

struct vertexIn
{
  float3 position: POSITION;
  float4 color:COLOR;
  float3 normal: NORMAL;
  float2 tex: TEXCOORD0;

};

struct vertexOut
{
    float4 position:SV_POSITION;
    float3 posW:POSITION;
    float4 color:COLOR;
    float3 normal: NORMAL;
    float2 tex: TEXCOORD0;
};
vertexOut vsMain(vertexIn pIn)
{
  vertexOut pOut;
  pOut.position = mul(float4(pIn.position,1.0f),mvp);
  pOut.posW = mul(float4(pIn.position,1.0f),gWorld).xyz;

  pOut.normal = mul(pIn.normal,(float3x3)gWorldInvTranspose);
  
  pOut.color = pIn.color;
  pOut.tex = pIn.tex;
  return pOut;

}
