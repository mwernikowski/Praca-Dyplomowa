#include "stdafx.h"
#include "AnimationStep.h"


AnimationStep::AnimationStep()
{
}


AnimationStep::~AnimationStep()
{
}

void AnimationStep::createAnimationStep(bool rotation, char direction, float value, bool positive)
{
	this->rotation = rotation;
	this->direction = direction;
	this->value = value;
	this->positive = positive;
}

void AnimationStep::move(float value)
{
	this->value -= value;
}

bool AnimationStep::isFinished()
{
	return (value <= 0.0f);
}

bool AnimationStep::isRotation()
{
	return rotation;
}

bool AnimationStep::isPositive()
{
	return positive;
}

char AnimationStep::getDirection()
{
	return direction;
}

void AnimationStep::addValue(float value)
{
	this->value += value;
}
