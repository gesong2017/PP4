cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

cbuffer ReflectionBuffer
{
	matrix reflectionMatrix;
};

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float4 reflectionPosition : TEXCOORD1;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;
	float4 pos = float4(input.position, 1.0f);
	matrix reflectProjectWorld;

	// Calculate the position of the vertex against the world, view, and projection matrices.
	pos = mul(pos, worldMatrix);
	pos = mul(pos, viewMatrix);
	pos = mul(pos, projectionMatrix);

	// Store the output information for the pixel shader to use.
	output.position = pos;
	output.tex = input.tex;

	// Create the reflection projection world matrix.
	reflectProjectWorld = mul(reflectionMatrix, projectionMatrix);
	reflectProjectWorld = mul(worldMatrix, reflectProjectWorld);

	// Calculate the input position against the reflectProjectWorld matrix.
	output.reflectionPosition = mul(float4(input.position, 1.0f), reflectProjectWorld);

	return output;
}