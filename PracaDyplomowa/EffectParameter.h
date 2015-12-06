#pragma once
class EffectParameter
{
private:
	GLuint paramID;
	GLenum type;
	GLuint textureID;

public:
	
	EffectParameter(){}
	
	EffectParameter(GLuint ProgramId, GLchar name[], GLenum u_type) : type(u_type)
	{
		if(this == NULL) { return; }
		paramID = glGetUniformLocation(ProgramId, name);
		textureID = -1;
	}
	
	EffectParameter(GLuint ProgramId, GLchar name[], GLenum u_type, GLuint u_textureID) : type(u_type), textureID(u_textureID)
	{
		if(this == NULL) { return; }
		paramID = glGetUniformLocation(ProgramId, name);
	}
	
	void SetValue(glm::mat4x4 &value)
	{
		if(this == NULL) { return; }
		glUniformMatrix4fv(paramID, 1, GL_FALSE, glm::value_ptr(value));
	}
	
	void SetValue(float value)
	{
		if(this == NULL) { return; }
		glUniform1f(paramID, value);
	}
	
	void SetValue(int value)
	{
		if(this == NULL) { return; }
		glUniform1i(paramID, value);
	}
	
	void SetValue(glm::vec2 value)
	{
		if(this == NULL) { return; }
		glUniform2fv(paramID, 1, glm::value_ptr(value));
	}
	
	void SetValue(glm::vec3 value)
	{
		if(this == NULL) { return; }
		glUniform3fv(paramID, 1, glm::value_ptr(value));
	}
	
	void SetValue(glm::vec4 &value)
	{
		if(this == NULL) { return; }
		glUniform4fv(paramID, 1, glm::value_ptr(value));
	}
	
	void SetValue(Texture2D tex)
	{
		if (this == NULL) { return; }
		glActiveTexture(GL_TEXTURE0 + textureID);
		tex.Bind();
		glUniform1i(paramID, textureID);
	}
	
	void SetValue(RenderTarget2D rt);

	//void SetValue(RenderTarget2D *tar);
	//void SetDepthAsValue(RenderTarget2D *tar);
};

