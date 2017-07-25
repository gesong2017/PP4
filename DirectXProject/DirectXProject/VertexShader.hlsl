//switch matrix to row major
#pragma pack_matrix(row_major)

cbuffer WorldViewProjectionConstantBuffer : register(b0)
{
	matrix world;
	matrix view;
	matrix projection;
	float4 lightvec;     // the diffuse light's vector
	float4 lightcol;      // the diffuse light's color
	float4 ambientcol;    // the ambient light's color
}

struct VertexShaderInput
{
	float3 posL : POSITION;
	float4 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	float4 pos = float4(input.posL, 1.0f);
	// Transform the vertex position into projected space.
	pos = mul(pos, world);
	pos = mul(pos, view);
	pos = mul(pos, projection);

	output.color = ambientcol;    // set the vertex color with ambient light
	float4 norm = normalize(mul(input.normal, world));    
	float diffusebrightness = saturate(dot(norm, lightvec));

	output.position = pos;
	output.color += lightcol * diffusebrightness;    // find the diffuse color and add
	output.texcoord = input.uv;    // set the texture coordinates, unmodified

	return output;
}