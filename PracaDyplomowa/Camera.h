#pragma once
__declspec(align(16)) class Camera
{
private:
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::mat4x4 View;
	glm::mat4x4 Projection;
	float width;
	float height;
	float horizontalAngle;
	float verticalAngle;
public:
	Camera() {}

	Camera(float Width, float Height)
		:width(Width), height(Height), position(glm::vec3(0, 0.5f, -2.0f)), lookAt(glm::vec3(0.0f, 0.0f, 0.0f))
	{
		width = Width;
		height = Height;
		horizontalAngle = 0.0f;
		verticalAngle = 0.0f;
		View = glm::lookAt(position, lookAt, glm::vec3(0, 1, 0));
		Projection = glm::perspective(45.0f, Width / Height, 0.1f, 100.0f);
	}
	Camera(glm::vec3 Position, glm::vec3 Target, float Width, float Height)
		:width(Width), height(Height), position(Position), lookAt(Target)
	{
		width = Width;
		height = Height;
		horizontalAngle = 0.0f;
		verticalAngle = 0.0f;
		View = glm::lookAt(position, lookAt, glm::vec3(0, 1, 0));
		Projection = glm::perspective(45.0f, Width / Height, 0.1f, 100.0f);
	}

	glm::mat4x4 getView()
	{
		View = glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
		return View;
	}

	glm::mat4x4 getProjection()
	{
		return Projection;
	}

	glm::mat4x4 getViewProjection()
	{
		View = glm::lookAt(position, lookAt, glm::vec3(0, 1, 0));
		return Projection*View;
	}

	void setPosition(glm::vec3 Position)
	{
		position = Position;
	}

	void setTarget(glm::vec3 Target)
	{
		lookAt = Target;
	}

	glm::vec3 getPosition()
	{
		return position;
	}

	glm::vec3 getTarget()
	{
		return lookAt;
	}

	void setHorizontalAngle(float horizontalAngle)
	{
		this->horizontalAngle = horizontalAngle;
	}

	float getHorizontalAngle()
	{
		return horizontalAngle;
	}

	void setVerticalAngle(float verticalAngle)
	{
		this->verticalAngle = verticalAngle;
	}

	float getVerticalAngle()
	{
		return verticalAngle;
	}

	void SetFOV(float fov)
	{
		Projection = glm::perspective(fov, width / height, 0.1f, 100.0f);
	}

	void* operator new(size_t i)
	{
		return _mm_malloc(i,16);
	}

	void operator delete(void* p)
	{
		_mm_free(p);
	}
};

