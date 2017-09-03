//
//  test_04.cpp
//  myOpenGL
//
//  Created by an andy on 2017/9/2.
//  Copyright © 2017年 andy. All rights reserved.
//

#include "test_04.hpp"



#include "stb_image.h"//宏处理一次就行了

#include <myShader.h>
#include <myCamera.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// timing
static float deltaTime = 0.0f;
static float lastFrame = 0.0f;

//old setting
static  bool firstMouse = true;
// camera
static Camera camera(glm::vec3(0.0f,0.0f,3.0f));
static float lastX	= SCR_WIDTH / 2.0f;
static float lastY = SCR_HEIGHT / 2.0f;


// --
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    float cameraSpeed = 2.5f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    	camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    	camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    	camera.ProcessKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    	camera.ProcessKeyboard(RIGHT, deltaTime);
}

static void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if(firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

static void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

//model
int do_model_1()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"LearnOpenGL", NULL,NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    Shader ourShaer("res/do_model_1.vs", "res/do_model_1.fs");

    Model ourModel("res/nanosuit/nanosuit.obj");

    while(!glfwWindowShouldClose(window))
    {
    	float currentFrame = glfwGetTime();
    	deltaTime = currentFrame - lastFrame;
    	lastFrame = currentFrame;

    	processInput(window);

    	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    	ourShaer.use();

    	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    	glm::mat4 view = camera.GetViewMatrix();
    	ourShaer.setMat4("projection", projection);
    	ourShaer.setMat4("view", view);

    	glm::mat4 model;

    	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    	ourShaer.setMat4("model", model);
    	ourModel.Draw(ourShaer);


    	glfwSwapBuffers(window);
    	glfwPollEvents();

    }

    glfwTerminate();
    
    return 0;

}

int do_model_2()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,"LearnOpenGL", NULL,NULL);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    Shader ourShaer("res/do_model_2.vs", "res/do_model_2.fs");

    Model ourModel("res/nanosuit/nanosuit.obj");

    //light dir
    glm::vec3 lampPos(1.2f, 1.0f, 2.0f);


    while(!glfwWindowShouldClose(window))
    {
    	float currentFrame = glfwGetTime();
    	deltaTime = currentFrame - lastFrame;
    	lastFrame = currentFrame;

    	processInput(window);

    	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	
    	ourShaer.use();

        // cubeShader.setVec3("material.specular",  0.5f, 0.5f, 0.5f);
        // cubeShader.setFloat("material.shininess", 64.0f);

        // ourShaer.setVec3("dirLight.ambient", 0.1f, 0.1f, 0.1f);
        // ourShaer.setVec3("dirLight.diffuse", 0.8f, 0.8f, 0.8f);
        // ourShaer.setVec3("dirLight.specular", 1.0f, 1.0f, 1.0f);
        // ourShaer.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        // ourShaer.setVec3("viewPos", camera.Position);

    	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
    	glm::mat4 view = camera.GetViewMatrix();
    	ourShaer.setMat4("projection", projection);
    	ourShaer.setMat4("view", view);

    	glm::mat4 model;

    	model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
    	model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    	ourShaer.setMat4("model", model);
    	ourModel.Draw(ourShaer);


    	glfwSwapBuffers(window);
    	glfwPollEvents();

    }

    glfwTerminate();
    
    return 0;

}
	

