Texture2D baseColor : register(t0);
Texture2D emmisiveMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samplerView : register(s0);

cbuffer LightObject : register(b0)
{
    float3 ambientColor;
    float ambientIntensity;
    
    float3 lightColor;
    float lightIntensity;
    float3 lightPosition;
};

struct pixelIn
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
    float3 worldPos : WORLD_POSITION;
};

float4 ps_main(pixelIn input) : SV_TARGET
{
    float3 sampleColor = baseColor.Sample(samplerView, input.uv).rgb;
    float3 sampleEmmisive = emmisiveMap.Sample(samplerView, input.uv).rgb;
    
    float3 ambientLight = ambientColor * ambientIntensity;
    float3 appliedLight = ambientLight;
    
    float3 vectorToLight = normalize(lightPosition - input.worldPos);
    float diffuseLightIntensity = max(dot(vectorToLight, input.normal), 0);
    float3 diffuseLight = lightColor * lightIntensity * diffuseLightIntensity;
    
    appliedLight += diffuseLight;
    
    float3 finalColor = sampleColor * appliedLight + sampleEmmisive;
    
    return float4(finalColor, 1);
    
}