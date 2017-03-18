cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model[3];
	matrix view;
	matrix projection;
	matrix lightViewMatrix;
	matrix lightProjectionMatrix;
};

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
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main(VertexShaderInput input, uint idx : SV_InstanceID)
{
	PixelShaderInput output;
	float4 pos = float4(input.pos);

	// Transform the vertex position into projected space.
	pos = mul(pos, model[idx]);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// Pass the color through without modification.
	output.uv = input.pos;

	return output;
}
