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

vertexOut main(vertexIn input)
{
    vertexOut output;
    output.position = float4(input.position, 1.0);
    output.color = input.color;
    
    return output;
}