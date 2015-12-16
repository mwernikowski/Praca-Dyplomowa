#include "stdafx.h"

void Text2D::drawText(const string & text, float x, float y, float sx, float sy)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	const FT_GlyphSlot glyph = face->glyph;

	for (int c : text) {
		c = getPolishSymbol(c);
		if (FT_Load_Char(face, c, FT_LOAD_RENDER) != 0)
			continue;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_R8,
			glyph->bitmap.width, glyph->bitmap.rows,
			0, GL_RED, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

		const float vx = x + glyph->bitmap_left * sx;
		const float vy = y + glyph->bitmap_top * sy;
		const float w = glyph->bitmap.width * sx;
		const float h = glyph->bitmap.rows * sy;

		struct {
			float x, y, s, t;
		} data[6] = {
			{ vx    , vy    , 0, 0 },
			{ vx    , vy - h, 0, 1 },
			{ vx + w, vy    , 1, 0 },
			{ vx + w, vy    , 1, 0 },
			{ vx    , vy - h, 0, 1 },
			{ vx + w, vy - h, 1, 1 }
		};

		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), data, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		x += (glyph->advance.x >> 6) * sx;
		y += (glyph->advance.y >> 6) * sy;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
}

int Text2D::getPolishSymbol(int character)
{
	switch (character)
	{
		case 165: return 260; break;
		case 198: return  262; break;
		case 202: return  280; break;
		case 163: return  321; break;
		case 209: return  323; break;
		case 211: return  211; break;
		case 140: return  346; break;
		case 143: return  377; break;
		case 175: return  379; break;
		case 185: return  261; break;
		case 230: return  263; break;
		case 234: return  281; break;
		case 179: return  322; break;
		case 241: return  324; break;
		case 243: return  243; break;
		case 156: return  347; break;
		case 159: return  378; break;
		case 191: return  380; break;
		default: return character;
	}
}

Text2D::Text2D(string fontFile, string shaderName)
{
	if (FT_Init_FreeType(&library) != 0) {
		cerr << "Couldn't initialize FreeType library\n";
		return;
	}

	if (FT_New_Face(library, fontFile.c_str(), 0, &face) != 0) {
		cerr << "Unable to load myfont.ttf\n";
		return;
	}

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenTextures(1, &texture);
	glGenSamplers(1, &sampler);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	shader = new Effect(shaderName);
	shader->CreateSimpleShader();

	program = shader->getProgramId();

	glUseProgram(program);
	glBindAttribLocation(program, 0, "in_Position");
	GLuint texUniform = glGetUniformLocation(program, "tex");
	GLuint colorUniform = glGetUniformLocation(program, "color");
}


Text2D::~Text2D()
{
}

void Text2D::renderText(const string & text, int x, int y, int size)
{
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindSampler(0, sampler);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glUseProgram(program);
	glUniform4f(colorUniform, 1, 1, 1, 1);
	glUniform1i(texUniform, 0);

	float normalX = 2.0f * x / WINDOW_WIDTH - 1.0f;
	float normalY = -2.0f * y / WINDOW_HEIGHT + 1.0f;

	FT_Set_Pixel_Sizes(face, 0, size);
	drawText(text, normalX, normalY, 2.0 / WINDOW_WIDTH, 2.0 / WINDOW_HEIGHT);
	glBindSampler(0, 0);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}