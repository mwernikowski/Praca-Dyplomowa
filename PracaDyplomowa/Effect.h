#pragma once
class Effect
{
private:
	GLuint VertexShaderId;
	GLuint FragmentShaderId;
	GLuint GeomShaderId;
	GLuint ProgramId;
	GLuint WorldMatrix;
	GLuint ViewMatrix;
	GLuint NormalMatrix;
	GLuint LightPos;
	GLuint EyePos;
	GLuint ProjectionMatrix;
	char *PixelShader;
	char *VertexShader;
	char *GeomShader;
	const GLchar *PShader;
	const GLchar *VShader;
	const GLchar *GShader;
	map<string, EffectParameter*> *parameters;
	char *textFileRead(char *fn);
public:
	Effect(string ShaderName);
	~Effect(void);
	void CreateShader();
	void CreateShaderInfo();
	void destroyShader();
	void Apply();
	//void AddParameter(aiMatrix4x4 param);
	//void AddWorld(glm::mat4x4 param);
	//void AddView(glm::mat4x4 param);
	//void AddProjection(glm::mat4x4 param);
	//void AddWorldNormal(glm::mat4x4 param);
	//void AddLightPos(glm::vec3 param);
	//void AddEye(glm::vec3 param);
	void glPrintError(GLenum err);
	EffectParameter* operator[](GLchar *name);
	EffectParameter* GetParameter(GLchar *name);
};

