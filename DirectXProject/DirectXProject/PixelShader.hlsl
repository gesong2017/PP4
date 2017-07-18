Texture2D Texture1;
Texture2D Texture2;
SamplerState ss;
float4 main(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{   
	float4 Color1 = Texture1.Sample(ss, texcoord);
	float4 Color2 = Texture2.Sample(ss, texcoord);
	return Color1 + Color2;
}