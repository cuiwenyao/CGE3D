#pragma once
#include "../Global_config.h"
#include "../tool/c_math.h"
#include "shader.h"
#include "mtl.h"

//定义一个结构体存储一个顶点的所有数据
typedef struct
{
	CM::vecf3 coordinate;//顶点坐标
	CM::vecf2 tex_coord;//顶点纹理
	CM::vecf3 normal;//法向量
}mesh_vertex;

class Mesh
{
public:
	std::string name;

	//表示一个mesh大小
	double x_min;
	double x_max;
	double y_min;
	double y_max;
	double z_min;
	double z_max;
	double length;
	double width;
	double height;

	std::string usemtl;//使用的mtl模块
	size_t v_num = 0;//v总数
	size_t vt_num = 0;//vt总数
	size_t vn_num = 0;//vn总数
	size_t face_num=0;//面的数量
	bool has_normal;
	bool has_tex_coord;
	std::vector<mesh_vertex> vertexes; //将数据存储到下面的数据中，再处理到该数据中，再直接使用该数据
	std::vector<CM::vecf3> vertex_coord; //顶点坐标 一个顶点包含三个坐标
	std::vector<CM::veci3> vertex_index; //顶点索引（面） 一个面包含三个顶点
	std::vector<CM::vecf2> vertex_texture;//顶点纹理坐标  一个纹理坐标包含两个坐标
	std::vector<CM::veci3> vertex_texture_index;//顶点纹理索引  一个面包含三个顶点
	//std::vector<CM::vecf3> vertex_texture_data; //按顶点顺序存储真正的纹理坐标 由顶点纹理坐标，顶点纹理索引 生成
	std::vector<CM::vecf3> vertex_normal; //顶点法线坐标 
	std::vector<CM::veci3> vertex_normal_index; //顶点法线索引
	std::vector<CM::vecf3> vertex_color; //顶点的颜色

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