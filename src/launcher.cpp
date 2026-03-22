#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "constants.h"
#include "mesh.h"
#include "image.h"
#include "text.h"
#include "button.h"
#include "object.h"
#include "camera.h"

static int window_width = WINDOW_WIDTH;
static int window_height = WINDOW_HEIGHT;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	window_width = width;
	window_height = height;

	glViewport(0, 0, width, height);
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
	glfwMakeContextCurrent(window);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (window == NULL || !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){std::cout << "error" << std::endl;glfwTerminate();return -1;}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	double mouseX, mouseY;

	int h = 0;
	
	float pixels = 12.0f;
	float font_size = pixels / window_height;

	Text text(0.2f, 0.2f, 5, 5, font_size);
	text.SetFont("BFont.png");

	Text greettext(0.4f, 0.2f, 25, 10, font_size);
	greettext.SetFont("BFont.png");
	greettext.SetText("This program does not work yet, but probably will. That's all for now");
	greettext.Update();

	Button but(0.2f, 0.6f, 0.6f, 0.2f);
	but.SetCall(
		[&h]()
		{
		h++;
			
		}
	);

	bool click = false;


	Camera cam;

	Object obj;
	obj.Init();

	obj.SetTexture("buttonfill.png");

	obj.AddPoint(Point(-1, 0, 1, 0, 0));
	obj.AddPoint(Point(-1, 0, 0, 0, 1));
	obj.AddPoint(Point( 1, 0, 0, 1, 1));
	obj.AddPoint(Point( 1, 0, 1, 1, 0));

	obj.AddFace(0,1,2);
	obj.AddFace(2,3,0);

	obj.Update();

	while(!glfwWindowShouldClose(window))
	{
		//cam.yaw += 1.f;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		glClearColor(0.5, 0.5, 0.5, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnable(GL_DEPTH_TEST);

		obj.Render(cam.getViewMatrix(), cam.getProjectionMatrix());

		glDisable(GL_DEPTH_TEST);

		text.SetText(std::to_string(h));

		float nx = mouseX / window_width;
		float ny = 1.0f - (mouseY / window_height);

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !click)
		{
			click = true;
			but.Check(nx, ny, cam.getOrthoProjview());
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			click = false;
		}

		text.Update();
		but.Update();

		but.Render(nx, ny, cam.getOrthoProjview());

		text.Render(cam.getOrthoProjview());
		greettext.Render(cam.getOrthoProjview());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
