cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexShaderInput
{
	float3 posL : POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

struct PixelShaderInput
{
	float4 posH : SV_POSITION;
	float2 uv : UV;
	float3 normal : NORMAL;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;


	// Change the position vector to be 4 units for proper matrix calculations.
	float4 pos = float4(input.posL, 1.0f);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	pos = mul(pos, worldMatrix);
	pos = mul(pos, viewMatrix);
	pos = mul(pos, projectionMatrix);

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Store the value to ouput
	output.posH = pos;
	output.uv = input.uv;

	return output;
}