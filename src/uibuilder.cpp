#include "UIscene.h"
#include "scene.h"

void BuildUI(UIScene& UIscene, Scene& scene)
{
//TEMPORARY FOR TESTING UI

UIscene.AddObject(new Button(10, 10, 200, 50));
Button* test = dynamic_cast<Button*>(UIscene.objects[0]);
test->SetText("Line mode");
test->SetCall
(
	[&scene]()
	{
		scene.SetRenderMode(0);
	}
);

UIscene.AddObject(new Button(10, 70, 200, 50));
test = dynamic_cast<Button*>(UIscene.objects[1]);
test->SetText("Color mode");
test->SetCall
(
	[&scene]()
	{
		scene.SetRenderMode(2);
		
		for(int i = 0; i < scene.objects.size(); i++)
		scene.objects[0].SetPosition(0, 0, 0);
	}
);

UIscene.AddObject(new Button(10, 130, 200, 50));

test = dynamic_cast<Button*>(UIscene.objects[2]);
test->SetText("Test button");
test->SetSnap(1);
test->SetCall
(
	[&scene]()
	{
		for(int i = 0; i < scene.objects.size(); i++)
		{
			scene.objects[i].SetPosition(1, 0, 0);
		}
	}
);

UIscene.AddObject(new EditBox(10, 190, 200, 50));
EditBox* a = dynamic_cast<EditBox*>(UIscene.objects[3]);
a->SetGetFunc
(
	[&scene]() 
	{
	    return std::to_string(scene.objects[0].points[0].x);
	}
);
	
a->SetSetFunc
(
[&scene](const std::string& value) 
{

	try 
	{
		float number = std::stof(value);
		scene.objects[0].points[0].x = number;
		scene.objects[0].dirtmesh = true;
	} 
	catch (const std::invalid_argument& e) 
	{
		std::cout << "\033[31m" << "argument is not a number!\n" << "\033[0m" << std::endl;
	} 
	catch (const std::out_of_range& e) 
	{
		std::cout << "\033[31m" << "number is out of range!" << "\033[0m" << std::endl;
	}
}

);

}
