Texture2D texture1 : register(t0);
SamplerState ss : register(s0);

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

float4 main(PixelShaderInput input) : SV_TARGET
{   
	return input.color * texture1.Sample(ss, input.texcoord);
}