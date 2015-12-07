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
	float NdL = dot(normalize(Normal), normalize(-xPosition.xyz + LightPosition));
	vec3 H = normalize(normalize(-xPosition.xyz + LightPosition));
	float spec = clamp(pow(dot(normalize(Normal), H), 30.0f), 0.0, 1.0);

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
		outputColor = vec4(5.0f, 5.0f, 5.0f, 1.0f) + spec;
	}

	if (lightOn < 1.0f) {
		if (mode == 10.0f)
			outputColor = vec4(0,0,0,1);
		else
			outputColor *= 0.01f;
	}

	float visibility = 1.0f;
	//if (texture2D(shadow, TexCoord).x < 1)
	//	visibility = 0.2f;
	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);

	float luminance = dot(outputColor.rgb, luminanceConvert);

	outputColor.r = luminance / 3.0f;

	luminance -= outputColor.r;

	outputColor.g = luminance / 2.0f;

	outputColor.b -= luminance - outputColor.g; 
}