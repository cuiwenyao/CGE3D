#pragma once

#include "../Global_config.h"

class Shader
{
public:
	
	Shader(const char* vert_path, const char* frag_path);
	Shader(const char* vert_path, const char* frag_path,const char * geo_path);
	
	void use();
	void set_uniform_bool(const std::string& bool_name, bool value);
	void set_uniform_int(const std::string& int_name, int value);
	void set_uniform_float(const std::string& float_name, float value);
	void set_uniform_vec2(const std::string& name, glm::vec2& value);
	void set_uniform_vec3(const std::string& name, glm::vec3& value);
	void set_uniform_vec4(const std::string& name, glm::vec4& value);
	void set_uniform_mat2(const std::string& name, glm::mat2& value);
	void set_uniform_mat3(const std::string& name, glm::mat3& value);
	void set_uniform_mat4(const std::string& name, glm::mat4& value);


private:
	unsigned int shader_program;
};