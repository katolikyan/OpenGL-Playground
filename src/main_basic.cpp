#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "../glm/glm.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"


static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
//    glViewport(0, 0, 640, 480);

    // Sinchronizing framerate (aka 60 per sec);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  1.0f, 0.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
     //     4, 5, 6
        0, 1, 2,
        2, 3, 0
    };

    // blending for Alpha channel and .png pics
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;

    VertexBuffer vb(positions, 7 * (3 + 2) * sizeof(float));

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);

    IndexBuffer ib(indices, 3 * 2);

    // screen projection;
//  glEnable(GL_CULL_FACE);
//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LESS);
//  glFrontFace(GL_CCW);
//  glCullFace(GL_BACK);

    
    //shaders
    Shader shader("shaders/basic.glsl");
    shader.Bind();

    Texture texture("resourses/uv2.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);
  

    float r = 0.0f;
    float cam = 0.0f;
    float increment = 0.02f;
    float increment_cam = 0.02f;
    float deg = 0.0f;
    float increment_deg = 1.0f;


    Renderer renderer;

    /* Wireframe mode */
   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.Clear();
        //glViewport(0, 0, 640, 480);


        shader.Bind();
        texture.Bind();

        // trasformations:
        // glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 trans = glm::mat4(1.0f);
//        trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f));
//        trans = glm::rotate(trans, glm::radians(deg), glm::vec3(0.0f, 0.0f, 1.0f));
//        trans = glm::translate(trans, glm::vec3(1.0f, 0.0f, 0.0f));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::mat4 mvp = projection * view * model;

        shader.SetUniformMat4f("u_MVP", mvp);
        //shader.SetUniformMat4f("u_proj", projection);
        //shader.SetUniformMat4f("u_view", view);
        //shader.SetUniformMat4f("u_model", model);


        shader.SetUniform4f("u_Color", r, 0.1, 0.5, 1.0);

        renderer.DrawElements(va, ib, shader);

        // Animation of color;
        if (r > 1.0f)
            increment = -0.02f;
        else if (r < 0.0f)
            increment = 0.02f;
        r += increment;

        // Animation of color;
        if (cam > 5.0f)
            increment_cam = -0.02f;
        else if (cam < 0.0f)
            increment_cam = 0.02f;
        cam += increment_cam;

        // Animation of degree
        if (deg > 180.0f)
            increment_deg = -1.0f;
        else if (deg < 0.0f)
            increment_deg = 1.0f;
        deg += increment_deg;

       /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}