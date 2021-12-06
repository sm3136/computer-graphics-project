#version 450 core

in layout (location = 0) vec3 vPosition;
in layout (location = 2) vec3 vNormal;

// Used in calculating the points position
uniform mat4 modelTransMatrix;
uniform mat4 projectionMatrix;

// Outputs the data on the vertex post modification
out vec3 Position;
out vec3 Normal;

// Runs the shader
void main()
{
    // Position
    vec4 modelPosition = modelTransMatrix * vec4(vPosition, 1.0);
    gl_Position = projectionMatrix * modelPosition;
    
    // Converts the position to a vec3
    Position = vec3(modelPosition.x, modelPosition.y, modelPosition.z);

    // Updates the normal relative to the position
    Normal = normalize(mat3(transpose(inverse(modelTransMatrix))) * vNormal);
}
