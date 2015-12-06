#pragma once

class Model
{
private:
	vector<SubModel*> meshes;
	int elements;
	glm::vec3 scale;
	glm::vec3 position;
public:
	Model(vector<SubModel*>);

	void DrawMesh(int i);
	SubModel* GetMesh(int i);
	int  Elements();//gets number of elements
	~Model(void);
	void Draw();

	glm::vec3 getScale();
	void setScale(glm::vec3 scale);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
};

