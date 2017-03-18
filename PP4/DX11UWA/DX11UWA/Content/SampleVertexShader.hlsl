// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model[3];
	matrix view;
	matrix projection;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
	float4 pos : POSITION;
	float4 uv : UV;
	float4 norm : NORMAL;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
	float4 pos : SV_POSITION;
	float4 uv : UV;
	float4 norm : Normal;
	float4 lPos : LPOSITION;
	float4 lightV: LV;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input, uint idx : SV_InstanceID)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos);
	// Transform the vertex position into projected space.
	pos = mul(pos, model[idx]);
	output.lPos = pos;
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	output.lightV = mul(input.pos, model[idx]);
	output.lightV = mul(output.lightV, lightViewMatrix);
	output.lightV = mul(output.lightV, lightProjectionMatrix);
	// Pass the color through without modification.
	output.uv = input.uv;
	output.norm = input.norm;
	return output;
}
