#include "stdafx.h"

Content::Content(void)
{
}

Content::~Content(void)
{
}

Texture2D *Content::LoadTexture(const char *filePath)
{
	string  fullPath(filePath);
	fullPath = "../resources/" + fullPath;
	FREE_IMAGE_FORMAT formato = FreeImage_GetFileType(fullPath.c_str(), 0);
	if (formato == FIF_UNKNOWN) { cout << "wrong image format or file does not exist."; }
	FIBITMAP* imagen = FreeImage_Load(formato, fullPath.c_str());
	if (!imagen) { cout << "wrong image format or file does not exist."; }

	FIBITMAP* temp = imagen;
	imagen = FreeImage_ConvertTo32Bits(imagen);
	FreeImage_Unload(temp);

	int w = FreeImage_GetWidth(imagen);
	int h = FreeImage_GetHeight(imagen);

	cout << "The size of the image in " << filePath << " is: " << w << "x" << h << endl; //Some debugging code

	GLubyte* texture = new GLubyte[4 * w*h];
	char* pixeles = (char*)FreeImage_GetBits(imagen);

	//bgr2rgb
	for (int j = 0; j<w*h; j++)
	{
		texture[j * 4 + 0] = pixeles[j * 4 + 2];
		texture[j * 4 + 1] = pixeles[j * 4 + 1];
		texture[j * 4 + 2] = pixeles[j * 4 + 0];
		texture[j * 4 + 3] = pixeles[j * 4 + 3];
	}
	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);
	GLenum huboError = glGetError();
	if (huboError) {
		cout << "There was an error loading the texture: " << glewGetErrorString(huboError) << endl;
	}

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	FreeImage_Unload(imagen);

	Texture2D* tex = new Texture2D(w, h, textureID);
	return tex;
}

/*
Model *Content::LoadModel(const char *filePath)
{
	vector<tinyobj::shape_t> shapes;
	vector<tinyobj::material_t> materials;
	string err = tinyobj::LoadObj(shapes, materials, filePath, "../resources/");

	if (!err.empty()) {
		std::cerr << err << std::endl;
		exit(1);
	}




}*/



Model *Content::LoadModel(const char *filePath)
{
	Assimp::Importer *importer = new Assimp::Importer();
	const aiScene* scene = importer->ReadFile(filePath, !aiProcess_JoinIdenticalVertices & aiProcessPreset_TargetRealtime_MaxQuality | aiProcess_PreTransformVertices | aiProcess_GenNormals);

	if (!scene)
	{
		cout << "Error occured: " << importer->GetErrorString() << endl;
		exit(-1);
	}

	cout << "Import of scene " << filePath << " succeeded.\n";

	int meshes = scene->mNumMeshes;
	cout << "meshes: " << meshes << endl;

	vector<SubModel*> vec;
	for (int i = 0; i<meshes; i++)
	{
		SubModel *newMesh = new SubModel(*scene->mMeshes[i]);
		newMesh->setLocalWorld(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
		scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
		
		aiMaterial *material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
		
		Material mat;

		aiColor4D albedo;
		float specularIntensity;
		float specularPower;

		//material.Get(AI_MATKEY_NAME, Name);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, albedo);
		material->Get(AI_MATKEY_SHININESS_STRENGTH, specularIntensity);
		material->Get(AI_MATKEY_SHININESS, specularPower);

		aiString *p = new aiString();

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, p) == AI_SUCCESS)
		{
			mat.texture = Content::LoadTexture(p->C_Str());
		}
		else
		{
			mat.texture = NULL;
		}

		mat.Color = glm::vec3(albedo.r, albedo.g, albedo.b);
		mat.specularIntensity = specularIntensity;
		mat.specularPower = specularPower;

		newMesh->SetMaterial(mat);
		vec.push_back(newMesh);
		//meshesVector->push_back(newMesh);
	}

	Model *model = new Model(vec);
	return model;
}
