#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
uniform sampler2D mask;
out vec3 outputColor;

void main() {
	double luminance = texture2D(tex, TexCoord).r + texture2D(tex, TexCoord).g + texture2D(tex, TexCoord).b;
	outputColor = vec3(texture(mask, TexCoord).r * luminance, texture(mask, TexCoord).r, 0);
}