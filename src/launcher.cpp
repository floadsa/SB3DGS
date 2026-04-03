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

	Scene scene;
	scene.ConvertFromObj("monkey.obj");

	Button RenderMode1Button(-0.99f, 0.99f, 0.25f, 0.07f);
	Button RenderMode2Button(-0.99f, 0.91f, 0.25f, 0.07f);
	Button RenderMode3Button(-0.99f, 0.83f, 0.25f, 0.07f);

	RenderMode1Button.SetText("LINE");
	RenderMode2Button.SetText("GRAY");
	RenderMode3Button.SetText("COLR");


	RenderMode1Button.SetCall(
		[&scene]()
		{
		scene.SetRenderMode(0);
		}
	);

	RenderMode2Button.SetCall(
		[&scene]()
		{
		scene.SetRenderMode(1);
		}
	);

	RenderMode3Button.SetCall(
		[&scene]()
		{
		scene.SetRenderMode(2);
		}
	);


	bool click = false;
   
  for(int i = 0; i < scene.objects.size(); i++)
  std::cout << i << std::endl;
//  scene.objects[i].Dump();


    
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


	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !click)
	{
	click = true; 

	RenderMode1Button.Check();
	RenderMode2Button.Check();
	RenderMode3Button.Check();

	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
	click = false;
	}

	RenderMode1Button.Update(mouseX/((float)width/2)-1, mouseY/((float)height/2)-1);
	RenderMode2Button.Update(mouseX/((float)width/2)-1, mouseY/((float)height/2)-1);
	RenderMode3Button.Update(mouseX/((float)width/2)-1, mouseY/((float)height/2)-1);

	RenderMode1Button.Render();
	RenderMode2Button.Render();
	RenderMode3Button.Render();


//	but.Update(mouseX/((float)width/2)-1, mouseY/((float)height/2)-1);


	glfwSwapBuffers(window);
	glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
