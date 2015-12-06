#pragma once

class Content
{
public:
	Content(void);
	~Content(void);
	static Texture2D *LoadTexture(const char *filePath);
	static Model *LoadModel(const char *filePath);
};

