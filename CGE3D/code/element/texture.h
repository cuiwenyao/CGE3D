#pragma once

#include "../Global_config.h"
#include "../tool/c_math.h"
/*
纹理，存储程序的纹理数据以及格式
*/

class Texture
{
public:
	unsigned int texture;
	TEXTURE_TYPE texture_type;
	TEXTURE_SURROUND texture_surround; //纹理环绕方式
	TEXTURE_FILTERING texture_filtering; //纹理过滤方式 
	TEXTURE_MIPMAP_FILTERING texture_mipmap_filtering;  //多级渐远纹理过滤方式
	float border_color[4] = { 1.0f, 1.0f, 0.0f, 1.0f }; //边界颜色
	int width; //纹理的宽
	int heigh; //纹理的高
	int nrchannels;  //纹理颜色通道个数
	unsigned  char* texture_data;//纹理的数据

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