

texture2D model : register(t0);
texture2D modelT : register(t1);
SamplerState modelFilter[2] : register(s0);

float4 main(float4 pos : SV_POSITION, float4 uv : UV, float4 normal : NORMAL, float4 lPos : LPOSITION, float4 lightV : LV) : SV_TARGET
{
	//clip(uv.);
	if (model.Sample(modelFilter[0], uv).a <= 0.5)
	return model.Sample(modelFilter[0], uv);

float4 shadowLightPos;
float ourDepth = pos.z / pos.w;
float sampleDepth = model.Sample(modelFilter[0], (lPos.xy / lPos.w + 1) / 2);
float shadowFactor = (ourDepth <= sampleDepth);

float4 lightDir = { -50, -50, 30, 1 };
float lightRatio = saturate(dot((normal), -normalize(lightDir)));
float4 lightColor = { 2,2,2,2 };
float4 ambientColor = { 0.5,0.5,0.5,1 };
float4 DirectionalLight = (saturate((model.Sample(modelFilter[0], uv))+(modelT.Sample(modelFilter[1], uv)*0.3)) * (lightColor * lightRatio));

float4 PlightDir = { 2, -3,3, 1 };
PlightDir = normalize(PlightDir - lPos.xyzw);
lightRatio = saturate(dot((normal), -(PlightDir)));
float4 PlightColor = { 0,0,1,1 };
float4 pointLight = (saturate((model.Sample(modelFilter[0], uv))+(modelT.Sample(modelFilter[1], uv)*0.3)) * (PlightColor * lightRatio));

float4 SlightDir = { 0, -3, 2.01 , 1 };
float4 coneDir = { 0, -0.8 ,-10 , 1 };
float coneRatio = 0.999999f;
SlightDir = normalize(SlightDir - lPos.xyzw);
float surfaceRatio = saturate(dot(-SlightDir, coneDir));
float spotFactor = (surfaceRatio > coneRatio) ? 1 : 0;
lightRatio = saturate(dot((SlightDir), (normal)));
float4 SlightColor = { 30,0,0,3 };
float4 SpotLight = (saturate((model.Sample(modelFilter[0], uv))+(modelT.Sample(modelFilter[1], uv)*0.3)) * (SlightColor * lightRatio) * spotFactor);

return  ((DirectionalLight + pointLight + SpotLight)/**shadowFactor*/) + (saturate((model.Sample(modelFilter[0], uv)) + (modelT.Sample(modelFilter[1], uv)*0.3))*ambientColor);
//return saturate((model.Sample(modelFilter[0], uv))+(modelT.Sample(modelFilter[1], uv)*0.5));
}