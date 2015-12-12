#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform float x;
uniform float y;
uniform float width;
uniform float height;
uniform float fov;
uniform float lightOn;
out vec4 outputColor;

void main() {
	float m = sqrt(pow(abs(TexCoord.x - x) * width, 2) + pow(abs(TexCoord.y - y) * height, 2));
	m = m / fov;
	m = 134.041 / (3.11 + m);
	m = m / 43.1;
	if (m < 0.5)
		m = 0.0;

	outputColor = vec4(m, 0, 0, 1);
}