//
//  main.c
//  GLtut5
//
//  Created by Adenike Adeyemi on 11/21/18.
//  Copyright © 2018 Adenike Adeyemi. All rights reserved.
//

#define GLFW_INCLUDE_GLCOREARB
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glmc.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>




int main(int argc, const char * argv[]) {
    GLFWwindow *window;
    
    //Initialize GLFW window
    if(!glfwInit()){
        printf("GLFW could not initialize.\n");
        exit(EXIT_FAILURE);
    }
    
    //GLFW for apple
#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    //create GLFW window
    window = glfwCreateWindow(400, 400, "Model View", NULL, NULL);
    
    //check is GLFW window has been created.
    if(!window){
        printf("Window could not open.\n");
        exit(EXIT_FAILURE);
    }
    //make the window active
    glfwMakeContextCurrent(window);
    
    //initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("GLAD failed to load.\n");
        exit(EXIT_FAILURE);
    }
    
    while(!glfwWindowShouldClose(window)){
        
        //Clear Window screen
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //swap frames and IO
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("Hello, World!\n");
    return 0;
}
