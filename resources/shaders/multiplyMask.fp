#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
uniform sampler2D mask;
out vec3 outputColor;

void main() {
	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);
	double luminance = dot(texture2D(tex, TexCoord).rgb, luminanceConvert);
	outputColor = vec3(texture(mask, TexCoord).r * luminance, texture(mask, TexCoord).r, 0);
}