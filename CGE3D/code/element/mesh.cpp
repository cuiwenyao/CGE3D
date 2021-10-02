#include "mesh.h"

Mesh::Mesh()
{
	x_min=0;
	x_max=0;
	y_min=0;
	y_max=0;
	z_min=0;
	z_max=0;
	length=0;
	width=0;
	height=0;

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
}

void Mesh::prepare_data()
{
	
	//�������� �Ҳ�֪����������ԭʼ��������Ϣ������ֻ�ܽ��㰴�� f �����˳�����vertexes��
	mesh_vertex vert_temp;
	//CM::vecf3 coordinate_temp;//��������
	//CM::vecf2 tex_coord_temp;//��������
	//CM::vecf3 normal_temp;//������
	//������
	for (size_t i = 0; i <= this->face_num - 1; i++)
	{
		//std::cout << this->name<<"������: "<<i << std::endl;
		//��ʱ����normal
		//coordinate_temp  ��i���� �� 1��x����1������
		vert_temp.coordinate = this->vertex_coord.at(this->vertex_index.at(i).x);
		if (i == 0)
		{
			x_min = vert_temp.coordinate.x;
			x_max = vert_temp.coordinate.x;
			y_min = vert_temp.coordinate.y;
			y_max = vert_temp.coordinate.y;
			z_min = vert_temp.coordinate.z;
			z_max = vert_temp.coordinate.z;
		}
		else
		{
			if(x_min > vert_temp.coordinate.x)
				x_min = vert_temp.coordinate.x;
			if(x_max < vert_temp.coordinate.x)
				x_max = vert_temp.coordinate.x;
			if(y_min > vert_temp.coordinate.y)
				y_min = vert_temp.coordinate.y;
			if (y_max < vert_temp.coordinate.y)
				y_max = vert_temp.coordinate.y;
			if(z_min >vert_temp.coordinate.z)
				z_min = vert_temp.coordinate.z;
			if(z_max < vert_temp.coordinate.z)
				z_max = vert_temp.coordinate.z;
		}
		//tex_coord_temp
		if (this->has_tex_coord)
			vert_temp.tex_coord = this->vertex_texture.at(this->vertex_texture_index.at(i).x);
		//normal_temp
		if (this->has_normal)
			vert_temp.normal = this->vertex_normal.at(this->vertex_normal_index.at(i).x);
		this->vertexes.push_back(vert_temp);
		//�ڶ�����
		vert_temp.coordinate = this->vertex_coord.at(this->vertex_index.at(i).y);
		if (this->has_tex_coord)
			vert_temp.tex_coord = this->vertex_texture.at(this->vertex_texture_index.at(i).y);
		if (this->has_normal)
			vert_temp.normal = this->vertex_normal.at(this->vertex_normal_index.at(i).y);
		this->vertexes.push_back(vert_temp);
		//��������  19146 20385 
		vert_temp.coordinate = this->vertex_coord.at(this->vertex_index.at(i).z);
		if (this->has_tex_coord)
			vert_temp.tex_coord = this->vertex_texture.at(this->vertex_texture_index.at(i).z);
		if (this->has_normal)
			vert_temp.normal = this->vertex_normal.at(this->vertex_normal_index.at(i).z);
		this->vertexes.push_back(vert_temp);
	}
	//��ȡģ�͵ĳ������Ϣ��ÿһ����ֻ����һ���㣬�ڱ�֤Ч�ʵ�ͬʱ����ʧ̫��ľ���
	this->length = x_max - x_min;
	this->width = z_max - z_min;
	this->height = y_max - y_min;


	//��˵��struct���ڴ�����������
	//std::cout << "&this->vertex.at(2): " << &this->vertex_coord.at(2) << std::endl;
	//std::cout << "&this->vertex.at(1): " << &this->vertex_coord.at(1) << std::endl;
	//std::cout << "&this->vertex.at(0): " << &this->vertex_coord.at(0) << std::endl;
	//std::cout << "this->vertex.data(): " << this->vertex_coord.data() << std::endl;
	//size_t mem = (&this->vertex_coord.at(2) - &this->vertex_coord.at(0));
	//std::cout << "mem_size: " << mem * sizeof(CM::vecf3) << "  sizeof vecf3" << sizeof(CM::vecf3) << std::endl;

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	//��������
	glBufferData(GL_ARRAY_BUFFER, (sizeof(mesh_vertex)) * this->vertexes.size(), this->vertexes.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	//��������
	//vertex_coord
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (void*)0);
	glEnableVertexAttribArray(0);
	//texture_coord
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(mesh_vertex), (void*)(sizeof(CM::vecf3)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Mesh::generate_shader(const char* vert_path, const char* frag_path)
{
	this->shader = new Shader(vert_path, frag_path);
}
void Mesh::attach_shader(Shader* shader)
{
	this->shader = shader;
}
void Mesh::attach_mtl(Mtl* mtl)
{	
	this->mtl = mtl;
}
void Mesh::print_info()
{
	std::cout << "Mesh info" << std::endl;
	std::cout << "name: " << this->name << std::endl;

	std::cout << "this->v_num: " << this->v_num << std::endl;
	std::cout << "this->vt_num: " << this->vt_num << std::endl;
	std::cout << "this->vn_num: " << this->vn_num << std::endl;

	std::cout << "�����������" << this->vertex_coord.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_coord.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_coord.at(i).x << " " << this->vertex_coord.at(i).y << " " << this->vertex_coord.at(i).z << std::endl;
	}
	std::cout << "���㷨��������" << this->vertex_normal.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_normal.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_normal.at(i).x << " " << this->vertex_normal.at(i).y << " " << this->vertex_normal.at(i).z << std::endl;
	}
	std::cout << "���������������" << this->vertex_texture.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_texture.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_texture.at(i).x << " " << this->vertex_texture.at(i).y << std::endl;
	}
	std::cout << "�����������棩����" << this->vertex_index.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_index.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_index.at(i).x << " " << this->vertex_index.at(i).y << " " << this->vertex_index.at(i).z << std::endl;
	}
	std::cout << "�������������������棩����" << this->vertex_texture_index.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_texture_index.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_texture_index.at(i).x << " " << this->vertex_texture_index.at(i).y << " " << this->vertex_texture_index.at(i).z << std::endl;
	}
	std::cout << "���㷨���������棩����" << this->vertex_normal_index.size() << std::endl;
	std::cout << "���  X   Y   Z" << std::endl;
	for (int i = 0; i <= (int)this->vertex_normal_index.size() - 1; i++)
	{
		std::cout << i << " " << this->vertex_normal_index.at(i).x << " " << this->vertex_normal_index.at(i).y << " " << this->vertex_normal_index.at(i).z << std::endl;
	}
	std::cout << "mesh�İ�������������" << std::endl;
	std::cout << "x_min: " << this->x_min << "x_max" << this->x_max << std::endl;
	std::cout << "y_min: " << this->y_min << "y_max" << this->y_max << std::endl;
	std::cout << "z_min: " << this->z_min << "z_max" << this->z_max << std::endl;
	std::cout << "length: " << this->length << std::endl;
	std::cout << "width: " << this->width << std::endl;
	std::cout << "height: " << this->height << std::endl;
}

void Mesh::draw()
{
	//ʹ�� shader ����
	this->shader->use();

	//������
	for (int i = 0; i <= this->mtl->texes.size() - 1; i++)
	{
		this->mtl->texes.at(i)->bind(i);//�󶨵�Ԫ
		switch (this->mtl->texes.at(i)->texture_type)
		{
		case TEXTURE_TYPE_AMBIENT:
			this->shader->set_uniform_int("ambient", i);
			break;
		case TEXTURE_TYPE_SPECULAR:
			this->shader->set_uniform_int("specular", i);
			break;
		case TEXTURE_TYPE_DIFFUSE:
			this->shader->set_uniform_int("diffuse", i);
			break;
		}
	}

	//�󶨶���������� ׼������
	glBindVertexArray(this->vao);
	//������������� ��ʹ��������������vao�е�����
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glDrawArrays(GL_TRIANGLES, 0, this->vertexes.size());
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
