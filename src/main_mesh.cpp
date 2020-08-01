#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
#include "Mesh.class.hpp"
#include "ObjLoad.class.hpp"

#include "../glm/glm.hpp"
#include "../glm/ext.hpp"
#include "../glm/gtx/string_cast.hpp"
#include "../glm/gtx/transform.hpp"
#include "../glm/gtc/matrix_transform.hpp"

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

    // Move camera
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
    // Swap lock mode
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        cam.SwapLock();
        // unlock/lock mouse
        if (cam.IsLocked())
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        else
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    // Reset view
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cam.SetLookAt(glm::vec3(0.0f, 0.0f, 3.0f), \
                      glm::vec3(0.0f, 0.0f, -1.0f), \
                      glm::vec3(0.0f, 1.0f, 0.0f));
    }
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
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Sinchronizing framerate;
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "error" << std::endl;

    std::vector<Vertex> verts;
    std::vector<unsigned int> indxs;
    std::vector<MeshTexture> txts;

    verts.push_back({glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)});
    verts.push_back({glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)});
    verts.push_back({glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)});
    verts.push_back({glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)});

    indxs.push_back(0);
    indxs.push_back(1);
    indxs.push_back(2);
    indxs.push_back(2);
    indxs.push_back(3);
    indxs.push_back(0);

    Mesh testmesh(verts, indxs, txts);

    ObjLoad testobj("resourses/testCube.obj");
    ObjLoad testobj2("resourses/testTeapot.obj");
    Mesh testCube(testobj.GetVertices());
    Mesh testTeapot(testobj2.GetVertices());
    // blending for Alpha channel and .png pics
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //shaders
    Shader shader("shaders/basic_mesh.glsl");
    shader.Bind();

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
    //glDepthFunc(GL_LESS);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);

    Camera cam01(1000.0f, 1000.0f);

    // loop parameters
    float deltaTime = 0.0f;
    float lastFrameTime = 0.0f;
    float crntTime = 0.0f;
    int width, height;
    double xmousepos, ymousepos;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        // thacking changes of window size;
        glfwGetWindowSize(window, &width, &height);
        // tracking moush position;
        glfwGetCursorPos(window, &xmousepos, &ymousepos);

        // Clearing with color
        renderer.Clear();
        renderer.ClearColor(0.12f, 0.12f, 0.12f, 1.0f);
        renderer.Clear((unsigned int []){GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT}, 2);

        // Projection and shader camera binding.
        shader.Bind();
        glm::mat4 model(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));  
        glm::mat4 proj;
        proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
        shader.SetUniformMat4f("u_MVP", proj * cam01.GetView() * model);
        //shader.SetUniform4f("u_Color", r, 0.1, 0.5, 1.0);

        // Rendering
        //renderer.DrawElements(testmesh, shader);
        testmesh.Draw(shader);
        testCube.Draw(shader);
        testTeapot.Draw(shader);


        // Animation of color;
        if (r > 1.0f)
            increment = -0.02f;
        else if (r < 0.0f)
            increment = 0.02f;
        r += increment;

        // Input and Camera movement:
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