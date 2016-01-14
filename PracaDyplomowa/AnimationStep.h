#pragma once
class AnimationStep
{
private:
	bool rotation;
	char direction;
	float value;
	bool positive;
public:
	AnimationStep();
	~AnimationStep();
	void createAnimationStep(bool rotation, char direction, float value, bool positive);
	void move(float);
	bool isFinished();
	bool isRotation();
	bool isPositive();
	char getDirection();
	void addValue(float value);
};

