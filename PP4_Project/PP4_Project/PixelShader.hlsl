Texture2D shaderTexture;
SamplerState SampleType;
struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 uv : UV;
};

float4 main(PixelShaderInput input) : SV_TARGET
{   
	float4 textureColor;
    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    textureColor = shaderTexture.Sample(SampleType, input.uv);

	return textureColor;
}