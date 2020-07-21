#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_MVP;
uniform mat4 u_proj;
uniform mat4 u_view;
uniform mat4 u_model;

void main() {
  gl_Position = u_MVP * vec4(position, 1.0);
  //gl_Position = u_proj * u_view * u_model * vec4(position, 1.0f);
 // gl_Position = vec4(position, 1.0f);
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main() {
  color = u_Color; 
}