#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform float x;
uniform float y;
uniform float width;
uniform float height;
uniform float fov;
out vec3 outputColor;

void main() {
	float m = sqrt(pow((TexCoord.x - x) * width, 2) + pow((TexCoord.y - y) * height, 2));
	m = m / fov;
	m = 134.041 / (3.11 + m);
	m = m / 43.1;

	outputColor = vec3(m, 0, 0);
}