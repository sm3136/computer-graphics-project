#version 430 core

#define MAX_LIGHTS 128

in layout (location = 0) vec3 vPosition;
in layout (location = 2) vec3 vNormal;
uniform vec3 vColor;

// Used in calculating the points position
uniform mat4 modelTransMatrix;
uniform mat4 projectionMatrix;

// The position of the viewport
uniform vec3 viewPos;

// Direction and Color of world light
uniform vec3 worldLightColor;
uniform vec3 worldLightDirection;

// Ambient color
uniform vec3 ambient;

// Contains the information for the lights
uniform float lightCount;
uniform vec3 lightColors[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];

out vec3 Color;
out vec3 Normal;

// Calculates the specular impact of the given light.
vec3 calculateSpecular(float strength, vec3 lightDir, vec3 position, vec3 lightColor)
{    
    vec3 viewDir = normalize(viewPos - position);
    vec3 reflectDir = reflect(-lightDir, Normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
    vec3 specular = strength * spec * lightColor;

    return specular;
}

// Calculates the diffuse impact of the given light.
vec3 calculateDiffuse(float strength, vec3 lightDirection, vec3 lightColor)
{
    float diff = max(dot(Normal, lightDirection), 0.0);
    return strength * diff * lightColor;
}

// Runs the shader
void main()
{
    // Position
    vec4 v = vec4(vPosition, 1.0f);
    vec4 modelPosition = modelTransMatrix * v;
    gl_Position = projectionMatrix * modelPosition;
    
    // Converts the position to a vec3
    vec3 position = vec3(modelPosition.x, modelPosition.y, modelPosition.z);

    // Color
    Normal = normalize(mat3(transpose(inverse(modelTransMatrix))) * vNormal);

    // Handles the infinite world light
    vec3 diffuse = calculateDiffuse(1, worldLightDirection, worldLightColor);
    vec3 specular = calculateSpecular(1, worldLightDirection, position, worldLightColor);
    
    // Handles all of the point lights
    for (int i = 0; i < lightCount; i++) {
        vec3 light_direction = lightPositions[i] - position;
        vec3 unit_light_direction = light_direction / length(light_direction);

        float inv_square = 1 / (length(light_direction) * length(light_direction));

        diffuse += calculateDiffuse(inv_square, light_direction, lightColors[i]);
        specular += calculateSpecular(inv_square / 2, unit_light_direction, position, lightColors[i]);
    }

    Color = (ambient + diffuse + specular) * vColor;
}
