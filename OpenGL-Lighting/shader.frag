#version 330

struct Material
{
    float ambient;
    float shininess;
    float diffuse;
    float specular;
};

struct Light {
    vec3 position;
    vec3 direction;
    float strength;
    float fallOffStart;
    float fallOffEnd;
    float spotPower;
    int isDirectional;
    int isPoint;
    int isSpot;
};

in vec2 TexCoord;
in vec3 posWorld;
in vec3 normalWorld;

out vec4 colour;

uniform sampler2D theTexture;
uniform bool useTexture;
uniform vec3 eyePosition;
uniform Material material;
uniform Light light;

float calcAttenuation(float d, float falloffStart, float falloffEnd)
{
    // Linear falloff
    return clamp((falloffEnd - d) / (falloffEnd - falloffStart), 0.0, 1.0);
}

vec3 blinnPhong(vec3 lightStrength, vec3 lightVec, vec3 normal, vec3 toEye, Material material)
{
    vec3 halfway = normalize(toEye + lightVec);
    float hdotn = dot(halfway, normal);
    vec3 specular = vec3(material.specular) * pow(max(hdotn, 0.0f), material.shininess);
    return material.ambient + (vec3(material.diffuse) + specular) * lightStrength;
}

vec3 computeDirectionalLight(Light light, Material material, vec3 normal, vec3 toEye)
{
    vec3 lightVec = light.direction;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    vec3 lightStrength = vec3(light.strength) * ndotl;
    
    return blinnPhong(lightStrength, lightVec, normal, toEye, material);
}

vec3 computePointLight(Light light, Material material, vec3 pos, vec3 normal, vec3 toEye)
{
    vec3 lightVec = light.position - pos;

    float d = length(lightVec);

    if (d > light.fallOffEnd)
    {
        return vec3(0.0);
    }
    else
    {
        lightVec /= d;
        
        float ndotl = max(dot(lightVec, normal), 0.0f);
        vec3 lightStrength = vec3(light.strength) * ndotl;
        
        float att = calcAttenuation(d, light.fallOffStart, light.fallOffEnd);
        lightStrength *= att;
        
        return blinnPhong(lightStrength, lightVec, normal, toEye, material);
    }
}

vec3 computeSpotLight(Light light, Material material, vec3 pos, vec3 normal, vec3 toEye)
{
    vec3 lightVec = light.position - pos;

    float d = length(lightVec);

    if (d > light.fallOffEnd)
    {
        return vec3(0.0f);
    }
    else
    {
        lightVec /= d;
        
        float ndotl = max(dot(lightVec, normal), 0.0f);
        vec3 lightStrength = vec3(light.strength) * ndotl;
        
        float att = calcAttenuation(d, light.fallOffStart, light.fallOffEnd);
        lightStrength *= att;
        
        float spotFactor = pow(max(dot(lightVec, light.direction), 0.0f), light.spotPower);
        lightStrength *= spotFactor;
        
        return blinnPhong(lightStrength, lightVec, normal, toEye, material);
    }
}

void main()
{
	vec3 toEye = normalize(eyePosition - posWorld);

	vec3 res = vec3(0.0);

    res += computeDirectionalLight(light, material, normalWorld, toEye) * light.isDirectional;
    
    res += computePointLight(light, material, posWorld, normalWorld, toEye) * light.isPoint;
    
    res += computeSpotLight(light, material, posWorld, normalWorld, toEye) * light.isSpot;

	colour = useTexture ? vec4(res, 1.0) * texture(theTexture, TexCoord) : vec4(res, 1.0);
}