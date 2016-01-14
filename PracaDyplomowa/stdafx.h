#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <ctime>
#include <cmath>

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstddef>
#include <cctype>

#include <string>
#include <fstream>
#include <sstream>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "FreeImage.h"
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "GL\glew.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "GLFW\glfw3.h"

using namespace std;

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const bool FULLSCREEN = false;

enum GAME_MODE { FIRST_INTRODUCTION, FIRST_PRESENTATION, SECOND_INTRODUCTION, SECOND_PRESENTATION, SUMMARY };

extern GLFWwindow* window;

#include "Keyboard.h"
#include "Texture2D.h"
#include "RenderTarget2D.h"
#include "EffectParameter.h"
#include "Quad.h"
#include "SubModel.h"
#include "Model.h"
#include "Effect.h"
#include "Camera.h"
#include "Content.h"
#include "Text2D.h"
#include "AnimationStep.h"
#include "Game.h"
