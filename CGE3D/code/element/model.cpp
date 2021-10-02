#include "model.h"
#include "../parse/model_parse.h"

Model::Model(const char* model_path)
{
	Model_parse* parse=new Model_parse(this);
	parse->parse(model_path);
	this->prepare_data_for_draw();
	delete(parse);
}
void Model::generate_shader(const char* vert_path, const char* frag_path)
{
	this->shader = new Shader(vert_path, frag_path);
}
void Model::prepare_data_for_draw()
{
	for (size_t i = 0; i <= this->meshes.size() - 1; i++)
	{
		this->meshes.at(i)->prepare_data();
		if (i == 0)
		{
			this->x_max = this->meshes.at(i)->x_max;
			this->x_min = this->meshes.at(i)->x_min;
			this->z_max = this->meshes.at(i)->z_max;
			this->z_min = this->meshes.at(i)->z_min;
			this->y_max = this->meshes.at(i)->y_max;
			this->y_min = this->meshes.at(i)->y_min;
		}
		else
		{
			if (this->x_min > this->meshes.at(i)->x_min)
				this->x_min = this->meshes.at(i)->x_min;
			if (this->y_min > this->meshes.at(i)->y_min)
				this->y_min = this->meshes.at(i)->y_min;
			if (this->z_min > this->meshes.at(i)->z_min)
				this->z_min = this->meshes.at(i)->z_min;
			if (this->x_max < this->meshes.at(i)->x_max)
				this->x_max = this->meshes.at(i)->x_max;
			if (this->y_max < this->meshes.at(i)->y_max)
				this->y_max = this->meshes.at(i)->y_max;
			if (this->z_max < this->meshes.at(i)->z_max)
				this->z_max = this->meshes.at(i)->z_max;
		}
	}
	//mesh已经准备好数据，现在可以让model准备数据了
	this->length = x_max - x_min;
	this->width = z_max - z_min;
	this->height = y_max - y_min;

}
void Model::attach_shader(Shader* shader)
{
	this->shader = shader;
	for (size_t i = 0; i <= meshes.size() - 1; i++)
	{
		meshes.at(i)->attach_shader(this->shader);
	}
}
void Model::attach_shader_for_meshes()
{
	for (size_t i = 0; i <= meshes.size() - 1; i++)
	{
		meshes.at(i)->attach_shader(this->shader);
	}
}
void Model::print_info()
{
	std::cout << "model info" << std::endl;
	std::cout << "name: " << this->name << std::endl;
	std::cout << "mesh个数" << this->meshes.size() << std::endl;
	for (size_t i = 0; i <= meshes.size() - 1; i++)
	{
		meshes.at(i)->print_info();
	}
}

void Model::draw()
{
	for (size_t i = 0; i <= meshes.size() - 1; i++)
	{
		meshes.at(i)->draw();
	}
}