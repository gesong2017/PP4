cbuffer ConstantBuffer
{
	float4x4 matFinal;
	float4x4 rotation;    // the rotation matrix
	float4 lightvec;     // the diffuse light's vector
	float4 lightcol;      // the diffuse light's color
	float4 ambientcol;    // the ambient light's color
}

struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
	float2 texcoord : TEXCOORD;
};

VOut main(float4 position : POSITION, float4 normal : NORMAL, float2 texcoord : TEXCOORD)
{
	VOut output;

	output.position = mul(matFinal, position);    // transform the vertex from 3D to 2D
	output.color = ambientcol;    // set the vertex color with ambient light
	float4 norm = normalize(mul(rotation, normal));    
	float diffusebrightness = saturate(dot(norm, lightvec));
	output.color += lightcol * diffusebrightness;    // find the diffuse color and add
	output.texcoord = texcoord;    // set the texture coordinates, unmodified

	return output;
}