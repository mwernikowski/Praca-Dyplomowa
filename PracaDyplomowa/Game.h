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
	RenderTarget2D* shadow;
	RenderTarget2D* sceneWithShadows;

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
	Effect* shadowRenderer;

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
	int nAnimations;

	bool first;
	bool lightOn;
	bool movingBar;
	bool gazeCenter;
	bool experiment;

	int firstSpeed, secondSpeed;

	string input;
	queue<AnimationStep*> steps;

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
	void setExperiment();
	void mouseMotion(double x, double y);
	void mouseClick(int button, int action);
	void drawSceneObjects(Effect* e);
	void drawSceneDepth(Effect* e);
	void updateCameraAngles(float angleHorizontalDelta, float angleVerticalDelta);
};

