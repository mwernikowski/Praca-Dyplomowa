#pragma once
class Game
{
private:
	Quad* quad;
	Texture2D* tex;

	RenderTarget2D* maskRT;
	RenderTarget2D* sceneRT;
	RenderTarget2D* luminanceMap;
	RenderTarget2D* currentLuminance;
	RenderTarget2D* adaptedRT;
	RenderTarget2D* changedLuminance;

	vector<Model*> sceneModels;
	vector<Model*> lightSources;

	Effect* objectsDrawer;
	Effect* tmo;
	Effect* spriteDrawer;
	Effect* toneCompressor;
	Effect* luminanceCalculator;
	Effect* shadowEffect;
	Effect* textureCopier;
	Effect* maskMultiplier;
	Effect* barDrawer;

	Text2D* text;

	Camera* camera;
	Camera* light;
	glm::vec3 LightPosition;
	glm::vec2 mousePosition;
	float theta;
	float playerSpeed;
	float deltaTime;
	float mouseSensitivity;
	float specularStrength;
	float lightPower;
	float defaultLightPower;
	float adaptationSpeed;

	float speeds[5];

	int clickCounter;
	float elapsedTime;
	float boxPosition;

	int sessionsLeft;

	bool first;
	bool lightOn;
	bool movingBar;

	int firstSpeed, secondSpeed;
	int repetition;

	string input;

	GAME_MODE gameMode;

	void setDeltaTime();

public:
	Game(string input, int sessions);
	~Game(void);
	void Update();
	void Init();
	void Redraw();
	void drawScene();
	void drawLogin();
	void drawSecondIntroduction();
	void drawSummary();
	void Input();
	void mouseMotion(double x, double y);
	void mouseClick(int button, int action);
	void drawSceneObjects(Effect* e);
	void updateCameraAngles(float angleHorizontalDelta, float angleVerticalDelta);
};

