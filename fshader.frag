#version 330

//in vec3 myColor;

out vec4 fragColor;
in vec2 myTexCoord;

uniform sampler2D texture0;

void main(){
    //fragColor = vec4(myColor, 1.0);
    fragColor = texture(texture0, myTexCoord);
}
