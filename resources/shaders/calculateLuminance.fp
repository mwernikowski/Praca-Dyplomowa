#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D oldTexture;
uniform sampler2D aimTexture;
uniform float deltaTime;
out vec3 outputColor;

void main()
{
	float delta = 1e-5;
	float oldLuminance = texture(oldTexture, TexCoord, 20).r / (texture(oldTexture, TexCoord, 20).g + delta);
	float aimLuminance = texture(aimTexture, TexCoord, 20).r / (texture(aimTexture, TexCoord, 20).g + delta);

	float logE10 = 2.302585;

	float logOldLuminance = log(oldLuminance) / logE10;
	float logAimLuminance = log(aimLuminance) / logE10;

	float tauRod = 0.4;
	float tauCone = 0.1;

	float sigma = 0.04 / (0.04 + oldLuminance);
	
	float tau = sigma * tauRod + (1 - sigma) * tauCone;

	float newLuminance = oldLuminance + (aimLuminance - oldLuminance) * (1 - exp(-(deltaTime/tau)));

	//float newLuminance = pow(logNewLuminance, 10.0f);

	outputColor = vec3(newLuminance, 1, 1);
}