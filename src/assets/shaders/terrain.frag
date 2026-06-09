#version 330 core

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
in vec4 SplatWeights;

uniform vec3 viewPos;
uniform Light light;

uniform sampler2D grassTex;
uniform sampler2D rockTex;
uniform sampler2D sandTex;
uniform sampler2D snowTex;
uniform sampler2D swampTex;

void main(){

    vec2 uv = FragPos.xz * 0.05;

    vec3 grass = texture(grassTex, uv).rgb;
    vec3 rock = texture(rockTex, uv).rgb;
    vec3 sand = texture(sandTex, uv).rgb;
    vec3 snow = texture(snowTex, uv).rgb;
    vec3 swamp = texture(swampTex, uv).rgb;

    vec3 albedo = mix(grass, swamp, SplatWeights.a);
    albedo = mix(sand, albedo, SplatWeights.b);
    albedo = mix(albedo, rock, SplatWeights.r);
    albedo = mix(albedo, snow, SplatWeights.g);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    vec3 ambient = light.ambient * albedo;
    
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = light.diffuse * diff * albedo;
    
    float spec = pow(max(dot(norm, halfwayDir),0.0), 16.0);
    vec3 specular = light.specular * spec * 0.05;
    
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result,1.0);

    //FragColor = vec4(norm * 0.5 + 0.5, 1.0);
    
}