#version 430 core
struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light {
    vec3 light_dir;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform vec3 camera_pos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;
uniform vec3 light_dir;
uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform vec3 fcolor;

out vec4 color;

vec3 colorResult(vec3 normal,vec3 viewDir,Light light);

void main()
{
    // Diffuse
    vec3 result;
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camera_pos - Position);
    Light light;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.light_dir = normalize(light_dir);
    result = colorResult(norm,viewDir,light);
    color = vec4(result,1.0f);
}

vec3 colorResult(vec3 normal,vec3 viewDir,Light light)
{
    // Diffuse shading
    float diff = max(dot(normal, -light.light_dir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(light.light_dir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),shininess);
    // Combine results
    vec3 myambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
    vec3 mydiffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    vec3 myspecular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

    return (myambient+mydiffuse+myspecular);
}
