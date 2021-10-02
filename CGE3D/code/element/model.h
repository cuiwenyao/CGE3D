/*
o myobject
v 0.5 0.5 0.0
v 0.5 -0.5 0.0
v -0.5 -0.5 0.0
v -0.5 0.5 0.0
f 0/0/0 1/1/1 3/3/3
f 1/1/1 2/2/2 3/3/3
*/


#pragma once
#include "../Global_config.h"
#include "mesh.h"
#include "mtllib.h"


class Model
{
public:
	std::string name;
	std::vector<Mesh*> meshes;
	std::string mtl_path;

	//表示一个模型大小
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
	double length;
	double width;
	double height;


	//模型的材质库
	Mtllib* mtllib;

	Model(const char* model_path);
	void generate_shader(const char* vert_path, const char* frag_path);
	void generate_shader(const char* vert_path, const char* frag_path, const char* geo_path);
	void prepare_data_for_draw();
	void attach_shader(Shader* shader);
	void attach_shader_for_meshes();
	void print_info();
	void draw();
private:
	Shader* shader;
};
