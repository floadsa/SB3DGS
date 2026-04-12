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
	scene.ConvertFromObj("test.obj");

	UIScene UIscene;
	UIscene.AddObject(new Button(10, 10, 200, 50));

	Button* test = dynamic_cast<Button*>(UIscene.objects[0]);
	test->SetText("Line mode");
	test->SetCall(
			[&scene]()
			{
			scene.SetRenderMode(0);
			}
		);

	UIscene.AddObject(new Button(10, 70, 200, 50));

	test = dynamic_cast<Button*>(UIscene.objects[1]);
	test->SetText("Color mode");
	test->SetCall(
			[&scene]()
			{
			scene.SetRenderMode(2);
			}
		);

	UIscene.AddObject(new Button(10, 130, 200, 50));

	test = dynamic_cast<Button*>(UIscene.objects[2]);
	test->SetText("Test button");
	test->SetCall(
			[&scene]()
			{
			for(int i = 0; i < scene.objects.size(); i++)
				scene.objects[i].dirtmesh = true;
			}
		);

	glfwSetWindowUserPointer(window, &UIscene);


	float distance = 5;
	glm::vec3 target = glm::vec3(0,0,0);
	double lastX, lastY;
	bool rotating = false;
	bool click = false;
    

	while(!glfwWindowShouldClose(window))
	{	

	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &mouseX, &mouseY);

	for(int i = 0; i < scene.cameras.size(); i++)
	scene.cameras[i].aspect = (float)width / (float)height;
	
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
	{
	if (!rotating){rotating = true; lastX = mouseX; lastY = mouseY;}
	
	double dx = mouseX - lastX;
	double dy = mouseY - lastY;
	
	lastX = mouseX;
	lastY = mouseY;
	
	float sensitivity = 0.005f;
	
	scene.cameras[0].yaw   += dx * sensitivity;
	scene.cameras[0].pitch += dy * sensitivity;

	float yaw   = scene.cameras[0].yaw;
	float pitch = scene.cameras[0].pitch;
	float dist  = distance;
	
	scene.cameras[0].position.x = target.x + dist * cos(pitch) * sin(-yaw);
	scene.cameras[0].position.y = target.y + dist * sin(pitch);
	scene.cameras[0].position.z = target.z + dist * cos(pitch) * cos(-yaw);
	
	}
	else
	{
	rotating = false;
	}

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
