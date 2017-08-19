cbuffer MatrixBuffer
{
	matrix worldMatrix;
	matrix viewMatrix;
	matrix projectionMatrix;
};

struct VertexInputType
{
	float3 position : POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
	float3 instancePosition : TEXCOORD1;
};

struct PixelInputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};

PixelInputType main(VertexInputType input)
{
	PixelInputType output;

	// Update the position of the vertices based on the data for this particular instance.
	input.position.x += input.instancePosition.x;
	input.position.y += input.instancePosition.y;
	input.position.z += input.instancePosition.z;
	float4 pos = float4(input.position, 1.0f);

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

	return output;
}