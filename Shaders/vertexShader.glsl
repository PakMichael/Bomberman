

#version 330 core
layout (location = 0) in vec3 position;

  

out vec4 vertexColor;


 uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
    gl_Position = projection * view * transform * vec4(position, 1.0f);

} 


 


 