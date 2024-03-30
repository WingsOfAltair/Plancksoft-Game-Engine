Texture2D tex2D;
SamplerState tex2DSampler;

struct pixelIn
{
    float4 position : SV_Position;
    float2 uv : TEXCOORD0;
};

float4 main(pixelIn input) : SV_TARGET
{
    return tex2D.Sample(tex2DSampler, input.uv);
}