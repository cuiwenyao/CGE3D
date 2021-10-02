#include "shader.h"


Shader::Shader(const char* vert_path, const char* frag_path)
{
    std::string vert_code;
    std::string frag_code;
    std::ifstream ifile;

    
    //异常
    ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        std::stringstream file_stream_vert;
        std::stringstream file_stream_frag;
        //打开文件
        ifile.open(vert_path, std::ios::beg);
        file_stream_vert << ifile.rdbuf();
        vert_code = file_stream_vert.str();
        ifile.close();
        //打开文件
        ifile.open(frag_path, std::ios::beg);
        file_stream_frag << ifile.rdbuf();
        frag_code = file_stream_frag.str();
        ifile.close();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "未能正确读入文件" << std::endl;
    }
    
    /*
    ifile.open(vert_path, std::ios::beg);
    char c;
    while ((c = ifile.get()) != EOF)
    {
        vert_code.push_back(c);
    }
    ifile.close();
    ifile.open(frag_path, std::ios::beg);
    while ((c = ifile.get()) != EOF)
    {
        frag_code.push_back(c);
    }
    ifile.close();
    */



    //编译glsl文件
    unsigned int vertex_shader;
    unsigned int fragment_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vert_code_char = vert_code.c_str();
    const char* frag_code_char = frag_code.c_str();



    glShaderSource(vertex_shader, 1, &vert_code_char, NULL);
    glShaderSource(fragment_shader, 1, &frag_code_char, NULL);

    glCompileShader(vertex_shader);
    int success;
    char shader_compile_info[1024];
    char shader_link_info[1024];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (success)
    {
        //std::cout << "vertext_shader 编译成功" << std::endl;
    }
    else
    {
        glGetShaderInfoLog(vertex_shader, sizeof(shader_compile_info), NULL, shader_compile_info);
        std::cout << "vertext_shader 编译失败" << std::endl << shader_compile_info << std::endl;
        std::cout << "vert_code:" << std::endl << vert_code << std::endl;
        exit(EXIT_SUCCESS);
    }

    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (success)
    {
        //std::cout << "fragment_shader 编译成功" << std::endl;
    }
    else
    {
        glGetShaderInfoLog(fragment_shader, sizeof(shader_compile_info), NULL, shader_compile_info);
        std::cout << "fragment_shader 编译失败" << std::endl << shader_compile_info << std::endl;
        std::cout << "frag_code:" << std::endl << frag_code << std::endl;
        exit(EXIT_SUCCESS);
    }
    //编译完成 进行链接
    
    this->shader_program = glCreateProgram();
    glAttachShader(this->shader_program, vertex_shader);
    glAttachShader(this->shader_program, fragment_shader);
    glLinkProgram(this->shader_program);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    //检查是否链接成功
    glGetProgramiv(this->shader_program, GL_LINK_STATUS, &success);
    if (success)
    {
        //std::cout << "链接成功" << std::endl;
        //std::cout << "vert_code:" << std::endl << vert_code << std::endl;
        //std::cout << "frag_code:" << std::endl << frag_code << std::endl;
    }
    else
    {
        glGetProgramInfoLog(this->shader_program, sizeof(shader_link_info), NULL, shader_link_info);
        std::cout << "链接失败" << std::endl << shader_link_info << std::endl;
        std::cout << "vert_code:" << std::endl << vert_code << std::endl;
        std::cout << "frag_code:" << std::endl << frag_code << std::endl;
        exit(EXIT_SUCCESS);
    }
}


void Shader::use()
{
    glUseProgram(this->shader_program);
}

void Shader::set_uniform_bool(const std::string& bool_name, bool value)
{
    glUniform1i(glGetUniformLocation(this->shader_program, bool_name.c_str()), (int)value);
}
void Shader::set_uniform_int(const std::string& int_name, int value)
{
    glUniform1i(glGetUniformLocation(this->shader_program, int_name.c_str()), value);
}
void Shader::set_uniform_float(const std::string& float_name, float value)
{
    glUniform1f(glGetUniformLocation(this->shader_program, float_name.c_str()), value);
}
void Shader::set_uniform_vec2(const std::string& name, glm::vec2& value)
{
    glUniform2fv(glGetUniformLocation(this->shader_program, name.c_str()), 1,&value[0]);
}
void Shader::set_uniform_vec3(const std::string& name, glm::vec3& value)
{
    glUniform3fv(glGetUniformLocation(this->shader_program, name.c_str()), 1, &value[0]);
}
void Shader::set_uniform_vec4(const std::string& name, glm::vec4& value)
{
    glUniform4fv(glGetUniformLocation(this->shader_program, name.c_str()), 1, &value[0]);
}
void Shader::set_uniform_mat2(const std::string& name, glm::mat2& value)
{
    glUniformMatrix2fv(glGetUniformLocation(this->shader_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::set_uniform_mat3(const std::string& name, glm::mat3& value)
{
    glUniformMatrix3fv(glGetUniformLocation(this->shader_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::set_uniform_mat4(const std::string& name, glm::mat4& value)
{
    glUniformMatrix4fv(glGetUniformLocation(this->shader_program, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

