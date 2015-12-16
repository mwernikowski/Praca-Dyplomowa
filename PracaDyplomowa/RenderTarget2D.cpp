#include "stdafx.h"

RenderTarget2D::RenderTarget2D(void) : RenderTarget2D(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA32F, GL_RGBA, GL_UNSIGNED_BYTE, GL_DEPTH24_STENCIL8)
{
}

RenderTarget2D::RenderTarget2D(int Width, int Height, GLenum InternalFotrmat, GLenum SurfaceFormat, GLenum SurfaceType, GLenum DepthFormat) :
	width(Width), height(Height), textureComponents(InternalFotrmat), textureFormat(SurfaceFormat), textureType(SurfaceType), depthFormat(DepthFormat)
{

	cout << "NEW MRT" << endl;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	glGenTextures(1, &renderTargetTextureID);
	glBindTexture(GL_TEXTURE_2D, renderTargetTextureID);
	//glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, InternalFotrmat, Width, Height, 0, SurfaceFormat, GL_FLOAT, 0);
	
	//	glPrintError(glGetError());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenRenderbuffers(1, &depthBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTargetTextureID, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	//glDrawBuffers(1, DrawBuffers);
}

void RenderTarget2D::depthBuffer(int width, int height)
{
	this->width = width;
	this->height = height;
	cout << "NEW MRT" << endl;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);

	glGenTextures(1, &renderTargetTextureID);
	glBindTexture(GL_TEXTURE_2D, renderTargetTextureID);
	//glEnable(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	//	glPrintError(glGetError());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenRenderbuffers(1, &depthBufferID);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, renderTargetTextureID, 0);
	glDrawBuffer(GL_NONE);
}

void RenderTarget2D::BindMRT(int num, RenderTarget2D rTargets[])
{
	if (num <= 0)
		return;
	RenderTarget2D rtcheck;
	glBindFramebuffer(GL_FRAMEBUFFER, rTargets[0].frameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rTargets[0].depthBufferID);

	GLenum *DrawBuffers = new GLenum[num];
	for (int i = 0; i < num; i++)
	{
		rtcheck = rTargets[i];
		DrawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, rTargets[i].renderTargetTextureID, 0);
	}
	glDrawBuffers(num, DrawBuffers);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

}

GLuint RenderTarget2D::GetFrameBufferID(void)
{
	return frameBufferID;
}

GLuint RenderTarget2D::GetRenderTargetTextureID(void)
{
	return renderTargetTextureID;
}

GLuint RenderTarget2D::GetDepthBufferID(void)
{
	return depthBufferID;
}

void RenderTarget2D::Bind(void)
{
	glBindTexture(GL_TEXTURE_2D, this->renderTargetTextureID);
}

void RenderTarget2D::SetRenderTarget(void)
{
	SetRenderTarget(this->width, this->height);
}

void RenderTarget2D::SetRenderTarget(int width, int height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferID);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderTargetTextureID, 0);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderTarget2D::copyToRenderTarget(RenderTarget2D * renderTarget, int width, int height, int level)
{
	renderTarget->Bind();
	glCopyTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, 0, 0, width, height, 0);
}

void RenderTarget2D::resize(int width, int height)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_DOUBLE, 0);
}

void RenderTarget2D::createMipmaps()
{
	glBindTexture(GL_TEXTURE_2D, renderTargetTextureID);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int RenderTarget2D::getWidth()
{
	return width;
}

int RenderTarget2D::getHeight()
{
	return height;
}

RenderTarget2D::~RenderTarget2D(void)
{
}
