#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../tool/stb_image.h"

Texture::Texture(const char* img_path)
{
	glGenTextures(1, &this->texture);
	stbi_set_flip_vertically_on_load(true);
	this->texture_data = stbi_load(img_path, &this->width, &this->heigh, &this->nrchannels, 0);
	//std::cout << "nrchannels: " << nrchannels << std::endl;
	this->set_texture_surround(TEXTURE_SURROUND_REPEAT);
	this->set_texture_filtering(TEXTURE_FILTERING_LINEAR);
	this->set_texture_mipmap_filtering(TEXTURE_LINEAR_MIPMAP_LINEAR);
	this->generate();
}

//指定绑定的纹理单元
void Texture::bind(unsigned texture_unit_num)
{
	glActiveTexture(GL_TEXTURE0+ texture_unit_num); // 在绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, this->texture);
}
void Texture::bind()
{
	glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
	glBindTexture(GL_TEXTURE_2D, this->texture);
}
void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::generate()
{
	this->bind();
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, this->border_color);
	if (this->nrchannels == 4)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->heigh, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture_data);
	}
	else if (this->nrchannels == 3)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->heigh, 0, GL_RGB, GL_UNSIGNED_BYTE, this->texture_data);
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	this->unbind();
}
void Texture::set_border_color(float border_color[4])
{
	memcpy(this->border_color, border_color, 4 * sizeof(float));
	this->generate();
}
void Texture::set_texture_surround(TEXTURE_SURROUND texture_surround)
{
	this->bind();
	this->texture_surround = texture_surround;
	switch (texture_surround)
	{
	case TEXTURE_SURROUND_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case TEXTURE_SURROUND_MIRRORED_REPEAT:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	case TEXTURE_SURROUND_CLAMP_TO_EDGE:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case TEXTURE_SURROUND_CLAMP_TO_BORDER:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	}
	if (texture_surround == TEXTURE_SURROUND_CLAMP_TO_BORDER)
	{
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, this->border_color);
	}
	this->unbind();
	this->generate();
}
void Texture::set_texture_filtering(TEXTURE_FILTERING texture_filtering)
{
	this->bind();
	this->texture_filtering = texture_filtering;
	switch (texture_filtering)
	{
	case TEXTURE_FILTERING_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TEXTURE_FILTERING_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	this->unbind();
	this->generate();
}
void Texture::set_texture_mipmap_filtering(TEXTURE_MIPMAP_FILTERING texture_mipmap_filtering)
{
	this->bind();
	this->texture_mipmap_filtering = texture_mipmap_filtering;
	switch (texture_mipmap_filtering)
	{
	case TEXTURE_NEAREST_MIPMAP_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TEXTURE_LINEAR_MIPMAP_NEAREST:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	case TEXTURE_NEAREST_MIPMAP_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		break;
	case TEXTURE_LINEAR_MIPMAP_LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	}
	this->unbind();
	this->generate();
}