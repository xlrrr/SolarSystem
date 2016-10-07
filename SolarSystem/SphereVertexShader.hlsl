struct Output {
	float4 position : SV_POSITION;
	float3 color : COLOR;
};
struct Input {
	float4 position : POSITION;
	float3 color : COLOR;
};
Output main(Input input)
{
	Output output;
    output.position = float4(input.position.x, input.position.y, input.position.z,1);
	output.color = float3(0.1f, 0.5f, 0.3f);
	return output;

}