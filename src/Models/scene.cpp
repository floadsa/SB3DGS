#include "scene.h"

Scene::Scene()
{
	CurrentCamera = 0;
	RenderMode = 1;
	cameras.push_back(Camera());
}
void Scene::AddObject()
{
	objects.push_back(Object());
	objects.back().Init();
	objects.back().materials.push_back(Material());
	objects.back().SetTexture("fill.png");
}

void Scene::SetRenderMode(int i)
{
	RenderMode = i;
	if(i == 0)
	{
		for(int i = 0; i < objects.size(); i++)
		objects[i].SetShader(LineVlmVxShader, LineVlmFgShader);
	}
	else if(i == 1)
	{
		for(int i = 0; i < objects.size(); i++)
		objects[i].SetShader(VlmVxShader, VlmFgShader);
	}
	else if(i == 2)
	{
		for(int i = 0; i < objects.size(); i++)
		objects[i].SetShader(ColorVlmVxShader, ColorVlmFgShader);
	}
}

void Scene::ConvertFromObj(const char* objfilename)
{
	
	std::ifstream file(objfilename);
	std::string _line;

	if(!file)
	{
		std::cout << "\033[31m" << "Error opening file!" << "\033[0m" << std::endl;
		return;
	}
	else
	{
		std::cout << "\033[0m" << "File was successfully opened " << "\033[32m" << "[OK]" << "\033[0m" << std::endl;
	}

	std::string mtlfilename;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> nvertices;
	std::vector<glm::vec2> tvertices;

	std::vector<std::vector<glm::vec3>> keys;
	keys.resize(200000);
	int counter = 0;
	int positionminus = 0;
	int positioncounter = 0;
	int minus = 0;


while (std::getline(file, _line)) 
{
	std::stringstream line(_line);
    std::string word1;
    line >> word1;

    if(word1 == "mtllib")
    {
	line >> mtlfilename;
	std::cout << "\033[0m" << "MTL file was found: "<< mtlfilename << "\033[32m" << "[OK]" << "\033[0m" << std::endl;
    
    continue;
    }

	if(word1 == "o")
	{
	
    this->AddObject();
    minus = counter;

    positionminus = positioncounter;
    
	continue;
    }
    if(word1 == "usemtl")
    {
    
    std::string _name;
    line >> _name;

    	
    objects.back().AddMaterial(Material(_name));

	std::ifstream mtlfile(mtlfilename);

	if(!mtlfile)
	{
		std::cout << "\033[31m" << "Error opening MTL file!" << "\033[0m" << std::endl;
		return;
	}
	else
	{
	//	std::cout << "\033[0m" << "MTL File was successfully opened " << "\033[32m" << "[OK]" << "\033[0m" << std::endl;
	}

	std::string line_;
	bool current_material = 0;
    
    while (std::getline(mtlfile, line_)) 
    {
  	std::stringstream mtlline(line_);
    std::string mtlword1;
    mtlline >> mtlword1;

    if(mtlword1 == "newmtl")
    {
    std::string word2;
    mtlline >> word2;
    if(_name == word2)
    {
    current_material = 1;
    }
    }   
	if(current_material == 1)
	{
	if(mtlword1 == "Ns")
	{
	float f1;
	mtlline >> f1;
	objects.back().materials.back().shininess = f1;
	}
    if(mtlword1 == "Kd")
    {
	float f1, f2, f3;
	mtlline >> f1 >> f2 >> f3;
    objects.back().materials.back().diffuse = glm::vec3(f1,f2,f3);
    }
    if(mtlword1 == "Ks")
    {
	float f1, f2, f3;
	mtlline >> f1 >> f2 >> f3;
    objects.back().materials.back().specular = glm::vec3(f1,f2,f3);
    break;
    }
    }
    }
    if(!current_material)
    {
     	std::cout << "\033[31m" << "Material was not found!" << "\033[0m" << std::endl;
    }
    else
    {
    // 	std::cout << "\033[0m" << "Material added successfully " << "\033[32m" << "[OK]" << "\033[0m" << std::endl;
    } 
    mtlfile.close();

    }
	if(word1 == "v")
	{
	
	float f1, f2, f3;
	line >> f1 >> f2 >> f3;
	objects.back().AddPoint(glm::vec3(f1, f2, f3));
	
	continue;
	}
	if(word1 == "vn")
	{
	
	float f1, f2, f3;
	line >> f1 >> f2 >> f3;
	nvertices.push_back(glm::vec3(f1, f2, f3));
	
	continue;
	}
	if(word1 == "vt")
	{
	
	float f1, f2;
	line >> f1 >> f2;
	tvertices.push_back(glm::vec2(f1, f2));
	
	continue;
	}
	if(word1 == "f")
	{
	
	std::vector<std::string> words;
    std::string temp;

    while (line >> temp) {words.push_back(temp);}
    
	std::vector<int> n;
	
	for(int i = 0; i < words.size() - 2; i++)
	{
		n.push_back(0);
		n.push_back(1+i);
		n.push_back(2+i);
	}

	std::vector<unsigned int> face;
	
	for(int i = 0; i < n.size(); i++)
	{
		int index[3] = {0};
		std::stringstream st(words[n[i]]);
		char sep;
	
		st >> index[0] >> sep >> index[1] >> sep >> index[2];


		index[0] = index[0] - 1;
		index[1] = index[1] - 1;
		index[2] = index[2] - 1;

		if(positioncounter <= index[0] )
		positioncounter = index[0] + 1;

		int t = 0;
		
		if (index[0] < keys.size())
		{
		for (int j = 0; j < keys[index[0]].size(); j++)
		{
	
		if(glm::vec2(keys[index[0]][j].x, keys[index[0]][j].y) == glm::vec2(index[1], index[2]))
		{
		face.push_back(keys[index[0]][j].z - minus);
		t++; 
		}
		}
		}
		if(t==0)
		{
		keys[index[0]].push_back(glm::vec3(index[1], index[2], counter));
		face.push_back(counter-minus);
		counter++;
		objects.back().AddVertex(Vertex(index[0]- positionminus, tvertices[index[1]].x, tvertices[index[1]].y, nvertices[index[2]].x, nvertices[index[2]].y, nvertices[index[2]].z));
		}
	}
		for (int i = 0; i < face.size() / 3; i++)
		{
		objects.back().faces.push_back(Face(face[i+2*i],face[i+1+2*i],face[i+2+2*i]));
		objects.back().faces.back().material = objects.back().materials.back();
		}
	}
}

    std::cout << "\033[0m" << "Model was successfully converted " << "\033[32m" << "[OK]" << "\033[0m" << std::endl;	
	file.close();
	
}

void Scene::Render()
{
	if(RenderMode == 0)
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for(int i = 0; i < objects.size(); i++)
	objects[i].Render(cameras[CurrentCamera].getViewMatrix(), cameras[CurrentCamera].getProjectionMatrix(), cameras[CurrentCamera]);

	if(RenderMode == 0)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
