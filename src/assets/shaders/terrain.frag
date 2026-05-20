#version 330 core

struct Material{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 UVCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;


void main(){
    
    vec3 ambient = light.ambient * texture(material.diffuse, UVCoords).rgb;
    
    vec3 norm = normalize(Normal);
    vec3 lightdir = normalize(-light.direction);
    float diff = max(dot(norm,lightdir),0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, UVCoords).rgb;
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(norm, -lightdir);
    float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);

    //FragColor = vec4(norm * 0.5 + 0.5, 1.0);
    
}