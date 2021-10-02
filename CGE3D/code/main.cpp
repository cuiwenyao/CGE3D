#pragma once
#include "Global_config.h"
#include "component/Window.h"
#include "global_valuable/Global_valuable.h"
#include "element/shader.h"
#include "element/mesh.h"
#include "parse/model_parse.h"
#include "../code/element/texture.h"
#include "element/object.h"
#include "element/camera.h"
int main()
{
    const char vert_path[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/glsl/shader.vert";
    const char frag_path[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/glsl/shader.frag";
    const char vert_path_2[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/glsl/shader_2.vert";
    const char frag_path_2[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/glsl/shader_2.frag";

    const char model_path_1[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/resource/model/stormtrooper/stormtrooper.obj";
    const char model_path_2[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/resource/model/nanosuit/nanosuit.obj";
    const char model_path_3[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/resource/model/cyborg/cyborg.obj";
    const char model_path_4[100] = "C:/Users/admin/source/repos/CGE3D/CGE3D/code/resource/model/backpack/backpack.obj";
    
    Window* window = new Window("mywindow1", 800, 600, WINDOW_MODE_WINDOWED);
    Scene* scene = new Scene();
    Model* model = new Model(model_path_2);
    Shader* shader1 = new Shader(vert_path, frag_path);
    Shader* shader2 = new Shader(vert_path_2, frag_path_2);

    window->attach_scene(scene);
    scene->add_camera(new Camera, NULL);

    for (int i = 0; i <= 10; i++)
    {
        for (int j = 0; j <= 10; j++)
        {
            Object* object = new Object("myobjct", model);
            if ((i + j) % 2)
            {
                object->attach_shader(shader1);
            }
            else
            {
                object->attach_shader(shader2);
                object->change_size(1);
            }
            object->move_to(glm::vec3(-100+i*20, -100 + j * 20, 0));
            scene->add_object(object, NULL);
        }
    }

    //object1->print_info();
    
    window->draw();
    
    return 0;
}
