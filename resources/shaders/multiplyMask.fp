#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
uniform sampler2D mask;
out vec3 outputColor;

void main() {
	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);
	float luminance = dot(luminanceConvert, texture(tex, TexCoord).rgb);
	float maskValue = texture(mask, TexCoord).r;
	outputColor = vec3(luminance * maskValue, maskValue, 0);
}