#include "stdafx.h"

EffectParameter* Effect::operator[](GLchar *name)
{
	return (*parameters)[name];
}

EffectParameter* Effect::GetParameter(GLchar *name)
{
	bool test = parameters->find(name) != parameters->end();
	if (test)
		return (*parameters)[name];

	return 0;
}

GLuint Effect::getProgramId()
{
	return ProgramId;
}

void EffectParameter::SetValue(RenderTarget2D rt)
{
	if (this == NULL)
	{
		//cout << "binding texture to inactive uniform\n";
		return;
	}
	glActiveTexture(GL_TEXTURE0 + textureID);
	rt.Bind();
	glUniform1i(paramID, textureID);
	//glPrintError(glGetError());
	int y = 1;
	//	glPrintError(glGetError());
}