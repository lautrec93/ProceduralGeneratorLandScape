#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main(){
    
    float ambientStrength=.1;
    vec3 ambient=ambientStrength*lightColor;
    
    vec3 norm=normalize(Normal);
    vec3 lightdir=normalize(lightPos-FragPos);
    float diff=max(dot(norm,lightdir),0.);
    vec3 diffuse=diff*lightColor;
    
    float specularStrength=.5;
    vec3 viewdir=normalize(viewPos-FragPos);
    vec3 reflectdir=reflect(-lightdir,norm);
    float spec=pow(max(dot(viewdir,reflectdir),0.),32.);
    vec3 specular=spec*lightColor*specularStrength;
    
    vec3 result=(ambient+diffuse+specular)*objectColor;
    //FragColor=vec4(result,1.);
    FragColor=vec4(norm*.5+.5,1.);
    
}