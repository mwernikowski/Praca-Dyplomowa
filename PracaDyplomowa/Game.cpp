#include "stdafx.h"

void Game::setDeltaTime()
{
	static float oldTime = 0.0f;
	float time = (float)clock() / (float)CLOCKS_PER_SEC;
	deltaTime = time - oldTime;
	oldTime = time;
}

Game::Game(void)
{
	defaultLightPower = 250.0f;
	lightPower = defaultLightPower;
	playerSpeed = 50.0f;
	mouseSensitivity = 0.1f;
	specularStrength = 1.0f;
	setDeltaTime();
	first = true;
	lightOn = true;
	mousePosition = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

Game::~Game(void)
{
}

void Game::Init()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	theta = 1.0f;
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	quad = new Quad();

	Model *model;
	model = Content::LoadModel("../resources/Bedroom.obj");
	model->setScale(glm::vec3(0.8f, 0.8f, 0.8f));
	model->setPosition(glm::vec3(0.0f, -1.5f, 0.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/book.obj");
	model->setScale(glm::vec3(0.05f, 0.05f, 0.05f));
	model->setPosition(glm::vec3(-200.0f, 38.0f, 220.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/Digital Alarm Clock.obj");
	model->setScale(glm::vec3(0.3f, 0.3f, 0.3f));
	model->setPosition(glm::vec3(-30.0f, 21.0f, 45.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/Bild mir Rahmen.obj");
	model->setScale(glm::vec3(0.14f, 0.14f, 0.14f));
	model->setPosition(glm::vec3(0.0f, 100.0f, -252.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/carpet.obj");
	model->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	model->setPosition(glm::vec3(-1.0f, 11.0f, -13.5f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/poster.obj");
	model->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
	model->setPosition(glm::vec3(-15.0f, 9.0f, -15.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/shoebox.obj");
	model->setScale(glm::vec3(0.02f, 0.007f, 0.02f));
	model->setPosition(glm::vec3(-250.0f, 0.0f, -900.0f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/notebook.obj");
	model->setScale(glm::vec3(3.0f, 3.0f, 3.0f));
	model->setPosition(glm::vec3(-2.3f, 2.1f, 0.6f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/keyboard.obj");
	model->setScale(glm::vec3(10.0f, 10.0f, 10.0f));
	model->setPosition(glm::vec3(-0.7f, 0.64f, 0.4f));
	sceneModels.push_back(model);

	model = Content::LoadModel("../resources/lightbulb.obj");
	model->setScale(glm::vec3(1.8f, 1.8f, 1.8f));
	model->setPosition(glm::vec3(1.7f, 10.7f, -4.4f));
	lightSources.push_back(model);
	
	renderTarget1 = new RenderTarget2D();
	renderTarget2 = new RenderTarget2D();
	renderTarget3 = new RenderTarget2D();
	currentLuminance = new RenderTarget2D();

	objectsDrawer = new Effect("drawObjects");
	objectsDrawer->CreateShader();

	spriteDrawer = new Effect("drawSprite");
	spriteDrawer->CreateShader();

	tmo = new Effect("tmo");
	tmo->CreateShader();

	toneCompressor = new Effect("compressTones");
	toneCompressor->CreateShader();

	luminanceCalculator = new Effect("calculateLuminance");
	luminanceCalculator->CreateShader();

	shadowEffect = new Effect("shadow");
	shadowEffect->CreateShader();

	maskGenerator = new Effect("generateMask");
	maskGenerator->CreateShader();

	textureCopier = new Effect("copyTexture");
	textureCopier->CreateShader();
	
	maskMultiplier = new Effect("multiplyMask");
	maskMultiplier->CreateShader();

	camera = new Camera((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	camera->setPosition(glm::vec3(10, 13, 3));
	camera->setTarget(glm::vec3(0, 0, 0));

	light = new Camera((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	light->setPosition(glm::vec3(-5, 19, -6.7));
	light->setTarget(glm::vec3(-4.999, 0, -6.7));
	light->SetFOV(35.0f);

	LightPosition = glm::vec3(-5, 19, -6.7);
}

void Game::Update()
{
	glm::vec3 newPosition = camera->getPosition();
	glm::vec3 newTarget = camera->getTarget();
	bool changed = false;
	float horizontalAngle = camera->getHorizontalAngle();
	float verticalAngle = camera->getVerticalAngle();

	if (Keyboard::isPressed('W'))
	{
		newPosition.z -= deltaTime * playerSpeed * (float)cos(horizontalAngle * M_PI / 180.0);
		newPosition.x -= deltaTime * playerSpeed * (float)sin(horizontalAngle * M_PI / 180.0);
		changed = true;
	}
	if (Keyboard::isPressed('S'))
	{
		newPosition.z += deltaTime * playerSpeed * (float)cos(horizontalAngle * M_PI / 180.0);
		newPosition.x += deltaTime * playerSpeed * (float)sin(horizontalAngle * M_PI / 180.0);
		changed = true;
	}
	if (Keyboard::isPressed('A'))
	{
		newPosition.z -= deltaTime * playerSpeed * (float)cos((horizontalAngle + 90.0) * M_PI / 180.0);
		newPosition.x -= deltaTime * playerSpeed * (float)sin((horizontalAngle + 90.0) * M_PI / 180.0);
		changed = true;
	}
	if (Keyboard::isPressed('D'))
	{
		newPosition.z += deltaTime * playerSpeed * (float)cos((camera->getHorizontalAngle() + 90.0) * M_PI / 180.0);
		newPosition.x += deltaTime * playerSpeed * (float)sin((camera->getHorizontalAngle() + 90.0) * M_PI / 180.0);
		changed = true;
	}
	if (Keyboard::isPressed(GLFW_KEY_UP))
	{
		updateCameraAngles(0.0, deltaTime * playerSpeed);
		changed = true;
	}
	if (Keyboard::isPressed(GLFW_KEY_DOWN))
	{
		updateCameraAngles(0.0, -deltaTime * playerSpeed);
		changed = true;
	}
	if (Keyboard::isPressed(GLFW_KEY_LEFT))
	{
		updateCameraAngles(deltaTime * playerSpeed, 0.0);
		changed = true;
	}
	if (Keyboard::isPressed(GLFW_KEY_RIGHT))
	{
		updateCameraAngles(-deltaTime * playerSpeed, 0.0);
		changed = true;
	}

	if (Keyboard::isPressedAndReleased('F')) {
		lightOn = !lightOn;
	}


	if (changed == true)
	{
		camera->setPosition(newPosition);
		newTarget.z = newPosition.z - (float)cos(verticalAngle * M_PI / 180.0) * (float)cos(horizontalAngle * M_PI / 180.0);
		newTarget.y = newPosition.y + (float)sin(verticalAngle * M_PI / 180.0);
		newTarget.x = newPosition.x - (float)cos(verticalAngle * M_PI / 180.0) * (float)sin(horizontalAngle * M_PI / 180.0);
		camera->setTarget(newTarget);
	}

	if (Keyboard::isPressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
	}
}

void Game::Redraw()
{
	setDeltaTime();

	renderTarget1->SetRenderTarget();
	objectsDrawer->Apply();
	drawSceneObjects(objectsDrawer);

	renderTarget2->SetRenderTarget();
	maskGenerator->Apply();
	maskGenerator->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	maskGenerator->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	maskGenerator->GetParameter("width")->SetValue((float)WINDOW_WIDTH);
	maskGenerator->GetParameter("height")->SetValue((float)WINDOW_HEIGHT);
	maskGenerator->GetParameter("fov")->SetValue(78.0f);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, maskGenerator->GetParameter("World"));

	renderTarget3->SetRenderTarget();
	maskMultiplier->Apply();
	maskMultiplier->GetParameter("tex")->SetValue(*renderTarget1);
	maskMultiplier->GetParameter("mask")->SetValue(*renderTarget2);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, maskMultiplier->GetParameter("World"));
	renderTarget3->createMipmaps();

	renderTarget2->SetRenderTarget();
	luminanceCalculator->Apply();
	if (first) 
	{
		first = false;
		luminanceCalculator->GetParameter("oldTexture")->SetValue(*renderTarget3);
	}
	else 
	{
		luminanceCalculator->GetParameter("oldTexture")->SetValue(*currentLuminance);
	}
	
	luminanceCalculator->GetParameter("aimTexture")->SetValue(*renderTarget3);
	luminanceCalculator->GetParameter("deltaTime")->SetValue(deltaTime);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, luminanceCalculator->GetParameter("World"));

	currentLuminance->SetRenderTarget();
	textureCopier->Apply();
	textureCopier->GetParameter("tex")->SetValue(*renderTarget2);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, textureCopier->GetParameter("World"));
	currentLuminance->createMipmaps();

	renderTarget1->SetRenderTarget(WINDOW_WIDTH, WINDOW_HEIGHT);
	toneCompressor->Apply();
	toneCompressor->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	toneCompressor->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	toneCompressor->GetParameter("luminance")->SetValue(*currentLuminance);
	drawSceneObjects(toneCompressor);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spriteDrawer->Apply();
	spriteDrawer->GetParameter("tex")->SetValue(*renderTarget1);
	spriteDrawer->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	spriteDrawer->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, spriteDrawer->GetParameter("World"));
}

void Game::mouseMotion(double x, double y)
{
	mousePosition = glm::vec2(x, y);
	/*float angleHorizontal = camera->getHorizontalAngle();
	float angleVertical = camera->getVerticalAngle();

	angleHorizontal += (float)(WINDOW_WIDTH / 2 - x) * mouseSensitivity;
	angleVertical += (float)(WINDOW_HEIGHT / 2 - y) * mouseSensitivity;

	if (angleHorizontal > 360.0f)
		angleHorizontal -= 360.0f;
	else if (angleHorizontal < 0.0f)
		angleHorizontal += 360.0f;

	if (angleVertical > 88.0f)
		angleVertical = 88.0f;
	else if (angleVertical < -88.0f)
		angleVertical = -88.0f;

	camera->setHorizontalAngle(angleHorizontal);
	camera->setVerticalAngle(angleVertical);

	glm::vec3 newTarget = camera->getTarget();
	glm::vec3 position = camera->getPosition();

	newTarget.z = position.z - (float)cos(angleVertical * M_PI / 180.0) * (float)cos(angleHorizontal * M_PI / 180.0);
	newTarget.y = position.y + (float)sin(angleVertical * M_PI / 180.0);
	newTarget.x = position.x - (float)cos(angleVertical * M_PI / 180.0) * (float)sin(angleHorizontal * M_PI / 180.0);
	camera->setTarget(newTarget);
	*/
}

void Game::updateCameraAngles(float angleHorizontalDelta, float angleVerticalDelta)
{
	float angleHorizontal = camera->getHorizontalAngle() + angleHorizontalDelta;
	float angleVertical = camera->getVerticalAngle() + angleVerticalDelta;

	if (angleHorizontal > 360.0f)
		angleHorizontal -= 360.0f;
	else if (angleHorizontal < 0.0f)
		angleHorizontal += 360.0f;

	if (angleVertical > 88.0f)
		angleVertical = 88.0f;
	else if (angleVertical < -88.0f)
		angleVertical = -88.0f;

	camera->setHorizontalAngle(angleHorizontal);
	camera->setVerticalAngle(angleVertical);

	glm::vec3 newTarget = camera->getTarget();
	glm::vec3 position = camera->getPosition();

	newTarget.z = position.z - (float)cos(angleVertical * M_PI / 180.0) * (float)cos(angleHorizontal * M_PI / 180.0);
	newTarget.y = position.y + (float)sin(angleVertical * M_PI / 180.0);
	newTarget.x = position.x - (float)cos(angleVertical * M_PI / 180.0) * (float)sin(angleHorizontal * M_PI / 180.0);
	camera->setTarget(newTarget);
}

void Game::drawSceneObjects(Effect *g)
{
	g->GetParameter("View")->SetValue(camera->getView());
	g->GetParameter("Projection")->SetValue(camera->getProjection());
	g->GetParameter("LightPosition")->SetValue(light->getPosition());
	g->GetParameter("EyePosition")->SetValue(camera->getPosition());
	g->GetParameter("lightOn")->SetValue(lightOn ? 1.0f : 0.0f);
	for (int i = 0; i < (int)sceneModels.size(); i++)
	{
		Model* model = sceneModels[i];
		for (int j = 0; j < model->Elements(); j++)
		{
			g->GetParameter("matColor")->SetValue(model->GetMesh(j)->GetMaterial().Color);

			if (model->GetMesh(j)->GetMaterial().texture != NULL)
			{
				g->GetParameter("mode")->SetValue(1.0f);
				g->GetParameter("tex")->SetValue(*model->GetMesh(j)->GetMaterial().texture);
			}
			else
			{
				g->GetParameter("mode")->SetValue(-1.0f);
			}

			g->GetParameter("World")->SetValue(
				model->GetMesh(j)->getLocalWorld() *
				glm::scale(glm::mat4(1.0f), model->getScale()) *
				glm::rotate(glm::mat4(1.0f), theta, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::translate(glm::mat4(1.0f), model->getPosition()));

			model->GetMesh(j)->Draw();
		}
	}

	for (int i = 0; i < (int)lightSources.size(); i++)
	{
		Model* model = lightSources[i];
		for (int j = 0; j < model->Elements(); j++)
		{
			g->GetParameter("matColor")->SetValue(glm::vec3(1.0f, 1.0f, 1.0f));
			g->GetParameter("mode")->SetValue(10.0f);

			g->GetParameter("World")->SetValue(
				model->GetMesh(j)->getLocalWorld() *
				glm::scale(glm::mat4(1.0f), model->getScale()) *
				glm::rotate(glm::mat4(1.0f), theta, glm::vec3(0.0f, 1.0f, 0.0f)) *
				glm::translate(glm::mat4(1.0f), model->getPosition()));

			model->GetMesh(j)->Draw();
		}
	}
}
