
#ifndef __myModel_h
#define __myModel_h

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "myMesh.h"
#include "myShader.h"

unsigned int TextureFromFile(const char * path, const string & directory, bool gamma = false);


using namespace std;

class Model
{

public:
	Model(char * path)
	{
		loadModel(path);
	}
	vector<Texture> textures_loaded;
	vector<Mesh> meshes;
	string directory;

	void Draw(Shader shader);

private:


	void loadModel(string path);
	void processNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);
	vector<Texture> loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName);

};


#endif
