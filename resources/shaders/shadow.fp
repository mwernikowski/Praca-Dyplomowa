#version 400
in vec4 ex_Color;
in vec2 TexCoord;
in vec3 Normal;
in vec4 xPosition;

uniform sampler2D tex;
uniform vec3 LightPosition;
uniform vec3 EyePosition;
uniform vec3 matColor;
uniform float mode;

out vec4 outputColor;

void main()
{
	float NdL = dot(normalize(Normal), normalize(-xPosition.xyz + LightPosition));
	vec3 H = normalize(normalize(-xPosition.xyz + LightPosition));
	float spec = clamp(pow(dot(normalize(Normal), H), 30.0f), 0.0, 1.0);

	if (mode < 0.0f)
	{
		outputColor = NdL * vec4(matColor,1) + spec;
	}
	else if (mode < 10.0f)
	{
		outputColor = NdL * texture2D(tex, TexCoord) + spec;
	}
	else if (mode == 10.0f)
	{
		outputColor = vec4(1.0f, 1.0f, 1.0f, 0.0f);
	}
}