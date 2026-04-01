#pragma once

inline const char* CmnVxShader = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aUV;
out vec2 fragUV;
void main() {
	fragUV = aUV;
    gl_Position = vec4(aPos, 1);
}
)";

inline const char* CmnFgShader = R"(
#version 330 core
out vec4 FragColor;
in vec2 fragUV;
uniform sampler2D tex;
void main() {
    FragColor = texture(tex, fragUV);;
}
)";


inline const char *VlmVxShader =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec2 aUV;\n"
"layout (location = 2) in vec3 aNormal;\n"
"out vec3 fragNormal;\n"
"out vec2 fragUV;\n"
"out vec3 fragPos;\n"
"uniform mat4 proj;\n"
"uniform mat4 view;\n"
"void main()\n"
"{\n"
"    fragUV = aUV;\n"
"    fragNormal = aNormal;\n"
"    gl_Position = proj * view * vec4(aPos, 1.0);\n"
"}\n";


inline const char *VlmFgShader =
"#version 330 core\n"
"#define MAX_LIGHTS 16\n"
"out vec4 FragColor;\n"
"in vec2 fragUV;\n"
"in vec3 fragNormal;\n"
"in vec3 fragPos;\n"
"uniform vec4 diffuse;\n"
"uniform vec3 specular;\n"
"uniform float shininess;\n"
"uniform vec3 viewPos;\n"
"uniform vec3 lightDir[MAX_LIGHTS];\n"
"uniform vec3 lightColor[MAX_LIGHTS];\n"
"uniform sampler2D tex;\n"
"void main()\n"
"{\n"
"   vec3 norm = normalize(fragNormal);\n"
"   vec3 texColor = texture(tex, fragUV).rgb;\n"
"   vec3 baseColor = texColor * diffuse.rgb;\n"
"   vec3 result = vec3(0.0);\n"
"   for (int i = 0; i < MAX_LIGHTS; ++i)\n"
"   {\n"
"       vec3 lDir = normalize(lightDir[i]);\n"
"       float diff = max(dot(norm, lDir), 0.0);\n"
"       vec3 diffuseComp = baseColor * diff * lightColor[i];\n"
"       result += diffuseComp;\n"
"   }\n"
"   FragColor = vec4(result, diffuse.a);\n"
"}\n";

//"   float diff = abs(dot(norm, normalize(lightDir)));\n"
//"   vec3 result = baseColor * diff;\n"
