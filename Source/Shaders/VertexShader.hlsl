struct vertexIn
{
    float3 position : POSITION;
    float4 color : COLOR;
};

struct vertexOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
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
    output.color = input.color;
    
    return output;
}