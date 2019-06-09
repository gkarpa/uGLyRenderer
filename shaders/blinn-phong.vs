#version 460 core

uniform mat4 model;
uniform mat4 modelViewProjection;
uniform mat4 modelView;
uniform mat4 view;
uniform mat3 normalMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 textureCoordinate;
layout (location = 4) in vec3 tangent;
layout (location = 5) in vec3 bitangent;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float kconstant;
	float klinear;
	float kquadratic;
};

uniform Light light;


out vec4 vertexColor;
out vec3 vertexNormal;
out float vertexLightDistance;
out vec2 texCoord;
out mat3 TBN;
out vec3 lightDir;
out vec3 viewDir;

void main()
{
	vertexColor = color;
	vertexNormal = normalize(normalMatrix * normal);
	vec3 vertexModelViewPos = vec3(modelView * vec4(position, 1.0));
	gl_Position = modelViewProjection * vec4(position, 1.0);
	texCoord = textureCoordinate;
	
	vec3 T = normalize(normalMatrix * tangent);
	vec3 B = normalize(normalMatrix * bitangent);
	TBN = mat3(T, B, vertexNormal);
	
	vec3 lightPos = vec3(view * vec4(light.position, 1.0));
	vertexLightDistance = length(lightPos - vertexModelViewPos);
	lightDir = normalize(lightPos - vertexModelViewPos);
	viewDir = normalize(-vertexModelViewPos);
}