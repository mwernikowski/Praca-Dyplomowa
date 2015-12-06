#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
uniform float x;
uniform float y;
uniform float color;
out vec3 outputColor;

void main()
{
	float l = length(TexCoord - vec2(x, y));
	if (l < 0.003f)
		outputColor = vec3(1.0f, 1.0f, 1.0f);
	else if (l < 0.005f)
		outputColor = vec3(0.0f, 1.0f, 0.0f);
	else {
		vec3 color = texture(tex, TexCoord).rgb;
		outputColor = color;
	}
	//outputColor = vec3(TexCoord.x * 2.0, TexCoord.y * 2.0, 0);
}