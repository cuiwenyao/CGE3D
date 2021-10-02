#pragma once

#include "../Global_config.h"
#include "model.h"

/*
object 就是一个model资源在场景中的实例
*/
class Object
{
public:
	unsigned int ID;
	std::string name;

	//表示一个物体大小
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
	double length;
	double width;
	double height;

	glm::vec3 position = { 0,0,0 };
	glm::vec3 scale_degree = { 1,1,1 };//自身变大或者变小的程度

	glm::mat4 model_mat = glm::mat4(1.0f);
	glm::mat4 view_mat = glm::mat4(1.0f);
	glm::mat4 projection_mat = glm::mat4(1.0f);
	//glm::mat4 transform = glm::mat4(1.0f);

	Object(const char* name, Model* model);
	Object(const char* name, Model* model, Shader* shader);
	Object(const char* name, const char* model_path);
	Object(const char* name, const char* model_path, Shader* shader);
	void init_model_data();
	void attach_shader(Shader* shader);
	void print_info();
	void change_size(double size);//改变大小 单位为像素 本质是缩放
	void draw();

	//移动
	void move_to(glm::vec3 new_position);
	//平移
	void move(glm::vec3 direction);
	//旋转
	void rotate(float radians, glm::vec3 axis);
	//放缩
	void scale(glm::vec3 scale);
	//放缩至原本的倍数
	void scale_to(glm::vec3 scale);

private:
	Model* model;
	Shader* shader;
};