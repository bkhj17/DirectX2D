cbuffer WorldBuffer : register(b0)
{
    matrix world;
};

cbuffer ViewBuffer : register(b1)
{
    matrix view;
};

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
};

struct VertexInput
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct VertexOutput
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, projection);
    output.color = input.color;
    return output;
}

