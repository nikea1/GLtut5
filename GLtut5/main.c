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
    
    //-----------------------------------------------------
    //Initialize GLFW and GLAD
    //-----------------------------------------------------
    
    //Initialize GLFW window
    if(!glfwInit()){
        printf("GLFW could not initialize.\n");
        exit(EXIT_FAILURE);
    }
    
    //GLFW hin for apple
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
    //------------------------------------------------------
    //OpenGL Code Starts Here
    //------------------------------------------------------
    
    GLuint program = initShaderFiles("vshader.vert", "fshader.frag");
    GLuint vao; //Vertex Array Object
    GLuint vbo; //Vertex Buffer Object
    GLuint ebo; //Element Buffer Object
    
    GLfloat vertices[] = {
        //Position
        0.5f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       -0.5f,  0.5f, 0.0f
    };
    
    GLuint elements[]={
      0, 1, 2,
      0, 2, 3
    };
    glUseProgram(program);
    
    //------------------------------------------------------
    //Buffers
    //------------------------------------------------------
    //Vertex Array
    glGenVertexArrays(1, &vao);                                                        //Generate Vertex Array that will hold the array buffers
    glBindVertexArray(vao);                                                            //Bind Vertex Array
    
    //Array Buffer
    glGenBuffers(1, &vbo);                                                             //gernerate array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                //bind Array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);         //set data in array buffer to draw
    
    //Element Buffer
    glGenBuffers(1, &ebo);                                                             //generate element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);                                        //bind element array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW); //set data in element array buffer to draw
    
    
    //------------------------------------------------------
    //Set Attributes
    //------------------------------------------------------
    //Position attributes in layout/index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0*sizeof(GL_FLOAT), (GLvoid*)0);   //define position attribute data
    glEnableVertexAttribArray(0);                                                      //Activate layout 0
    
    //------------------------------------------------------
    //Loop Starts Here
    //------------------------------------------------------
    while(!glfwWindowShouldClose(window)){
        
        //Clear Window screen
        glClearColor(1.0, 1.0, 1.0, 1.0);                                              //Set a clear color to white
        glClear(GL_COLOR_BUFFER_BIT);                                                  //Clear color with the clear color
        
        //Draw
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);                           //Reads Element Buffer and draws
        
        //swap frames and IO
        glfwSwapBuffers(window);                                                       //swap frames
        glfwPollEvents();                                                              //Check for IO
    }
    //-------------------------------------------------------
    //End
    //-------------------------------------------------------
    printf("Hello, World!\n");
    return 0;
}


