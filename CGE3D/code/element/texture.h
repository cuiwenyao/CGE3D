#pragma once

#include "../Global_config.h"
#include "../tool/c_math.h"
/*
�����洢��������������Լ���ʽ
*/

class Texture
{
public:
	unsigned int texture;
	TEXTURE_TYPE texture_type;
	TEXTURE_SURROUND texture_surround; //�����Ʒ�ʽ
	TEXTURE_FILTERING texture_filtering; //������˷�ʽ 
	TEXTURE_MIPMAP_FILTERING texture_mipmap_filtering;  //�༶��Զ������˷�ʽ
	float border_color[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; //�߽���ɫ
	int width; //����Ŀ�
	int heigh; //����ĸ�
	int nrchannels;  //������ɫͨ������
	unsigned  char* texture_data;//���������

	Texture(const char* img_path);
	void bind();
	void bind(unsigned texture_unit_num);
	void unbind();
	void generate();
	void set_border_color(float border_color[4]);
	void set_texture_surround(TEXTURE_SURROUND texture_surround);
	void set_texture_filtering(TEXTURE_FILTERING texture_filtering);
	void set_texture_mipmap_filtering(TEXTURE_MIPMAP_FILTERING texture_mipmap_filtering);
private:




};