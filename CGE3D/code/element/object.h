#pragma once

#include "../Global_config.h"
#include "model.h"

/*
object ����һ��model��Դ�ڳ����е�ʵ��
*/
class Object
{
public:
	unsigned int ID;
	std::string name;

	//��ʾһ�������С
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
	glm::vec3 scale_degree = { 1,1,1 };//��������߱�С�ĳ̶�

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
	void change_size(double size);//�ı��С ��λΪ���� ����������
	void draw();

	//�ƶ�
	void move_to(glm::vec3 new_position);
	//ƽ��
	void move(glm::vec3 direction);
	//��ת
	void rotate(float radians, glm::vec3 axis);
	//����
	void scale(glm::vec3 scale);
	//������ԭ���ı���
	void scale_to(glm::vec3 scale);

private:
	Model* model;
	Shader* shader;
};