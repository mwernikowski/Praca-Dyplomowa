#version 400
in vec4 ex_Color;
in vec2 TexCoord;
in vec3 Normal;
in vec4 xPosition;

uniform sampler2D tex;
uniform sampler2D luminance;
uniform float x;
uniform float y;

uniform vec3 LightPosition;
uniform vec3 EyePosition;
uniform vec3 matColor;
uniform float mode;
uniform float lightOn;

out vec3 outputColor;

void main()
{
	float NdL = dot(normalize(Normal), normalize(-xPosition.xyz + LightPosition));
	vec3 H = normalize(normalize(-xPosition.xyz + LightPosition));
	float spec = clamp(pow(dot(normalize(Normal), H), 30.0f), 0.0, 1.0);
	vec3 color;

	if (mode < 0.0f)
	{
		color = (NdL * vec4(matColor,1).rgb / 1.0f + spec) / 100.0f;
	}
	else if (mode < 10.0f)
	{
		color = (NdL * texture(tex, TexCoord).rgb / 1.0f + spec) / 100.0f;
	}
	else if (mode == 10.0f)
	{
		color = vec3(5.0f, 5.0f, 5.0f) + spec;
	}

	if (lightOn < 1.0f) {
		if (mode == 10.0f)
			color = vec3(0,0,0);
		else
			color *= 0.01f;
	}
		

	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);
	float compFactor = texture(luminance, TexCoord, 20).r / texture(luminance, TexCoord, 20).g;
	
	float Y = dot(color, luminanceConvert);
	float aa = 1.002 * exp(-pow((compFactor - 9.949) / 6.806, 2));
	float ldrY = Y / (Y + compFactor);
	vec3 ldr;
	ldr.x = pow(color.x / Y, 0.8) * ldrY;
	ldr.y = pow(color.y / Y, 0.8) * ldrY;
	ldr.z = pow(color.z / Y, 0.8) * ldrY;
	
	outputColor.x = pow(ldr.x, 0.4) * 0.8;
	outputColor.y = pow(ldr.y, 0.4) * 0.8;
	outputColor.z = pow(ldr.z, 0.4) * 0.8;
}	