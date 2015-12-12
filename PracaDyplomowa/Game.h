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
	RenderTarget2D* text;
	RenderTarget2D* changedLuminance;

	vector<Model*> sceneModels;
	vector<Model*> lightSources;

	Effect* objectsDrawer;
	Effect* tmo;
	Effect* spriteDrawer;
	Effect* toneCompressor;
	Effect* luminanceCalculator;
	Effect* shadowEffect;
	Effect* maskGenerator;
	Effect* textureCopier;
	Effect* maskMultiplier;
	Effect* drawText;

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

	bool first;
	bool lightOn;

	GAME_MODE gameMode;
	FT_Face font;

	void setDeltaTime();

public:
	Game(void);
	~Game(void);
	void Update();
	void Init();
	void Redraw();
	void drawScene();
	void Input();
	void mouseMotion(double x, double y);
	void mouseClick(int button, int action);
	void drawSceneObjects(Effect* e);
	void updateCameraAngles(float angleHorizontalDelta, float angleVerticalDelta);
	void renderText(const std::string &str, float x, float y, float sx, float sy);
};

