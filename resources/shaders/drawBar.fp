#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform float x;
uniform float y;
uniform float boxPosition;
out vec3 outputColor;

void main()
{
	float l = length(TexCoord - vec2(x, y));

	float normalBoxPosition = (boxPosition + 1.0f) * 0.5f * 0.9f + 0.05f;

	if (TexCoord.y < 0.31f && TexCoord.y > 0.29f && TexCoord.x < 0.95f && TexCoord.x > 0.05f)
		outputColor = vec3(0.0f, 0.0f, 0.0f);
	else if (TexCoord.y < 0.35f && TexCoord.y > 0.25f) {
		if (abs(TexCoord.x - 0.05f) < 0.001f)
			outputColor = vec3(0.0f, 0.0f, 0.0f);
		else if (abs(TexCoord.x - 0.275f) < 0.001f)
			outputColor = vec3(0.0f, 0.0f, 0.0f);
		else if (abs(TexCoord.x - 0.50f) < 0.001f)
			outputColor = vec3(0.0f, 0.0f, 0.0f);
		else if (abs(TexCoord.x - 0.725f) < 0.001f)
			outputColor = vec3(0.0f, 0.0f, 0.0f);
		else if (abs(TexCoord.x - 0.95f) < 0.001f)
			outputColor = vec3(0.0f, 0.0f, 0.0f);
		else
			outputColor = vec3(0.5f, 0.5f, 0.5f);
	}
	else
		outputColor = vec3(0.5f, 0.5f, 0.5f);
	
	if (TexCoord.y < 0.4f && TexCoord.y > 0.2f && abs(TexCoord.x - normalBoxPosition) < 0.01f)
		outputColor = vec3(0.0f, 0.0f, 1.0f);
		
	if (l < 0.003f)
		outputColor = vec3(1.0f, 1.0f, 1.0f);
	else if (l < 0.005f)
		outputColor = vec3(0.0f, 1.0f, 0.0f);	
}