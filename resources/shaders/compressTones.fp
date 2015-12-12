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
uniform vec3 matColor;
uniform float mode;
uniform float lightOn;

out vec3 outputColor;

void main()
{
	float NdL = abs(dot(normalize(Normal), normalize(-xPosition.xyz + LightPosition)));
	vec3 H = normalize(normalize(-xPosition.xyz + LightPosition));
	float spec = clamp(pow(dot(normalize(Normal), H), 30.0f), 0.0, 1.0);
	vec4 vColor;
	if (lightOn < 1.0f)
		spec = 0.0f;

	if (mode < 0.0f)
	{
		vColor = (NdL * vec4(matColor,1) / 1.0f + spec) / 100.0f;
	}
	else if (mode < 10.0f)
	{
		vColor = (NdL * texture2D(tex, TexCoord) / 1.0f + spec) / 100.0f;
	}
	else if (mode == 10.0f)
	{
		vColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	if (lightOn < 1.0f) {
		if (mode == 10.0f)
			vColor = vec4(0,0,0,1);
		else
			vColor *= 0.01f;
			vColor.r = vColor.g;
			vColor.b = vColor.g;
	}

	vec3 color = vColor.rgb;
	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);
	float compFactor = texture(luminance, vec2(0,0), 20).r / texture(luminance, vec2(0,0), 20).g;
	//compFactor = dot(luminanceConvert,  texture(luminance, TexCoord, 20).rgb);

	
	float Y = dot(color, luminanceConvert);
	float p = (compFactor - 9.949) / 6.806;
	float aa = 1.002 * exp(p) * exp(p);//pow(p, 2));
	float ldrY = Y / (Y + compFactor);
	vec3 ldr;
	
	ldr.x = pow(color.x / Y, 0.8) * ldrY;
	ldr.y = pow(color.y / Y, 0.8) * ldrY;
	ldr.z = pow(color.z / Y, 0.8) * ldrY;
	
	outputColor.x = pow(ldr.x, 0.4) * 0.8;
	outputColor.y = pow(ldr.y, 0.4) * 0.8;
	outputColor.z = pow(ldr.z, 0.4) * 0.8;

//	if (texture(luminance, vec2(0,0), 20).r == 0)
	//	outputColor = vec3(0,1,0);
	//outputColor = color / (color + aa);
	//outputColor = texture(tex, TexCoord).rgb;
}	