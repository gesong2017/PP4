Texture2D shaderTexture;
SamplerState SampleType;

cbuffer DLightBuffer : register(b0)
{
	float4 dlightdiffuseColor;
	float3 lightDirection;
	float padding;
};

cbuffer PLightColorBuffer : register(b1)
{
	float4 plightdiffuseColor;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 plightDir : TEXCOORD1;
};

float4 main(PixelInputType input) : SV_TARGET
{
	float4 textureColor;
    float3 dlightDir;
    float dlightRatio, plightRatio;
	float4 color, dcolor, pcolor;

	// Sample the pixel color from the texture using the sampler at this texture coordinate location.
	textureColor = shaderTexture.Sample(SampleType, input.tex);

	// Invert the directional light direction for calculations.
	dlightDir = -lightDirection;

	// Calculate the amount of light on this pixel.
	dlightRatio = saturate(dot(input.normal, dlightDir));

	// Determine the final amount of diffuse color based on the diffuse color combined with the directional light intensity.
	dcolor = saturate(dlightdiffuseColor * dlightRatio);

	// Calculate the different amounts of light on this pixel based on the positions of the lights.
	plightRatio = saturate(dot(input.normal, input.plightDir));

	// Determine the diffuse color amount of each of the four lights.
	pcolor = plightdiffuseColor * plightRatio;

	// Multiply the texture pixel by the combination of all light colors to get the final result.
	color = saturate(dcolor + pcolor) * textureColor;

	return color;
}