cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer LightPositionBuffer
{
	float4 lightPosition;
};

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 lightDirection : TEXCOORD1;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 worldPosition;
	float4 pos = float4(input.position, 1.0f);

	// Calculate the position of the vertex in the world.
	worldPosition = mul(pos, worldMatrix);

	// Calculate the position of the vertex against the world, view, and projection matrices.
	pos = mul(pos, worldMatrix);
	pos = mul(pos, viewMatrix);
	pos = mul(pos, projectionMatrix);

	// Calculate the normal vector against the world matrix only.
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	// Normalize the normal vector.
	output.normal = normalize(output.normal);

	// Store the output information for the pixel shader to use.
	output.position = pos;
	output.tex = input.tex;

	// Determine the light direction based on the position of the lights and the position of the vertex in the world.
	output.lightDirection.xyz = lightPosition.xyz - worldPosition.xyz;
	output.lightDirection = normalize(output.lightDirection);

	return output;
}