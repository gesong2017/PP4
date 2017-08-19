TextureCube skybox : register(t0);
SamplerState skyboxFilter : register(s0);

struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float3 uvw : UVW;
};

float4 main(PixelShaderInput input) : SV_TARGET
{
	return skybox.Sample(skyboxFilter,input.uvw);
}