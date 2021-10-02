#include "object.h"
#include "../global_valuable/Global_valuable.h"

Object::Object(const char * name,Model* model)
{
	this->ID = ++Global_valuable::OBJECT_NUM;
	this->name = name;
	this->model = model;
	this->init_model_data();
}
Object::Object(const char* name, Model* model, Shader* shader)
{
	this->ID = ++Global_valuable::OBJECT_NUM;
	this->name = name;
	this->model = model;
	this->attach_shader(shader);
	this->init_model_data();
}
Object::Object(const char* name, const char *model_path)
{
	this->ID = ++Global_valuable::OBJECT_NUM;
	this->name = name;
	this->model = new Model(model_path);
	this->init_model_data();
}
Object::Object(const char* name, const char* model_path, Shader* shader)
{
	this->ID = ++Global_valuable::OBJECT_NUM;
	this->name = name;
	this->model = new Model(model_path);
	this->attach_shader(shader);
	this->init_model_data();
}
void Object::init_model_data()
{
	this->x_min = this->model->x_min;
	this->x_max = this->model->x_max;
	this->y_min = this->model->y_min;
	this->y_max = this->model->y_max;
	this->z_min = this->model->z_min;
	this->z_max = this->model->z_max;
	this->length = this->model->length;
	this->width = this->model->width;
	this->height = this->model->height;
}
void Object::attach_shader(Shader* shader)
{
	this->shader = shader;
	this->model->attach_shader(shader);
}
void Object::print_info()
{
	std::cout << "object的包含六面体如下" << std::endl;
	std::cout << "x_min: " << this->x_min << "x_max" << this->x_max << std::endl;
	std::cout << "y_min: " << this->y_min << "y_max" << this->y_max << std::endl;
	std::cout << "z_min: " << this->z_min << "z_max" << this->z_max << std::endl;
	std::cout << "length: " << this->length << std::endl;
	std::cout << "width: " << this->width << std::endl;
	std::cout << "height: " << this->height << std::endl;
}
void Object::change_size(double size)//改变大小 单位为像素 本质是缩放
{
	double max = std::fmax(std::fmax(this->length, this->width), this->height);
	this->scale_to(glm::vec3(size / max));
}
void Object::draw()
{
	this->shader->set_uniform_mat4("model", this->model_mat);
	this->shader->set_uniform_mat4("view", this->view_mat);
	this->shader->set_uniform_mat4("projection", this->projection_mat);
	//每一个obj有一个shader，model的shader只可以依赖于object传递的。绘制object的时候将object的shader传递给model
	this->model->attach_shader(this->shader);
	this->model->draw();
}

//移动
void Object::move_to(glm::vec3 new_position)
{
	this->shader->use();
	this->model_mat = glm::translate(this->model_mat, new_position - this->position);
	this->position = new_position;
	this->shader->set_uniform_mat4("model", this->model_mat);
}
//平移
void Object::move(glm::vec3 direction)
{
	this->shader->use();
	this->model_mat = glm::translate(this->model_mat, direction);
	this->position += direction;
	this->shader->set_uniform_mat4("model", this->model_mat);
}
//旋转
void Object::rotate(float radians, glm::vec3 axis)
{
	this->shader->use();
	this->model_mat = glm::rotate(this->model_mat, radians,axis);
	//新的position我还不不知道怎么求，暂时不要使用这个函数
	this->shader->set_uniform_mat4("model", this->model_mat);
}
//放缩至当前的倍数
void Object::scale(glm::vec3 scale)
{
	this->shader->use();
	this->model_mat = glm::scale(model_mat, scale);
	this->shader->set_uniform_mat4("model", this->model_mat);
}
//放缩至原本的倍数
void Object::scale_to(glm::vec3 scale)
{
	//std::cout << this->scale_degree.x << std::endl;
	this->shader->use();
	glm::vec3 temp = scale;
	scale = scale / this->scale_degree;
	this->scale_degree = temp;
	this->model_mat = glm::scale(model_mat, scale);
	this->shader->set_uniform_mat4("model", this->model_mat);
}