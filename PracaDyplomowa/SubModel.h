#pragma once
struct Material
{
	Texture2D* texture;
	glm::vec3 Color;
	float specularIntensity;
	float specularPower;
};

__declspec(align(16)) class SubModel
{
private:
	Material material;
	glm::mat4x4 LocalWorld;
	GLuint VaoId;
	GLuint VertexVAOID;
	GLuint indexBuffer;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint texCoordBuffer;
	GLuint normalBuffer;
	GLuint ColorBufferId;
	glm::mat4x4 assimMat2Mymat(aiMatrix4x4 m);
	int indIter;
public:
	SubModel(aiMesh &mesh);
	void SetMaterial(Material m);
	Material &GetMaterial();
	void setLocalWorld(glm::mat4x4 &world);
	glm::mat4x4 getLocalWorld();
	~SubModel(void);
	void Draw();

	void* operator new(size_t i)
	{
		return _mm_malloc(i,16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

