#pragma once
class Texture2D
{
private:
	int width;
	int height;
	GLuint textureID;
public:
	Texture2D(void);
	Texture2D(int Width, int Height, GLuint TextureID);
	int GetWidth();
	int GetHeight();
	void Bind();
	~Texture2D(void);
};

