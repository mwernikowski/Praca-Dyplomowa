#version 400
in vec2 TexCoord;
in vec4 xPosition;

uniform sampler2D previous;
uniform sampler2D average;
uniform float deltaTime;
uniform float first;
out vec3 outputColor;

void main()
{
	float delta = 0.00001;
	float loge10Inv = 0.434294;

	float logAverageLuminance = exp(textureLod(average, TexCoord, 20).x);
	float previousLuminance = textureLod(previous, TexCoord, 20).x;
	float logPreviousLuminance = log(previousLuminance + delta) * loge10Inv;
	
	float rodsTime = 0.4;
	float conesTime = 0.1;

	float rodsSensitivity = 0.04 / (0.04 + previousLuminance);
	
	float adaptationSpeed = rodsSensitivity * rodsTime + (1 - rodsSensitivity) * conesTime;
	
	if (first > 1.0f)
		logPreviousLuminance = 0.0f;
	
	float logNewLuminance = logPreviousLuminance + (logAverageLuminance - logPreviousLuminance) * (1 - exp(-deltaTime / adaptationSpeed));
	float newLuminance = pow(10, logNewLuminance);

	float a = (0.949 - newLuminance) / 6.806;
	float s = 1.002 * exp(a*a);

	float toneCompressedLuminance = newLuminance / (newLuminance + s);
	
	outputColor = vec3(toneCompressedLuminance, 0, 0);
}