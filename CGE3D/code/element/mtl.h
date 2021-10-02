#pragma once

#include "../Global_config.h"
#include "texture.h"


class Mtl
{
public:
	std::vector<Texture*> texes;
	//mtl�еĲ������� ÿһ��������Ϊһ��texture��mtl�����������
	std::string name;
	CM::vecf3 Ka;
	CM::vecf3 Kd;
	CM::vecf3 Ks;
	unsigned int Ns;
	unsigned int Ni;
	unsigned int d;
	unsigned int illum;
	std::string map_Ka;
	std::string map_Kd;
	std::string map_Ks;
	std::string map_d;
	std::string map_bump;
	
};