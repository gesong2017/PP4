cbuffer WorldViewProjectionConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
};

struct VertexShaderInput
{
	float3 posL : POSITION;
};

struct PixelShaderInput
{
	float4 posH : SV_POSITION;
	float3 uvw : UVW;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;

	float4 pos = float4(input.posL, 1.0f);
	output.uvw = input.posL;
	// Transform the vertex position into projected space.
	pos = mul(pos, world);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.posH = pos;

	return output;
}