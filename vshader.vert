#version 330
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTex;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;

out vec2 myTexCoord;
//out vec3 myColor;

void main(){
    gl_Position = vec4(aPos, 1.0);
    //myColor = aColor;
    myTexCoord = aTex;
}
