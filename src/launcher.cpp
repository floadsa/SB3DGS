#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "mesh.h"
#include "image.h"
#include "text.h"
#include "button.h"
#include "editbox.h"
#include "scene.h"
#include "UIscene.h"
#include "uibuilder.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
glViewport(0, 0, width, height);
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
UIScene* uiscene = static_cast<UIScene*>(glfwGetWindowUserPointer(window));
uiscene->UpdateSize(width, height); 	
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

UIScene* uiscene = static_cast<UIScene*>(glfwGetWindowUserPointer(window));
if (action == GLFW_PRESS)
{
	uiscene->anykeypressed = true;
	uiscene->lastkey = key;
}
if (action == GLFW_RELEASE)
{
	uiscene->anykeypressed = false;
}

}

void char_callback(GLFWwindow* window, unsigned int codepoint)
{
UIScene* uiscene = static_cast<UIScene*>(glfwGetWindowUserPointer(window));
uiscene->lastchar = codepoint;
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
glfwSetKeyCallback(window, key_callback);
glfwSetCharCallback(window, char_callback);
glfwMakeContextCurrent(window);
//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

if (window == NULL || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){std::cout << "error" << std::endl;glfwTerminate();return -1;}

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

double mouseX, mouseY;
int width, height;

//TEMP
float distance = 5;
glm::vec3 target = glm::vec3(0,0,0);
double lastX, lastY;
bool rotating = false;
//
	
bool click = false;
int delay = 0;
int templastkey = 0;

Scene scene;
scene.ConvertFromObj("monkey.obj");

UIScene UIscene;
glfwSetWindowUserPointer(window, &UIscene);

BuildUI(UIscene, scene);

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
UIscene.Render();
	
if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !click)
{
	click = true; 
	UIscene.Click();
}
if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
{
	click = false;
}

if(templastkey != UIscene.lastkey)
{
	templastkey = UIscene.lastkey;
	delay = 0;
}
if(UIscene.anykeypressed && delay == 0)
{
	UIscene.Press();
	delay = 20;
}
if(delay > 0)
delay--;

glfwSwapBuffers(window);
glfwPollEvents();
}

glfwTerminate();
return 0;
}
