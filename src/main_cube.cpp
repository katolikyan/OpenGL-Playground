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

#include "Mat4.class.hpp"
#include "Vec3.class.hpp"
#include "Camera.class.hpp"

#include "../glm/glm.hpp"
#include "../glm/ext.hpp"
#include "../glm/gtx/string_cast.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"
/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
};
*/

static void processMouse(GLFWwindow *window, Camera &cam, double xpos, double ypos) {
    static float xprev = 1000.0f / 2.0f;
    static float yprev = 1000.0f / 2.0f;
    static bool  firstrun = 1;

    if (cam.IsLocked()) {
        firstrun = 1;
        return ;
    }

    if (firstrun) {
        xprev = xpos;
        yprev = ypos;
        firstrun = 0;
    }

    float xoffset = xpos - xprev;
    float yoffset = yprev - ypos;
    xprev = xpos;
    yprev = ypos;
    cam.MoveViewDirection(xoffset, yoffset);
}

void processInput(GLFWwindow *window, Camera &cam, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (!cam.IsLocked()) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cam.MoveForward(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cam.MoveBack(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cam.MoveLeft(deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cam.MoveRight(deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        cam.SwapLock();
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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



    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Sinchronizing framerate (aka 60 per sec);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;

    float positions[] = {
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 
        -0.5f,  0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f, 1.0f, 0.0f
    };

    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int v_ind[] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,
        1, 2, 6, 
        1, 6, 5, 
        6, 5, 4, 
        6, 7, 4,
        7, 3, 4, 
        3, 4, 0, 
        2, 6, 3, 
        6, 3, 7, 
        5, 1, 4, 
        1, 4, 0
    };

    glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
    };

    // blending for Alpha channel and .png pics
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    VertexArray va;
    VertexBuffer vb(vertices, 5 * 36 * sizeof(float));
    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    va.AddBuffer(vb, layout);
    IndexBuffer ib(indices, 3 * 12);

    // screen projection;

// -----------
   // glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f / 480.9f, 0.1f, 100.0f);
  //  glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
  //  glm::mat4 model = glm::mat4(1.0f);
// -----------


    //glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f);
 //   glm::mat4 mvp = /* proj * view  */ model;

    
    //shaders
    Shader shader("shaders/basic.glsl");
    shader.Bind();

//    shader.SetUniformMat4f("u_MVP", mvp);
 //   va.Unbind();
 //   vb.Unbind();
  //  ib.Unbind();
  //  shader.Unbind();

    Texture texture("resourses/box.png");
    texture.Bind();
    shader.SetUniform1i("u_Texture", 0);

    float r = 0.0f;
    float increment = 0.02f;
    float cam = 0.0f;
    float increment_cam = 0.02f;

    Renderer renderer;
    glEnable(GL_DEPTH_TEST);  
    //glEnable(GL_CULL_FACE);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);

    Camera cam01(1000.0f, 1000.0f);
    
    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    float crntTime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        double xmousepos, ymousepos;
        glfwGetCursorPos(window, &xmousepos, &ymousepos);

        /* Render here */
        renderer.Clear();
        renderer.ClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        renderer.Clear((unsigned int []){GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT}, 2);
        // glViewport(0, 0, 1000 * 2, 1000 * 2);

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.1, 0.5, 1.0);

//        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f / 480.9f, 0.1f, 100.0f);
        //glm::mat4 view = glm::lookAt(glm::vec3(cam, 0, -35), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
//        glm::mat4 view = glm::mat4(1.0f);
  //      view = glm::translate(view, glm::vec3(cam ,0.0f, -25.0f));
 //       glm::mat4 mvp = proj * view * model;

/*
        glm::mat4 mvp = glm::mat4(1.0f);
        glm::mat4 scl = glm::mat4(1.0f);
        glm::mat4 rot = glm::mat4(1.0f);
        glm::mat4 trns = glm::mat4(1.0f);
        scl = glm::scale(scl, glm::vec3(0.5f, 0.5f, 0.5f));
        rot = glm::rotate(rot, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        rot = glm::rotate(rot, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        trns = glm::translate(trns, glm::vec3(0.0f, 0.0f, -10.0));
        mvp = trns * rot * scl;
        //mvp = rot * scl;

        glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
        //// test
        Mat4 t_scale(1.0f);
        Mat4 t_rotate(1.0f);
        Mat4 t_translate(1.0f);
        Mat4 t_mvp(1.0f);
        t_scale.SetScale(0.5f, 0.5f, 0.5f);
        t_rotate.Rotate(45.0f, 45.0f, 0.0f);
        t_translate.SetTranslate(0.2f, 0.2f, 0.0f);
        t_mvp = t_translate * t_rotate * t_scale;
        ///  test
        */

        glm::mat4 model(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glm::mat4 proj;
        proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

        float radius = 10.0f;
        
       /*
        view = glm::lookAt(glm::vec3(sin(glfwGetTime()) * radius, 0.0f, cos(glfwGetTime()) * radius),
                           glm::vec3(0.0f, 0.0f, 0.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));
        cam01.SetLookAt(glm::vec3(sin(glfwGetTime()) * radius, 0.0f, cos(glfwGetTime()) * radius),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 1.0f, 0.0f));
       */

        //shader.SetUniformMat4f("u_MVP", t_translate * t_rotate * t_scale);
        //shader.SetUniformMat4f("u_MVP", proj * view * model);

        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i; 
            if (i % 3 == 0)
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
            else
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.SetUniformMat4f("u_MVP", proj * cam01.GetView() * model);
            renderer.DrawArrays(va, shader, 36);
        }

 //       renderer.Draw(va, ib, shader);
        //renderer.DrawArrays(va, shader, 36);

        // Animation of color;
        if (r > 1.0f)
            increment = -0.02f;
        else if (r < 0.0f)
            increment = 0.02f;
        r += increment;

        // Animation of color;
        if (cam > 4.0f)
            increment_cam = -0.02f;
        else if (cam < 0.0f)
            increment_cam = 0.02f;
        cam += increment_cam;

        // camera movement:
        crntTime = glfwGetTime();
        deltaTime = crntTime - lastFrameTime;
        lastFrameTime = crntTime;
        processInput(window, cam01, deltaTime);
        processMouse(window, cam01, xmousepos, ymousepos);

        glViewport(0, 0, width * 2, height * 2);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}