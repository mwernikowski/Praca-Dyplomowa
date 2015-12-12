#version 400
in vec4 ex_Color;
in vec2 TexCoord;
in vec3 Normal;
in vec4 xPosition;

uniform sampler2D tex;
uniform vec3 LightPosition;
uniform vec3 matColor;
uniform float mode;
uniform float lightOn;

out vec4 outputColor;

void main()
{
	float NdL = abs(dot(normalize(Normal), normalize(-xPosition.xyz + LightPosition)));
	vec3 H = normalize(normalize(-xPosition.xyz + LightPosition));
	float spec = clamp(pow(dot(normalize(Normal), H), 30.0f), 0.0, 1.0);
	if (lightOn < 1.0f)
		spec = 0.0f;

	if (mode < 0.0f)
	{
		outputColor = (NdL * vec4(matColor,1) / 1.0f + spec) / 1.0f;
	}
	else if (mode < 10.0f)
	{
		outputColor = (NdL * texture2D(tex, TexCoord) / 1.0f + spec) / 1.0f;
	}
	else if (mode == 10.0f)
	{
		outputColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (lightOn < 1.0f) {
		if (mode == 10.0f)
			outputColor = vec4(0,0,0,1);
		else
			outputColor *= 0.01f;
			outputColor.r = outputColor.g;
			outputColor.b = outputColor.g;
	}
}