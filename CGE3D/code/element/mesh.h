#pragma once
#include "../Global_config.h"
#include "../tool/c_math.h"
#include "shader.h"
#include "mtl.h"

//����һ���ṹ��洢һ���������������
typedef struct
{
	CM::vecf3 coordinate;//��������
	CM::vecf2 tex_coord;//��������
	CM::vecf3 normal;//������
}mesh_vertex;

class Mesh
{
public:
	std::string name;

	//��ʾһ��mesh��С
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
	double length;
	double width;
	double height;

	std::string usemtl;//ʹ�õ�mtlģ��
	size_t v_num = 0;//v����
	size_t vt_num = 0;//vt����
	size_t vn_num = 0;//vn����
	size_t face_num=0;//�������
	bool has_normal;
	bool has_tex_coord;
	std::vector<mesh_vertex> vertexes; //�����ݴ洢������������У��ٴ����������У���ֱ��ʹ�ø�����
	std::vector<CM::vecf3> vertex_coord; //�������� һ�����������������
	std::vector<CM::veci3> vertex_index; //�����������棩 һ���������������
	std::vector<CM::vecf2> vertex_texture;//������������  һ���������������������
	std::vector<CM::veci3> vertex_texture_index;//������������  һ���������������
	//std::vector<CM::vecf3> vertex_texture_data; //������˳��洢�������������� �ɶ����������꣬������������ ����
	std::vector<CM::vecf3> vertex_normal; //���㷨������ 
	std::vector<CM::veci3> vertex_normal_index; //���㷨������
	std::vector<CM::vecf3> vertex_color; //�������ɫ

	Shader* shader;
	Mtl* mtl;

	Mesh();
	void prepare_data();
	void generate_shader(const char* vert_path, const char* frag_path);
	void generate_shader(const char* vert_path, const char* frag_path, const char* geo_path);
	void attach_shader(Shader*shader);
	void attach_mtl(Mtl* mtl);
	void print_info();
	void draw();

private:
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;

};