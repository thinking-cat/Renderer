#version 330 core

layout(location = 0) in vec2 pos;

void main(){
    gl_PointSize = 5.0f;
    gl_Position = vec4(pos.x, pos.y, 0.0f, 1.0f);
}