#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D oldTexture;
uniform sampler2D aimTexture;
uniform float deltaTime;
uniform float speed;
out vec3 outputColor;

void main()
{

	float oldLuminance = texture(oldTexture, TexCoord, 20).r / texture(oldTexture, TexCoord, 20).g;
	float aimLuminance = texture(aimTexture, TexCoord, 20).r / texture(aimTexture, TexCoord, 20).g;

	float tauRod = 1.6;
	float tauCone = 1.6;

	float sigma = 0.04 / (0.04 + oldLuminance);
	
	float tau = sigma * tauRod + (1 - sigma) * tauCone;

	float newLuminance = oldLuminance;// + (aimLuminance - oldLuminance) * speed;//(1 - exp(-(deltaTime/tau)));

	float changeSign = 0.5f;
	
	if (oldLuminance > aimLuminance)
		changeSign = -tauRod;
	else if (oldLuminance < aimLuminance)
		changeSign = tauCone;

	//newLuminance = oldLuminance + (deltaTime / changeSign);


	if (oldLuminance != aimLuminance)
		newLuminance = oldLuminance + (deltaTime / changeSign);
	else
		newLuminance = aimLuminance;
	
	/*
	if (oldLuminance > aimLuminance)
		if (oldLuminance < aimLuminance)
			newLuminance = aimLuminance;
	else if (oldLuminance < aimLuminance)
		if (newLuminance > aimLuminance)
			newLuminance = aimLuminance;
	else
		newLuminance = aimLuminance;
	*/
	//newLuminance = pow(10.0f, logNewLuminance);
	//newLuminance = aimLuminance;
	outputColor = vec3(newLuminance, 1, 0);
}