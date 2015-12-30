#include "stdafx.h"

void Game::setDeltaTime()
{
	static float oldTime = 0.0f;
	float time = (float)clock() / (float)CLOCKS_PER_SEC;
	deltaTime = time - oldTime;
	oldTime = time;
}

Game::Game(string input, int sessions)
{
	this->input = input;
	this->sessionsLeft = sessions;
	defaultLightPower = 250.0f;
	lightPower = defaultLightPower;
	playerSpeed = 50.0f;
	adaptationSpeed = 0.1f;
	mouseSensitivity = 0.1f;
	specularStrength = 1.0f;
	setDeltaTime();
	gameMode = FIRST_INTRODUCTION;
	first = true;
	lightOn = true;
	mousePosition = glm::vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	input = "";
	clickCounter = 0;
	elapsedTime = 0.0f;
	boxPosition = -1.0f;
	movingBar = false;
	speeds[0] = 2.0f;
	speeds[1] = 4.0f;
	speeds[2] = 8.0f;
	speeds[3] = 16.0f;
	speeds[4] = 32.0f;

	repetition = 1;

	firstSpeed = rand() % 5;
	secondSpeed = rand() % 4;
	if (secondSpeed >= firstSpeed)
		++secondSpeed;
}

Game::~Game(void)
{
}

void Game::Init()
{
	theta = 1.0f;
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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
	
	sceneRT = new RenderTarget2D();
	maskRT = new RenderTarget2D();
	luminanceMap = new RenderTarget2D();
	currentLuminance = new RenderTarget2D();
	adaptedRT = new RenderTarget2D();
	changedLuminance = new RenderTarget2D();

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

	textureCopier = new Effect("copyTexture");
	textureCopier->CreateShader();
	
	maskMultiplier = new Effect("multiplyMask");
	maskMultiplier->CreateShader();

	barDrawer = new Effect("drawBar");
	barDrawer->CreateShader();

	camera = new Camera((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	camera->setPosition(glm::vec3(10, 13, 3));
	camera->setTarget(glm::vec3(0, 0, 0));

	light = new Camera((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT);
	light->setPosition(glm::vec3(-5, 19, -6.7));
	light->setTarget(glm::vec3(-4.999, 0, -6.7));
	light->SetFOV(35.0f);

	LightPosition = glm::vec3(-5, 19, -6.7);

	text = new Text2D("../resources/OpenSans.ttf", "renderText");

}

void Game::Update()
{
	if (gameMode == FIRST_PRESENTATION || gameMode == SECOND_PRESENTATION)
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


		if (changed == true)
		{
			camera->setPosition(newPosition);
			newTarget.z = newPosition.z - (float)cos(verticalAngle * M_PI / 180.0) * (float)cos(horizontalAngle * M_PI / 180.0);
			newTarget.y = newPosition.y + (float)sin(verticalAngle * M_PI / 180.0);
			newTarget.x = newPosition.x - (float)cos(verticalAngle * M_PI / 180.0) * (float)sin(horizontalAngle * M_PI / 180.0);
			camera->setTarget(newTarget);
		}
	}

	else if (gameMode == FIRST_INTRODUCTION)
	{
		if (Keyboard::isPressed(GLFW_KEY_ENTER)) {
			lightOn = true;
			gameMode = FIRST_PRESENTATION;
		}
	}

	else if (gameMode == SECOND_INTRODUCTION) {
		if (Keyboard::isPressed(GLFW_KEY_ENTER)) {
			lightOn = true;
			gameMode = SECOND_PRESENTATION;
		}
	}

	else if (gameMode == SUMMARY) {
		if (Keyboard::isPressed(GLFW_KEY_SPACE)) {

			fstream results;
			results.open("results.csv", ios::app);
			results << input << "," << repetition << ",to_dark,room" <<
				"," << speeds[firstSpeed] << "," << speeds[secondSpeed] << "," << boxPosition << endl;
			results.close();
			sessionsLeft--;

			repetition++;
			firstSpeed = rand() % 5;
			secondSpeed = rand() % 4;
			if (secondSpeed >= firstSpeed)
				++secondSpeed;
			gameMode = FIRST_INTRODUCTION;
			if (sessionsLeft == 0)
				glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
		}
	}

	if (Keyboard::isPressed(GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
	}

}

void Game::Redraw()
{
	setDeltaTime();
	switch (gameMode) {
	case FIRST_INTRODUCTION:
		drawLogin();
		break;
	case SECOND_INTRODUCTION:
		drawSecondIntroduction();
		break;
	case FIRST_PRESENTATION:
		drawScene();
		break;
	case SECOND_PRESENTATION:
		drawScene();
		break;
	case SUMMARY:
		drawSummary();
		break;
	}
}

void Game::drawLogin()
{
	glClear(GL_COLOR_BUFFER_BIT);
	text->renderText("Za chwile na ekranie wyswietli sie scena w oswietlonym pokoju. ", 10, 100, 30);
	text->renderText("Ruch ludzkiego oka bedzie symulowany za pomoca ruchu myszki. ", 10, 150, 30);
	text->renderText("Po nacisnieciu lewego przycisku myszy zgasnie swiatlo i rozpocznie sie proces", 10, 200, 30);
	text->renderText("adaptacji do ciemnosci.", 10, 230, 30);
	text->renderText("Symulacja zakonczy sie 10 sekund po drugim nacisnieciu przycisku.", 10, 280, 30);
	text->renderText("Nacisnij ENTER, aby kontynuowac", 100, 500, 50);
}

void Game::drawSecondIntroduction()
{
	glClear(GL_COLOR_BUFFER_BIT);
	text->renderText("Za chwile na ekranie wyswietli sie scena w oswietlonym pokoju. ", 10, 100, 30);
	text->renderText("Ruch ludzkiego oka bedzie symulowany za pomoca ruchu myszki. ", 10, 150, 30);
	text->renderText("Po nacisnieciu lewego przycisku myszy zgasnie swiatlo i rozpocznie sie proces", 10, 200, 30);
	text->renderText("adaptacji do ciemnosci.", 10, 230, 30);
	text->renderText("Symulacja zakonczy sie 10 sekund pozniej.", 10, 280, 30);
	text->renderText("Adaptacja bedzie przebiegac z inna predkoscia.", 10, 500, 50);
	text->renderText("Nacisnij ENTER, aby kontynuowac.", 10, 570, 50);
}

void Game::drawSummary()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	barDrawer->Apply();
	barDrawer->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	barDrawer->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	barDrawer->GetParameter("boxPosition")->SetValue(boxPosition);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, barDrawer->GetParameter("World"));

	
	text->renderText("Ktory sposob adaptacji bardziej Ci odpowiadal?", 50, 300, 50);
	text->renderText("Zdecydowanie pierwszy", 2, (int)(WINDOW_HEIGHT * 0.58), 18);
	text->renderText("Raczej pierwszy", (int)(0.225 * WINDOW_WIDTH), (int)(0.83 * WINDOW_HEIGHT), 18);
	text->renderText("Nie widze roznicy", (int)(0.45 * WINDOW_WIDTH), (int)(0.58 * WINDOW_HEIGHT), 18);
	text->renderText("Raczej drugi", (int)(0.675 * WINDOW_WIDTH), (int)(0.83 * WINDOW_HEIGHT), 18);
	text->renderText("Zdecydowanie drugi", (int)(0.85 * WINDOW_WIDTH), (int)(0.58 * WINDOW_HEIGHT), 18);
	if (sessionsLeft > 1)
		text->renderText("Nacisnij SPACJE, aby zatwierdzic wybor i rozpoczac nowa sesje.", 10, (int)(WINDOW_HEIGHT * 0.95), 50);
	else
		text->renderText("Nacisnij SPACJE, aby zakonczyc eksperyment.", 10, (int)(WINDOW_HEIGHT * 0.95), 50);
}

void Game::drawScene()
{
	if (clickCounter > 0) {
		elapsedTime += deltaTime;
		if (elapsedTime > 10.0f) {
			//gameMode = (gameMode == FIRST_PRESENTATION ? SECOND_INTRODUCTION : SUMMARY);
			elapsedTime = 0.0f;
			clickCounter = 0;
			boxPosition = 0.0f;
		}
	}
	
	sceneRT->SetRenderTarget();
	objectsDrawer->Apply();
	drawSceneObjects(objectsDrawer);

	luminanceMap->SetRenderTarget();
	maskMultiplier->Apply();
	maskMultiplier->GetParameter("tex")->SetValue(*sceneRT);
	maskMultiplier->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	maskMultiplier->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	maskMultiplier->GetParameter("width")->SetValue((float)WINDOW_WIDTH);
	maskMultiplier->GetParameter("height")->SetValue((float)WINDOW_HEIGHT);
	maskMultiplier->GetParameter("fov")->SetValue(90.0f);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, maskMultiplier->GetParameter("World"));
	luminanceMap->createMipmaps();
	
	
	changedLuminance->SetRenderTarget();
	luminanceCalculator->Apply();
	if (first)
	{
		first = false;
		luminanceCalculator->GetParameter("oldTexture")->SetValue(*luminanceMap);
	}
	else
	{
		luminanceCalculator->GetParameter("oldTexture")->SetValue(*currentLuminance);
	}

	luminanceCalculator->GetParameter("aimTexture")->SetValue(*luminanceMap);
	luminanceCalculator->GetParameter("deltaTime")->SetValue(deltaTime);
	luminanceCalculator->GetParameter("speed")->SetValue(speeds[(gameMode == FIRST_PRESENTATION ? firstSpeed : secondSpeed)]);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, luminanceCalculator->GetParameter("World"));

	currentLuminance->SetRenderTarget();
	textureCopier->Apply();
	textureCopier->GetParameter("tex")->SetValue(*changedLuminance);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, textureCopier->GetParameter("World"));
	currentLuminance->createMipmaps();

	adaptedRT->SetRenderTarget();
	toneCompressor->Apply();
	toneCompressor->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	toneCompressor->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	toneCompressor->GetParameter("luminance")->SetValue(*currentLuminance);
	drawSceneObjects(toneCompressor);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	spriteDrawer->Apply();
	spriteDrawer->GetParameter("tex")->SetValue(*adaptedRT);
	spriteDrawer->GetParameter("x")->SetValue(mousePosition.x / WINDOW_WIDTH);
	spriteDrawer->GetParameter("y")->SetValue(1.0f - mousePosition.y / WINDOW_HEIGHT);
	quad->Draw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, spriteDrawer->GetParameter("World"));
}

void Game::mouseMotion(double x, double y)
{
	mousePosition = glm::vec2(x, y);

	if (gameMode == SUMMARY && movingBar) {

		float normalBoxPosition = (boxPosition + 1.0f) * 0.5f * 0.9f + 0.05f;
		float normalY = 1.0f - mousePosition.y / WINDOW_HEIGHT;
		float normalX = mousePosition.x / WINDOW_WIDTH;

		if (normalX >= 0.05f && normalX <= 0.95f)
			boxPosition = (((normalX - 0.05f) / 0.9f) / 0.5f) - 1.0f;
		else if (normalX < 0.05f)
			boxPosition = -1.0f;
		else
			boxPosition = 1.0f;
	}

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

void Game::mouseClick(int button, int action)
{
	if (button = GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && (gameMode == FIRST_PRESENTATION || gameMode == SECOND_PRESENTATION)) {
		lightOn = !lightOn;
		clickCounter++;
		if (clickCounter == 1) {
			elapsedTime = 0.0f;
		}
	}

	if (button = GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS && gameMode == SUMMARY) {
		float normalBoxPosition = (boxPosition + 1.0f) * 0.5f * 0.9f + 0.05f;
		float normalY = 1.0f - mousePosition.y / WINDOW_HEIGHT;
		float normalX = mousePosition.x / WINDOW_WIDTH;

		if (abs(normalY - 0.3f) < 0.1f && abs(normalX - normalBoxPosition) < 0.01f)
			movingBar = true;
	}
	if (button = GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE && gameMode == SUMMARY) {
		movingBar = false;
	}
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
