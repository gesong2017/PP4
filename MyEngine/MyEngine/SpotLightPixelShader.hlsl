Texture2D shaderTexture;
SamplerState SampleType;

cbuffer LightColorBuffer : register(b0)
{
	float4 diffuseColor;
};

cbuffer LightConeBuffer : register(b1)
{
	float3 coneDirection;
	float  coneRatio;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 lightDirection : TEXCOORD1;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
    float spotFactor, surfaceRatio, lightRatio;
	float4 color;

	// Calculate the surfaceratio.
	surfaceRatio = saturate(dot((-1.0f*input.lightDirection), coneDirection));

	// Calculate the spotfactor
	if (surfaceRatio > coneRatio)
	{
		spotFactor = 1.0f;
	}

	else
	{
		spotFactor = 0.0f;
	}

	// Calculate the lightratio.
	lightRatio = saturate(dot(input.lightDirection, input.normal));

	// Sample the texture pixel at this location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
	color = spotFactor * saturate(diffuseColor * lightRatio);

	// Calculate final color
	color = color * textureColor;

	return color;
}