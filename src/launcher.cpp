#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "mesh.h"
#include "image.h"
#include "text.h"
#include "button.h"
#include "scene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
  
}

int Launch()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "SB3DGS", NULL, NULL);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
	glfwSetWindowSizeCallback(window, window_size_callback);  
	glfwMakeContextCurrent(window);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (window == NULL || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){std::cout << "error" << std::endl;glfwTerminate();return -1;}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double mouseX, mouseY;
	int width, height;

	int h = 0;

	Text text(-1, 0.9, 4, 2, 0.1);
	text.SetFont("BFont.png");

	Text greettext(-0.9, 0, 25, 3, 0.06);
	greettext.SetFont("BFont.png");
//	greettext.SetText("This program does not work yet, but probably will. That's all for now");
	greettext.Update();

	Scene scene;
	scene.ConvertFromObj("monkey.obj");

	Button but(-0.7f, 0.90f, 0.6f, 0.2f);
	but.SetCall(
		[&h]()
		{
		h++;
		}
	);

	bool click = false;
   
//  for(int i = 0; i < scene.objects.size(); i++)
//  scene.objects[i].Dump();

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
	float yaww = 0;
	scene.cameras[0].pitch = -30;
	
	while(!glfwWindowShouldClose(window))
	{
//	std::cout << "Window resized: " << width << height << std::endl;
	glfwGetWindowSize(window, &width, &height);

	//This is temporary
	for(int i = 0; i < scene.cameras.size(); i++)
	scene.cameras[i].aspect = (float)width / (float)height;

	
	yaww += 0.4f;
	scene.cameras[0].yaw += 0.4f;
	scene.cameras[0].position.x = 5 *  cosf(yaww * 3.1415 / 180);
	scene.cameras[0].position.z = 5 *  sinf(yaww * 3.1415 / 180);

	glfwGetCursorPos(window, &mouseX, &mouseY);
	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	scene.Render();

	glDisable(GL_DEPTH_TEST);

	text.SetText(std::to_string(h));

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !click)
	{
	click = true; 
	but.Check();
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
	click = false;
	}

	text.Update();
	but.Update(mouseX/((float)width/2)-1, mouseY/((float)height/2)-1);

	but.Render();
	text.Render();
	greettext.Render();

	glfwSwapBuffers(window);
	glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
