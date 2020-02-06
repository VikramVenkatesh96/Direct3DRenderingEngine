Texture2D tex;

SamplerState smplr;

float4 main(float2 tc: TexCoord) :SV_Target
{	
	float4 tempTex = tex.Sample(smplr, tc);
	clip(tempTex.a < 1.0f ? -1 : 1);
	return tempTex;
}