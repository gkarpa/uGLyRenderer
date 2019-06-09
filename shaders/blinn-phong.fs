#version 460 core

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 emissive;
	vec3 transparent;
	float opacity;
	float shininess;
	float shininessStrength;
};

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float kconstant;
	float klinear;
	float kquadratic;
};

uniform Material material;
uniform Light light;
uniform mat4 view;

layout (binding = 0) uniform sampler2D ambientMap;
uniform bool hasAmbientMap;

layout (binding = 1) uniform sampler2D diffuseMap;
uniform bool hasDiffuseMap;

layout (binding = 2) uniform sampler2D specularMap;
uniform bool hasSpecularMap;

layout (binding = 3) uniform sampler2D normalMap;
uniform bool hasNormalMap;

in vec4 vertexColor;
in vec3 vertexNormal;
in float vertexLightDistance;
in vec2 texCoord;
in mat3 TBN;

in vec3 lightDir;
in vec3 viewDir;

out vec4 fragColor;

void main()
{	
	vec3 lightDirection = normalize(lightDir);
	vec3 viewDirection = normalize(viewDir);
	
	vec3 norm;
	if (hasNormalMap)
	{
		norm = texture(normalMap, texCoord).rgb * 2.0 - vec3(1.0);
		norm = normalize(TBN * norm);		
	}
	else
	{
		norm = normalize(vertexNormal);		
	}
	
	float lightAttenuation = 1.0 / (light.kconstant + light.klinear * vertexLightDistance + light.kquadratic * (vertexLightDistance * vertexLightDistance));
	
	float diffuseFactor = max(dot(norm, lightDirection), 0.0);
	vec3 diffuseLight = diffuseFactor * light.diffuse * lightAttenuation;	
	
	vec3 halfwayDirection = normalize(lightDirection + viewDirection);
	float specularFactor = pow(max(dot(norm, halfwayDirection), 0.0), material.shininess);
	vec3 specularLight = specularFactor * material.shininessStrength * light.specular * lightAttenuation;
	
	vec3 ambient = light.ambient * lightAttenuation * material.ambient;
	if (hasAmbientMap)
	{
		ambient = ambient * vec3(texture(ambientMap, texCoord));		
	}
	vec3 diffuse = diffuseLight * material.diffuse;
	if (hasDiffuseMap)
	{
		diffuse = diffuse * vec3(texture(diffuseMap, texCoord));	
	}
	vec3 specular = specularLight * material.specular;
	if (hasSpecularMap)
	{
		specular = specular * texture(specularMap, texCoord).r;
	}	
	fragColor = vec4(ambient + diffuse + specular, 1.0) * vertexColor;	
}