#include "model_parse.h"

Model_parse::Model_parse(Model* model)
{
	this->model = model;
}

//解析总控程序
void Model_parse::parse(const char* file_path)
{
	// C:/Users/admin/source/repos/CGE3D/CGE3D/code/glsl/shader.vert
	//读入文件名，获取文件格式，获取文件目录路径。
	if (!file_path)
	{
		std::cout << "error invalid file path" << std::endl;
	}
	std::string path(file_path);
	this->path = path;
	size_t last_backslash = path.rfind('/');
	if (last_backslash == std::string::npos)
		last_backslash = -1;
	if (last_backslash != -1)
	{
		this->dir_path.assign(path, 0, last_backslash + 1);
	}
	int file_name_length = path.length() - last_backslash - 1;
	this->file_name.assign(path, last_backslash + 1, file_name_length);
	//std::cout << "file_name: " << this->file_name << std::endl;
	size_t last_dot = this->file_name.find('.');
	if (last_dot == std::string::npos || last_dot == 0 || this->file_name.length() == 1)
	{
		std::cout << "错误 不确定的文件格式: " << this->file_name << std::endl;
		exit(EXIT_SUCCESS);
	}
	int postfix_length = file_name.length() - last_dot - 1;
	this->file_postfix.assign(this->file_name, last_dot + 1, postfix_length);
	//std::cout << "file_postfix: " << file_postfix << std::endl;
	if (this->file_postfix.compare("obj") == 0)
	{
		this->parse_obj();
	}
	else
	{
		std::cout << "暂未支持的文件格式" << std::endl;
		exit(EXIT_SUCCESS);
	}

}
void Model_parse::parse_obj()
{
	std::cout << "解析到这是一个obj文件，正在解析中" << std::endl;
	double time = glfwGetTime();
	std::ifstream ifile;
	ifile.open(this->path, std::ios::beg);
	char c;
	std::string str;
	size_t index = 0;
	while ((c = ifile.get()) != EOF)
	{
		str.push_back(c);
	}
	//std::cout << "解析此串:\n" <<str<< std::endl;
	while (index < str.length())
	{
		this->skip_white_char(index, &str);
		this->parse_obj_token(index, &str);
	}
	std::cout << "obj解析完成 "<<"耗时: "<< glfwGetTime()-time << std::endl;
}

void Model_parse::parse_mtl()
{
	std::cout << "解析mtl文件" << std::endl;
	std::ifstream ifile;
	ifile.open(this->model->mtl_path, std::ios::beg);
	char c;
	std::string str;
	size_t index = 0;
	while ((c = ifile.get()) != EOF)
	{
		str.push_back(c);
	}
	//std::cout << "mtl解析此串:\n" <<str<< std::endl;
	while (index < str.length())
	{
		this->skip_white_char(index, &str);
		this->parse_mtl_token(index, &str);
	}
	std::cout << "mtl解析完成" << std::endl;
}
// 跳过空白部分
// 解析 标识符 从而得知其后的数据是什么成分
// 将解析到的数据存放
// o v vt vn f 

void Model_parse::skip_to_next_row(size_t& index, std::string* str)
{
	char c;
	while (index < str->size())
	{
		c = str->at(index);
		if (c != '\n')
			index++;
		else
			break;
	}
	//现在index指向换行符
	index++;
}
//跳过空白符
void Model_parse::skip_white_char(size_t& index, std::string* str)
{
	char c;
	while (index < str->length())
	{
		c = str->at(index);
		if (c == '\n' || c == '\t' || c == '\r' || c == ' ')
			index++;
		else
			return;
	}

}

//解析标识符 即一行的开始的字符串以此来认定是什么数据
void Model_parse::parse_obj_token(size_t& index, std::string* str)
{
	//std::cout << "解析标识符" <<str->at(index)<< std::endl;
	skip_white_char(index, str);
	//从index开始比较1个字符
	//前缀码
	if (index >= str->length())
		return;
	//mtllib
	else if (!str->compare(index, 6, "mtllib"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_obj_token_mtllib(index, str);
	}
	//usemtl 
	else if (!str->compare(index, 6, "usemtl"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_obj_token_usemtl(index, str);
	}
	// 顶点纹理坐标
	else if (!str->compare(index, 2, "vt"))
	{
		index += 2;
		this->skip_white_char(index, str);
		this->parse_obj_token_vt(index, str);
	}
	//顶点法线 
	else if (!str->compare(index,  2, "vn"))
	{
		index += 2;
		this->skip_white_char(index, str);
		this->parse_obj_token_vn(index, str);
	}
	//object 
	else if (!str->compare(index, 1, "o"))
	{
		index++;
		this->skip_white_char(index, str);
		this->parse_obj_token_o(index, str);
	}
	// vertex 顶点坐标
	else if (!(str->compare(index, 1, "v")))
	{
		index++;
		this->skip_white_char(index, str);
		this->parse_obj_token_v(index, str);
	}
	else if (!str->compare(index, 1, "f"))
	{
		index++;
		this->skip_white_char(index, str);
		this->parse_obj_token_f(index, str);
	}
	else if (!str->compare(index, 1, "#"))
	{
		skip_to_next_row(index, str);
	}
	else
	{
		if(index<str->length())
			//std::cout << "obj 暂时无法解析" << str->at(index) << std::endl;
		skip_to_next_row(index,str);
		return;
	}
}

//o  说明这一行的数据是一个mesh的name
void Model_parse::parse_obj_token_o(size_t& index, std::string* str)
{
	//解析出一个 mesh 放入model中
	int a = this->model->meshes.size();
	if (a > 0)
	{
		this->v_num = this->v_num + this->model->meshes.at(a - 1)->v_num;
		this->vt_num = this->vt_num+ this->model->meshes.at(a - 1)->vt_num;
		this->vn_num = this->vn_num+ this->model->meshes.at(a - 1)->vn_num;
	}
	else
	{
		this->v_num = 0;
		this->vt_num = 0;
		this->vn_num = 0;
	}
	Mesh* mesh = new Mesh();
	this->model->meshes.push_back(mesh);
	//解析mesh的名字
	size_t name_index = index;
	char c;
	while (name_index<str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\t' || c == '\r' || c == ' ')
			break;
		name_index++;
	}
	name_index--;
	size_t name_length = name_index - index+1;
	mesh->name.assign(*str, index, name_length);
	index = name_index + 1;
	//std::cout << "解析出一个mesh：" << mesh->name << std::endl;
}


//解析顶点坐标
void Model_parse::parse_obj_token_v(size_t& index, std::string* str)
{
	//std::cout << "获取顶点坐标" << std::endl;
	//获取当前mesh
	Mesh* mesh = this->model->meshes.at(this->model->meshes.size() - 1);
	mesh->v_num++;
	char* end;
	CM::vecf3 res;
	//for (int i = 1; i <= 1; i++)
	{
		skip_white_char(index, str);
		res.x = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
		skip_white_char(index, str);
		res.y = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
		skip_white_char(index, str);
		res.z = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
	}
	mesh->vertex_coord.push_back(res);
}
//vt
void Model_parse::parse_obj_token_vt(size_t& index, std::string* str)
{
	//std::cout << "获取顶点纹理坐标" << std::endl;
	//获取当前mesh
	Mesh* mesh = this->model->meshes.at(this->model->meshes.size() - 1);
	mesh->vt_num++;
	char* end;
    CM::vecf2 res;
	//for (int i = 1; i <= 1; i++)
	{
		skip_white_char(index, str);
		res.x = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
		skip_white_char(index, str);
		res.y = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
	}
	mesh->vertex_texture.push_back(res);
}
//vn
void Model_parse::parse_obj_token_vn(size_t& index, std::string* str)
{
	//std::cout << "获取顶点法线坐标" << std::endl;
	//获取当前mesh
	Mesh* mesh = this->model->meshes.at(this->model->meshes.size() - 1);
	mesh->vn_num++;
	char* end;
	CM::vecf3 res;
	//for (int i = 1; i <= 1; i++)
	{
		skip_white_char(index, str);
		res.x = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
		skip_white_char(index, str);
		res.y = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
		skip_white_char(index, str);
		res.z = strtod(str->c_str() + index, &end);
		index = end - str->c_str();
	}
	mesh->vertex_normal.push_back(res);
}
void Model_parse::parse_obj_token_f(size_t& index, std::string* str)
{
	CM::length(CM::vecf3(1));
	//obj中的索引是从1开始的，所以要进行减一处理
	//std::cout << "获取索引（面）" << std::endl;
	//获取当前mesh
	Mesh* mesh = this->model->meshes.at(this->model->meshes.size() - 1);
	mesh->face_num++;
	char* end;
	unsigned int res;
	std::vector<unsigned int> ver_i;
	std::vector<unsigned int> ver_t_i;
	std::vector<unsigned int> ver_n_i;
	for (int i = 1; i <= 3; i++)
	{
		//v
		skip_white_char(index, str);
		res = strtod(str->c_str() + index, &end)-1-this->v_num;
		ver_i.push_back(res);
		index = end - str->c_str();
		//如果不是斜杠,说明没有纹理坐标，则略过
		if (index >= str->size())
		{
			mesh->has_tex_coord = false;
			break;
		}
		if (str->at(index) != '/')
		{
			mesh->has_tex_coord = false;
			continue;
		}
		mesh->has_tex_coord = true;
		index++;//略过下一个斜杠
		//vt
		res = strtod(str->c_str() + index, &end)-1 - this->vt_num;
		ver_t_i.push_back(res);
		index = end - str->c_str();
		//检查是否超限
		if (index >= str->size())
		{
			mesh->has_normal = false;
			break;
		}
		//如果不是斜杠,说明没有法向量 则略过
		if (str->at(index) != '/')
		{
			mesh->has_normal = false;
			continue;
		}
		mesh->has_normal = true;
		index++;//略过下一个斜杠
		//vn
		res = strtod(str->c_str() + index, &end)-1 - this->vn_num;
		ver_n_i.push_back(res);
		index = end - str->c_str();
	}
	//将vector转化为veci3
	CM::veci3 temp;
	temp.x = ver_i.at(0);
	temp.y = ver_i.at(1);
	temp.z = ver_i.at(2);
	mesh->vertex_index.push_back(temp);
	if (mesh->has_tex_coord)
	{
		temp.x = ver_t_i.at(0);
		temp.y = ver_t_i.at(1);
		temp.z = ver_t_i.at(2);
	}
	else
	{
		temp.x = 0;
		temp.y = 0;
		temp.z = 0;
	}
	mesh->vertex_texture_index.push_back(temp);

	if (mesh->has_normal)
	{
		temp.x = ver_n_i.at(0);
		temp.y = ver_n_i.at(1);
		temp.z = ver_n_i.at(2);
	}
	else
	{
		temp.x = 0;
		temp.y = 0;
		temp.z = 0;
	}
	mesh->vertex_normal_index.push_back(temp);
}

void Model_parse::parse_obj_token_mtllib(size_t& index, std::string* str)
{
	//解析出一个 mtl路径 放入model中
	//解析mtl的名字
	//std::cout << "获取mtllib" << std::endl;
	std::string mtl_name;
	size_t name_index = index;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\t' || c == '\r' || c == ' ')
			break;
		name_index++;
	}
	//name_index--;
	size_t name_length = name_index - index;
	mtl_name.assign(*str, index, name_length );
	index = name_index;
	//生成mtl的路径
	this->model->mtl_path = this->dir_path + mtl_name;
	//std::cout << "解析出一个mtl：" << this->model->mtl_path << std::endl;
	//解析该mtl库  mtllib - mtles  之于  model - meshes
	this->model->mtllib = new Mtllib();
	this->model->mtllib->mtl_path = this->model->mtl_path;
	this->parse_mtl();
}
void Model_parse::parse_obj_token_usemtl(size_t& index, std::string* str)
{
	//std::cout << "获取 usemtl" << std::endl;
	//获取当前mesh
	Mesh* mesh = this->model->meshes.at(this->model->meshes.size() - 1);
	size_t name_index = index;
	size_t name_length = 0;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\t' || c == '\r' || c == ' ')
			break;
		name_index++;
	}
	name_length = name_index - index;
	mesh->usemtl.assign(*str, index, name_length);
	index = name_index;
	//std::cout << "解析出一个usemtl：" << mesh->usemtl << std::endl;
	//由于mtl文件早已解析完成，这里只需要进行寻找并装配即可
	for (unsigned int i = 0; i <= this->model->mtllib->mtls.size() - 1; i++)
	{
		if (mesh->usemtl.compare(this->model->mtllib->mtls.at(i)->name) == 0)
		{
			mesh->attach_mtl(this->model->mtllib->mtls.at(i));
			//std::cout << "usemtl已成功attach" << mesh->usemtl << std::endl;
			return;
		}
	}
	std::cout << "usemtl错误，没有此mtl" << mesh->usemtl << std::endl;
}

void Model_parse::parse_mtl_token(size_t& index, std::string* str)
{
	//std::cout << "解析标识符" <<str->at(index)<< std::endl;
	skip_white_char(index, str);
	if (index >= str->length())
		return;
	//newmtl
	else if (!str->compare(index, 6, "newmtl"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_mtl_token_newmtl(index, str);
	}
	//map_Ka
	else if (!str->compare(index, 6, "map_Ka"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_mtl_token_map_Ka(index, str);
	}
	//map_Kd
	else if (!str->compare(index, 6, "map_Kd"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_mtl_token_map_Kd(index, str);
	}
	//map_Ks
	else if (!str->compare(index, 6, "map_Ks"))
	{
		index += 6;
		this->skip_white_char(index, str);
		this->parse_mtl_token_map_Ks(index, str);
	}
	else if (!str->compare(index, 1, "#"))
	{
		//std::cout << "注释" << str->at(index) << std::endl;
		skip_to_next_row(index, str);
	}
	else
	{
		if (index < str->length())
			//std::cout << "mtl 暂时无法解析,略过此行" << str->at(index) << std::endl;
		skip_to_next_row(index, str);
		return;
	}
}
void Model_parse::parse_mtl_token_newmtl(size_t& index, std::string* str)
{
	//std::cout << "parse_mtl_token_newmtl" << std::endl;
	skip_white_char(index, str);
	//解析出名字，新生成一个mtl放入model->mtllib中
	Mtl* new_mtl = new Mtl();
	std::string mtl_name;
	size_t name_index = index;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\r' || c == '\t' || c == ' ')
			break;
		name_index++;
	}
	size_t name_length = name_index - index;
	mtl_name.assign(*str, index, name_length);
	index = name_index;
	new_mtl->name = mtl_name;
	this->model->mtllib->mtls.push_back(new_mtl);
	//std::cout << "解析出一个新的mtl："<< new_mtl->name << std::endl;
}
void Model_parse::parse_mtl_token_Ns(size_t& index, std::string* str)
{
	
}
void Model_parse::parse_mtl_token_Ka(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_Kd(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_Ks(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_Ni(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_d(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_illum(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_map_Ka(size_t& index, std::string* str)
{
	//ambient
	//解析参数，即目标文件名，由目标文件生成一个纹理并放入当前的mtl中
	//std::cout << "获取 ambient Ka" << std::endl;
	//获取当前的mtl
	Mtl* cur_mtl = this->model->mtllib->mtls.at(this->model->mtllib->mtls.size() - 1);
	skip_white_char(index, str);
	std::string file_name;
	size_t name_index = index;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\r' || c == '\t' || c == ' ')
			break;
		name_index++;
	}
	size_t name_length = name_index - index;
	file_name.assign(*str, index, name_length);
	index = name_index;
	std::string file_path = this->dir_path + file_name;
	Texture* new_tex = new Texture(file_path.c_str());
	new_tex->texture_type = TEXTURE_TYPE_AMBIENT;
	cur_mtl->texes.push_back(new_tex);
	//std::cout << "获取 ambient KA 成功 path: " << file_path << std::endl;
}
void Model_parse::parse_mtl_token_map_Kd(size_t& index, std::string* str)
{
	//diffuse
	//解析参数，即目标文件名，由目标文件生成一个纹理并放入当前的mtl中
	//std::cout << "获取 diffuse Kd" << std::endl;
	//获取当前的mtl
	Mtl* cur_mtl = this->model->mtllib->mtls.at(this->model->mtllib->mtls.size() - 1);
	skip_white_char(index, str);
	std::string file_name;
	size_t name_index = index;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\r' || c == '\t' || c == ' ')
			break;
		name_index++;
	}
	size_t name_length = name_index - index;
	file_name.assign(*str, index, name_length);
	index = name_index;
	std::string file_path = this->dir_path + file_name;
	Texture* new_tex = new Texture(file_path.c_str());
	new_tex->texture_type = TEXTURE_TYPE_DIFFUSE;
	cur_mtl->texes.push_back(new_tex);
	//std::cout << "获取 diffuse Kd 成功 path: "<< file_path << std::endl;
}
void Model_parse::parse_mtl_token_map_Ks(size_t& index, std::string* str)
{
	//specular
	//std::cout << "获取 specular Ks" << std::endl;
	//获取当前的mtl
	Mtl* cur_mtl = this->model->mtllib->mtls.at(this->model->mtllib->mtls.size() - 1);
	skip_white_char(index, str);
	std::string file_name;
	size_t name_index = index;
	char c;
	while (name_index < str->length())
	{
		c = str->at(name_index);
		if (c == '\n' || c == '\r' || c == '\t' || c == ' ')
			break;
		name_index++;
	}
	size_t name_length = name_index - index;
	file_name.assign(*str, index, name_length);
	index = name_index;
	std::string file_path = this->dir_path + file_name;
	Texture* new_tex = new Texture(file_path.c_str());
	new_tex->texture_type = TEXTURE_TYPE_SPECULAR;
	cur_mtl->texes.push_back(new_tex);
	//std::cout << "获取 specular Ks 成功 path: " << file_path << std::endl;
}
void Model_parse::parse_mtl_token_map_d(size_t& index, std::string* str)
{

}
void Model_parse::parse_mtl_token_map_bump(size_t& index, std::string* str)
{

}

