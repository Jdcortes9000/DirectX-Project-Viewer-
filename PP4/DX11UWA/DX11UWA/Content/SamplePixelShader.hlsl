// Per-pixel color data passed through the pixel shader.
//struct PixelShaderInput
//{
//	float4 pos : SV_POSITION;
//	float3 uv : UV;
//	
//};
//
//// A pass-through function for the (interpolated) color data.
//float4 main(PixelShaderInput input) : SV_TARGET
//{
//	return float4(input.uv, 1.0f);
//}

texture2D model : register(t0);

SamplerState modelFilter : register(s0);

float4 main(float4 pos : SV_POSITION, float4 uv : UV, float4 normal : NORMAL, float4 lPos : LPOSITION, float4 lightV : LV) : SV_TARGET
{
	//clip(uv.);
	if (model.Sample(modelFilter, uv).a <= 0.5)
	discard;

float4 shadowLightPos;
float ourDepth = pos.z / pos.w;
float sampleDepth = model.Sample(modelFilter, (lPos.xy / lPos.w + 1) / 2);
float shadowFactor = (ourDepth <= sampleDepth);

float4 lightDir = { -50, -50, 30, 1};
float lightRatio = saturate(dot((normal), -normalize(lightDir)));
float4 lightColor = { 2,2,2,2 };
float4 ambientColor = { 0.5,0.5,0.5,1 };
float4 DirectionalLight = (model.Sample(modelFilter, uv) * (lightColor * lightRatio));

float4 PlightDir = { 2, -3,3, 1 };
PlightDir = normalize(PlightDir - lPos.xyzw);
lightRatio = saturate(dot((normal), -(PlightDir)));
float4 PlightColor = { 0,0,1,1 };
float4 pointLight = (model.Sample(modelFilter, uv) * (PlightColor * lightRatio));

float4 SlightDir = { 0, -3, 2.01 , 1 };
float4 coneDir = { 0, -0.8 ,-10 , 1 };
float coneRatio = 0.999999f;
SlightDir = normalize(SlightDir - lPos.xyzw);

float surfaceRatio = saturate(dot(-SlightDir, coneDir));
float spotFactor = (surfaceRatio > coneRatio) ? 1 : 0;
 lightRatio = saturate(dot((SlightDir), (normal)));
float4 SlightColor = { 30,0,0,3 };
float4 SpotLight = (model.Sample(modelFilter, uv) * (SlightColor * lightRatio) * spotFactor);
return  ((DirectionalLight + pointLight + SpotLight)/**shadowFactor*/) + (model.Sample(modelFilter, uv)*ambientColor);
}
