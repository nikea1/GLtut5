#version 330

in vec3 myColor;

out vec4 fragColor;
in vec2 myTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
    //fragColor = vec4(myColor, 1.0);
    fragColor = mix(texture(texture1, myTexCoord), texture(texture0, myTexCoord), 0.8)*vec4(myColor, 1.0);
}
