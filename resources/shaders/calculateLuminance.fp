#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D oldTexture;
uniform sampler2D aimTexture;
uniform float deltaTime;
uniform float speed;
out vec4 outputColor;

void main()
{

	float oldLuminance = texture(oldTexture, TexCoord, 20).r / texture(oldTexture, TexCoord, 20).g;
	float aimLuminance = texture(aimTexture, TexCoord, 20).r / texture(aimTexture, TexCoord, 20).g;

	float tauRod = speed;
	float tauCone = 2.0f;

	float newLuminance = 0.0f;

	if (oldLuminance < aimLuminance) {
		newLuminance = min(oldLuminance + deltaTime / tauCone, aimLuminance);
	} else {
		newLuminance = max(oldLuminance - deltaTime / tauRod, aimLuminance);
	}

	outputColor = vec4(newLuminance, 1, 0, 1);
}