struct vertexIn
{
    float3 position : POSITION;
    float2 uv : TEXCOORD;
};

struct vertexOut
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

cbuffer ConstantBuffer
{
    matrix worldMatrix;
    Matrix viewMatrix;
    matrix projectionMatrix;
}

vertexOut main(vertexIn input)
{
    vertexOut output;
    output.position = mul(float4(input.position, 1.0f), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    output.uv = input.uv;
    
    return output;
}