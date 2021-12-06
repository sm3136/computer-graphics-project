#version 450 core

// Defines the maximum number of lights
#define MAX_LIGHTS 128

// Base color
uniform vec3 vColor;

// The position of the viewport
uniform vec3 viewPos;

// Ambient color
uniform vec3 ambient;

// Direction and Color of world light
uniform vec3 worldLightColor;
uniform vec3 worldLightDirection;

// Contains the information for the lights
uniform float pointLightCount;
uniform float spotLightCount;

uniform vec3 lightColors[MAX_LIGHTS];
uniform vec3 lightPositions[MAX_LIGHTS];
uniform vec3 coneDirections[MAX_LIGHTS];

// Data on the vertex
in vec3 Position;
in vec3 Normal;

// Outputs the color
out vec4 output_color;

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

// Calculates how the spotlight affects the vector.
vec3 calculateSpotLight(float strength, float cutoffAngle, vec3 coneDirection, vec3 lightDirection, vec3 lightColor)
{
    cutoffAngle = radians(50 - cutoffAngle);

    float spotCos = dot(normalize(-coneDirection), lightDirection);
    float epsilon = (cutoffAngle * 1.114) - cutoffAngle;
    float intensity = clamp((spotCos - (cutoffAngle * 1.114)) / epsilon, 0.0, 1.0);

    strength *= spotCos;

    vec3 viewDir = normalize(Position - viewPos);
    vec3 spotHalfVector = normalize(lightDirection + viewDir);
    
    float spotDiffuse = max(0.0, dot(Normal, lightDirection));
    float spotSpecular = max(0.0, dot(Normal, spotHalfVector));

    spotSpecular = pow(spotSpecular, 32);

    vec3 spotScatteredLight = lightColor * spotDiffuse * (strength / 2);
    vec3 spotReflectedLight = lightColor * spotSpecular * strength;

    return intensity * (spotScatteredLight + spotReflectedLight);
}

// Determines the color for a set fragment.
void main()
{
    // Grabs the position and makes it a local variable. (Incase changes need to be made)
    vec3 frag_position = Position;

    // Handles the infinite world light
    vec3 diffuse = calculateDiffuse(1, worldLightDirection, worldLightColor);
    vec3 specular = calculateSpecular(1, worldLightDirection, frag_position, worldLightColor);

    // Since we have no initial spotlights, lets just make a zero vector.
    vec3 spot = vec3(0, 0, 0);

    // Keeps track of where we are in the lights array.
    int index = 0;

    // Handles all of the spot lights
    for (int i = 0; i < spotLightCount; i++)
    {
        vec3 light_direction = lightPositions[index] - frag_position;
        vec3 unit_light_direction = light_direction / length(light_direction);

        float inv_square = 1 / (length(light_direction) * length(light_direction));

        spot += calculateSpotLight(inv_square, 35, coneDirections[index], unit_light_direction, lightColors[index]);
        index++;
    }

    // After spot lights we want to handle the point lights.
    for (int i = 0; i < pointLightCount; i++) {

        // Gets the light direction and the unit light direction
        vec3 light_direction = lightPositions[index] - frag_position;
        vec3 unit_light_direction = light_direction / length(light_direction);

        // Calculates a good realistic fall off
        float inv_square = 1 / (length(light_direction) * length(light_direction));


        // Adds the diffuse and the specular that way we can apply them to the output color.
        diffuse += calculateDiffuse(inv_square, light_direction, lightColors[index]);
        specular += calculateSpecular(inv_square, unit_light_direction, frag_position, lightColors[index]);

        index++;
    }

    // Gets the output color, we use min in order to make sure no bleeding occurs from over 1 color values.
    output_color = vec4(min((ambient + diffuse + specular + spot) * vColor, vec3(1, 1, 1)), 1.0);
}