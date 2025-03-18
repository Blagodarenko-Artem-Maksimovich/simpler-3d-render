#pragma once

#define NOMINMAX
#include <fstream>
#include <vector>
#include "geometry.h"
#include <iostream>
#include <sstream>
#include "tgaimage.h"
#include "algorithm"

class Model
{
public:
	Model(std::string filename, Vec3f center = Vec3f(0., 0., 0.), float specCoeff = 10.f);

	int nfaces();
	std::vector<std::vector<int>> face(int i);
	Vec3f vert(int i);
	Vec2i uv(int i);
	TGAColor diffuse(Vec2f uv);
	Vec3f normal(int i);
	Vec3f normal(Vec2f uv);
	bool hasNormalMap();
	float spec(Vec2f uv);

	mat4 ModelView();

private:
	std::vector<Vec3f> _vertices{ {0., 0., 0.} };
	std::vector<std::vector<std::vector<int>>> _faces;
	std::vector<Vec2f> _texVertices{ {0., 0.} };
	std::vector<Vec3f> _norms{ {0., 0., 0.} };
	float _scale{ 1 };
	mat4 _ModelView;
	float _defaultSpec;

	void load_texture(std::string filename, const char* suffix, TGAImage& img);

	TGAImage _diffMap;
	TGAImage _normalMap;
	TGAImage _specularMap;
};