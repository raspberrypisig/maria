#version 330

// Input vertex attributes
in vec3 vertexPosition; 
in vec2 vertexTexCoord;
in vec4 vertexColor; 

// Input uniform values
uniform mat4 mvp;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord; //uv
out vec4 fragColor; //gl_FragColor


void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    gl_Position = mvp*vec4(vertexPosition, 1.0);
}