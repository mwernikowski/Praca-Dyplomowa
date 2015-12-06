#pragma once
class RenderTarget2D
{
private:
	GLuint frameBufferID;
	GLuint renderTargetTextureID;
	GLuint depthBufferID;
	GLenum textureComponents;
	GLenum textureFormat;
	GLenum textureType;
	GLenum depthFormat;
	int width;
	int height;
public:
	RenderTarget2D(void);
	RenderTarget2D(int Width, int Height, GLenum SurfaceComponents, GLenum SurfaceFormat, GLenum SurfaceType, GLenum DepthFormat);
	void depthBuffer(int width, int height);
	static void BindMRT(int num, RenderTarget2D rTargets[]);
	GLuint GetFrameBufferID();
	GLuint GetRenderTargetTextureID();
	GLuint GetDepthBufferID();
	void SetRenderTarget();
	void SetRenderTarget(int width, int height);
	void copyToRenderTarget(RenderTarget2D* renderTarget, int width, int height, int level);
	void resize(int width, int height);
	void createMipmaps();
	void Bind();
	int getWidth();
	int getHeight();
	~RenderTarget2D(void);
};

