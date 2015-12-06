#pragma once
class Game
{
private:
	Quad* quad;
	Texture2D* tex;

	RenderTarget2D* renderTarget1;
	RenderTarget2D* renderTarget2;
	RenderTarget2D* renderTarget3;
	RenderTarget2D* currentLuminance;

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

	bool first;
	bool lightOn;

	void setDeltaTime();

public:
	Game(void);
	~Game(void);
	void Update();
	void Init();
	void Redraw();
	void Input();
	void mouseMotion(double x, double y);
	void drawSceneObjects(Effect* e);
	void updateCameraAngles(float angleHorizontalDelta, float angleVerticalDelta);
};

