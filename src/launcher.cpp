#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "mesh.h"
#include "image.h"
#include "text.h"
#include "button.h"
#include "scene.h"
#include "UIscene.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
  	UIScene* uiscene = static_cast<UIScene*>(glfwGetWindowUserPointer(window));

  	if(uiscene)
  	{
  		uiscene->UpdateSize(width, height);
  	}
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

	UIScene UIscene;
	UIscene.AddObject(new Button(10, 10, 200, 50));

	Button* test = dynamic_cast<Button*>(UIscene.objects[0]);
	test->SetText("Hello button");
	test->SetCall(
			[&scene]()
			{
			scene.SetRenderMode(0);
			}
		);

	UIscene.AddObject(new Button(10, 70, 200, 50));

	test = dynamic_cast<Button*>(UIscene.objects[1]);
	test->SetText("Test text");
	test->SetCall(
			[&scene]()
			{
			scene.SetRenderMode(1);
			}
		);

	UIscene.AddObject(new Button(10, 130, 400, 100));

	test = dynamic_cast<Button*>(UIscene.objects[2]);
	test->SetCall(
			[&scene]()
			{
			scene.SetRenderMode(2);
			}
		);


	UIscene.AddObject(new Text(10, 500, 15, 3, 50, "Test"));
	Text* testtext = dynamic_cast<Text*>(UIscene.objects[3]);
	
	glfwSetWindowUserPointer(window, &UIscene);
	
	bool click = false;
    
	float yaww = 0;
	scene.cameras[0].pitch = -30;
	
	while(!glfwWindowShouldClose(window))
	{
	
	testtext->SetText(std::to_string(mouseX));

	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &mouseX, &mouseY);

	//This is temporary
	for(int i = 0; i < scene.cameras.size(); i++)
	scene.cameras[i].aspect = (float)width / (float)height;

	yaww += 0.4f;
	scene.cameras[0].yaw += 0.4f;
	scene.cameras[0].position.x = 5 *  cosf(yaww * 3.1415 / 180);
	scene.cameras[0].position.z = 5 *  sinf(yaww * 3.1415 / 180);
	//////////////////

	glClearColor(0.5, 0.5, 0.5, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	
	scene.Render();

	glDisable(GL_DEPTH_TEST);

	UIscene.Update(mouseX, mouseY);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	UIscene.Render();
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !click)
	{
	click = true; 
	UIscene.Check();
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
	click = false;
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
