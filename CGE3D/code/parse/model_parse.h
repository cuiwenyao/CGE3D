/*
����ģ�����ݣ���ǰֻ֧��obj

o myobject
v -0.5f, -0.5f, 0.0f,
v 0.5f, -0.5f, 0.0f,
v 0.0f,  0.5f, 0.0f
f 1 2 3

һ��ģ���кö��mesh��

model_parse����ģ�Ͳ���������뵽һ��model�����С� model������һ��ʵ�壨������ڣ�������object������Ը���model��������ݡ�
*/


#pragma once
#include "../Global_config.h"
#include "../element/model.h"


class Model_parse
{
public:
	size_t v_num=0;//��������
	size_t vt_num = 0;//��������
	size_t vn_num = 0;//��������
	void parse(const char* file_path);
	void parse_obj();
	void parse_mtl();

	Model_parse(Model* model);

private:
	Model* model;
	std::string path;
	std::string dir_path;
	std::string file_name;
	std::string file_postfix;

	//������һ��
	void skip_to_next_row(size_t& index, std::string* str);
	void skip_white_char(size_t& index, std::string* str);
	void parse_obj_token(size_t& index, std::string* str);
	void parse_obj_token_o(size_t& index, std::string* str);//o  ˵����һ�е�������һ��mesh��name
	void parse_obj_token_v(size_t& index, std::string* str);
	void parse_obj_token_vt(size_t& index, std::string* str);
	void parse_obj_token_vn(size_t& index, std::string* str);
	void parse_obj_token_f(size_t& index, std::string* str);
	void parse_obj_token_mtllib(size_t& index, std::string* str);
	void parse_obj_token_usemtl(size_t& index, std::string* str);

	void parse_mtl_token(size_t& index, std::string* str);
	void parse_mtl_token_newmtl(size_t& index, std::string* str);
	void parse_mtl_token_Ns(size_t& index, std::string* str);
	void parse_mtl_token_Ka(size_t& index, std::string* str);
	void parse_mtl_token_Kd(size_t& index, std::string* str);
	void parse_mtl_token_Ks(size_t& index, std::string* str);
	void parse_mtl_token_Ni(size_t& index, std::string* str);
	void parse_mtl_token_d(size_t& index, std::string* str);
	void parse_mtl_token_illum(size_t& index, std::string* str);
	void parse_mtl_token_map_Ka(size_t& index, std::string* str);
	void parse_mtl_token_map_Kd(size_t& index, std::string* str);
	void parse_mtl_token_map_Ks(size_t& index, std::string* str);
	void parse_mtl_token_map_d(size_t& index, std::string* str);
	void parse_mtl_token_map_bump(size_t& index, std::string* str);
};



