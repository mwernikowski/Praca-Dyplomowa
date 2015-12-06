#pragma once
class Text2D
{
private:
	Texture2D* fontTexture;
	unsigned int vertexBuffer;
	unsigned int uvBuffer;
	unsigned int shader;
	unsigned int uniformId;
public:
	Text2D();
	~Text2D();
	void initText2D(const char* texturePath);
};

