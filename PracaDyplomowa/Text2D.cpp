#include "stdafx.h"

Text2D::Text2D()
{
}


Text2D::~Text2D()
{
}

void Text2D::initText2D(const char * texturePath)
{
	fontTexture = Content::LoadTexture(texturePath);
}