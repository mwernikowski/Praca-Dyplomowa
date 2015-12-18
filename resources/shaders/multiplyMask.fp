#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D tex;
uniform float width;
uniform float height;
uniform float x;
uniform float y;
uniform float fov;
out vec3 outputColor;

void main() {

	vec3 luminanceConvert = vec3(0.212656, 0.715158, 0.072186);
	float luminance = dot(luminanceConvert, texture(tex, TexCoord).rgb);
	float m = sqrt(pow(abs(TexCoord.x - x) * width, 2) + pow(abs(TexCoord.y - y) * height, 2));
	m = m / fov;
	m = 134.041 / (3.11 + m);
	m = m / 43.1;
	if (m < 0.6)
		m = 0.0;
	outputColor = vec3(luminance * m, m, 0);
}