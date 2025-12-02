#version 460 core

#define MAX_LIGHTS 1
#define SPECULAR_FACTOR 100
#define AMBIENT_FACTOR 0.3f

struct PointLight{
    vec3 pos;
    vec3 emission;
    float I;
};

in vec3 fragPos;
in vec3 fragNormal;
in vec2 TexCoords;

uniform sampler2D image;
uniform float tiling;
uniform PointLight[MAX_LIGHTS] lights;
uniform int nLights;
uniform vec3 diffuse;
uniform float alpha;
uniform float shiny;
uniform vec3 camPos;
uniform int LOD;

out vec4 fragColor;

vec3 calculateFragColor(vec4 base){
    vec3 result = AMBIENT_FACTOR * base.xyz;
    // apply diffuse and specular changes for each light affecting the object.
    for(int i = 0; i < nLights; i++){
        PointLight light = lights[i];
        // diffuse:
        vec3 lightDir = normalize(light.pos - fragPos);
        // calculate distance between light src and obj.
        float dist = distance(light.pos, fragPos);
        //
        result += (light.emission * base.xyz * max(0, dot(fragNormal, lightDir)) * light.I) / (dist);

        // specular:
        vec3 view = normalize(camPos - fragPos);
        vec3 vHalf = normalize(lightDir + view);
        result += (light.emission * base.xyz * pow(max(0, dot(fragNormal, vHalf)), shiny * SPECULAR_FACTOR) * light.I) / (dist);
    }
    return result;
}

void main()
{
    if(LOD == 0) {
        vec4 base_color = AMBIENT_FACTOR * vec4(diffuse.xyz, alpha) * texture(image, TexCoords * tiling);
        fragColor = vec4(base_color.xyz, alpha) ;
        return;
    }

    fragColor = vec4(calculateFragColor(vec4(diffuse, 1.0)).xyz, alpha) * texture(image, TexCoords * tiling);
}
