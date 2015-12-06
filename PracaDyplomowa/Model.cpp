#include "stdafx.h"

Model::Model(vector<SubModel*> subModels)
{
	meshes = subModels;
	elements = meshes.size();
}


Model::~Model(void)
{
}

void Model::Draw()
{
	int size = meshes.size();
	for (int i = 0; i < size; i++)
	{
		meshes.at(i)->Draw();
	}
}

glm::vec3 Model::getScale()
{
	return scale;
}

void Model::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 Model::getPosition()
{
	return position;
}

void Model::setPosition(glm::vec3 position)
{
	this->position = position;
}

void Model::DrawMesh(int i)
{
	meshes.at(i)->Draw();
}
SubModel* Model::GetMesh(int i)
{
	return meshes.at(i);
}
int Model::Elements()
{
	return elements;
}