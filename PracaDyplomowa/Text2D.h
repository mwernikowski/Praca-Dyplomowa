#pragma once
class Text2D
{
private:
	GLuint texture, sampler;
	GLuint vbo, vao;
	GLuint vs, fs, program;
	FT_Library library;
	FT_Face face;
	Effect* shader;

	GLuint texUniform;
	GLuint colorUniform;
	void drawText(const string &text, float x, float y, float sx, float sy);
	int getPolishSymbol(int character);

public:
	Text2D(string fontFile, string shaderName);
	~Text2D();
	void renderText(const string &text, int x, int y, int size);
};

