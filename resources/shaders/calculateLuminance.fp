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
	float tauCone = 0.2f;

	float newLuminance = 0.0f;

	float changeSign = 0.5f;
	
	if (oldLuminance > aimLuminance) {
		changeSign = -tauRod;
	}
	else if (oldLuminance < aimLuminance) {
		changeSign = tauCone;
	}

	/*if (abs(change) < 0.000001f)
		newLuminance = oldLuminance;
	else if (abs(change) < abs(aimLuminance - oldLuminance))
		newLuminance = aimLuminance;
	else*/

	/*if (abs(change) < 0.006f)
		newLuminance = oldLuminance;
	else
		newLuminance = oldLuminance + change;
		*/
	//newLuminance = oldLuminance + (aimLuminance - oldLuminance) * deltaTime / changeSign;

	
	if (abs(oldLuminance - aimLuminance) < 0.0005f)
		newLuminance = aimLuminance;
	else {

	if (oldLuminance != aimLuminance)
		newLuminance = oldLuminance + (deltaTime / changeSign);
	else
		newLuminance = aimLuminance;
	}
	/*if (oldLuminance > aimLuminance)
		if (oldLuminance < aimLuminance)
			newLuminance = aimLuminance;
	else if (oldLuminance < aimLuminance)
		if (newLuminance > aimLuminance)
			newLuminance = aimLuminance;
	else
		newLuminance = aimLuminance;
		}*/

	outputColor = vec4(newLuminance, 1, 0, 1);
}