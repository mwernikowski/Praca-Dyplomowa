#include "stdafx.h"

Game game;
FT_Library freeType;

void mouseMotionFunc(GLFWwindow* window, double x, double y)
{
	game.mouseMotion(x, y);	
	//glfwSetCursorPos(window, WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0);
}

void mouseButtonFunc(GLFWwindow* window, int button, int action, int mods)
{
	game.mouseClick(button, action);
}

int main()
{
	if (!glfwInit()) {
		return -1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window;
	if (FULLSCREEN)
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Praca dyplomowa", glfwGetPrimaryMonitor(), NULL);
	else
		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Praca dyplomowa", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// sprawdzenie czy nie wystapil blad
	GLenum err = glGetError();
	if (err) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(err));
		exit(EXIT_FAILURE);
	}

	if (FT_Init_FreeType(&freeType)) {
		fprintf(stderr, "ERROR: could not initialize freetype library\n");
		exit(EXIT_FAILURE);
	}

	// inicjalizacja GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult;
	GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}

	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	// glowna petla gry
	game.Init();
	glfwSetCursorPosCallback(window, mouseMotionFunc);
	glfwSetMouseButtonCallback(window, mouseButtonFunc);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	Keyboard::KeyboardInit();
	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		// rendering
		game.Update();
		game.Redraw();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}

