#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
out vec3 outputColor;

void main()
{
	outputColor = texture2D(tex, TexCoord).rgb;
}