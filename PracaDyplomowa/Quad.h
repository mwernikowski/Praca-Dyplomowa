#pragma once
__declspec(align(16)) class Quad
{
private:
	GLuint VaoId;
	GLuint VertexVAOID[1];
	GLuint VertexVBOID[3];
	GLuint IndexVBOID[2];
	GLuint ColorBufferId;
	GLfloat *Vertices;
	GLfloat *Colors;
	GLfloat *texCoords;
	glm::vec4 quadRect;
public:
	Quad(void);
	void Draw(void);
	void Draw(int, int, int, int, EffectParameter *world);
	~Quad(void);
	GLuint getVaoId() { return VertexVAOID[0]; }

	void* operator new(size_t i)
	{
		return _mm_malloc(i,16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

