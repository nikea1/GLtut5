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

void mat4DoubleToFloat(t_mat4 in, float* out);
void mat4Copy(t_mat4 in, t_mat4 out);
double toRadians(double degrees);
void mat4Transpose(t_mat4, t_mat4);
void test(t_vec4, t_mat4);
void zeroMat4(t_mat4 in);

int main(int argc, const char * argv[]) {
    //-----------------------------------------------------
    //Initialize GLFW and GLAD
    //-----------------------------------------------------
    
    GLFWwindow *window;
    
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
    window = glfwCreateWindow(800, 600, "Model View", NULL, NULL);
    
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
    
    //GLuint program = initShaderFiles("vshader.vert", "fshader.frag");   //Initialize shaders
    GLuint c_program = initShaderFiles("cubevshader.vert", "cubefshader.frag"); //Init shader for cube
    GLuint vao; //Vertex Array Object
    GLuint vbo; //Vertex Buffer Object
    GLuint ebo; //Element Buffer Object
    
    GLuint tex0, tex1; //Textures
    unsigned char *img; //image data
    int width, height, nrchannel; //image details
    
    //Local Coordinates
    /*
    GLfloat vertices[] = {
        //Position         //Color            //Textures
        0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 0.25f, 1.0f, 1.0f, //0
        0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.25f, 1.0f, 0.0f, //1
       -0.5f, -0.5f, 0.0f, 1.0f, 0.5f, 0.25f, 0.0f, 0.0f, //2
       -0.5f,  0.5f, 0.0f, 1.0f, 0.5f, 0.25f, 0.0f, 1.0f, //3
    };
    
    GLuint elements[]={
      0, 1, 2,
      0, 2, 3
    };
    */
    GLfloat c_vertices[] = {
        //Position            //Textures
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
      
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    t_vec3 cube_Positions[] = {
        {0.0f, 0.0f,   0.0f},
        {2.0f, 5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f},
        
    };
    //Matrices and vectors
    GLfloat m4_out[16]; //output to shaders
    t_mat4 temp;
    t_vec3 axis;
    t_vec3 trans;
    t_vec4 frustrum; //FOV, Ascpect, Near, Far
    t_mat4 model;
    t_mat4 view;
    t_mat4 projection;
    //glUseProgram(program);
    glUseProgram(c_program);
    
    //------------------------------------------------------
    //MVP Matrix
    //------------------------------------------------------
    glmc_identity(model);                                       //initialize model matrix as identity matrix
    glmc_vec3(0.5, 1.0, 0.0, axis);                             //set axis
   /* glmc_rotate(model, toRadians(50.0), axis, temp);          //rotate model -55 degrees around x axis and save to temp
    mat4Copy(temp, model);                                      //copy temp into model
    */
    glmc_identity(view);                                    //Initialize view
    glmc_vec3(0.0, 0.0, -3.0, trans);                           //Set Translation vector
    glmc_translate(view, trans, temp);                          //Translate view matrix and save in temp
    mat4Copy(temp, view);/*  */                                     //copy temp in view
    
    
    glmc_identity(projection);                                //Initialize projection
    glmc_vec4(toRadians(45.0), (double)800/(double)600, 0.1, 100.0, frustrum); //Set Frustrum
    test(frustrum, projection);                                 //Test my own Perspective matrix
   /* */
    
    //------------------------------------------------------
    //Textures
    //------------------------------------------------------
    
    //Container
    glGenTextures(1, &tex0);                                                                        //Generate Texture
    glBindTexture(GL_TEXTURE_2D, tex0);                                                             //Bind current Texture
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);                                   //Set S parameter to Repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                                   //Set T parameter to Repeat
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                               //Set Minification filter to Linear
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                               //Set Magnification filter to linear
    
    img = stbi_load("container.jpg", &width, &height, &nrchannel, 0);                               //Load image data into array
    
    if(img){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);    //Load image into the texture
        glGenerateMipmap(GL_TEXTURE_2D);                                                            //Generate mipmaps of current texture
        stbi_image_free(img);                                                                       //Free image after use
    }
    else{
        printf("Image did not load.\n");
        exit(EXIT_FAILURE);
    }
    
    //Awesome Face
    glActiveTexture(GL_TEXTURE1);                                                                   //Turn on Texture 1
    glGenTextures(1, &tex1);                                                                        //Generate Texture
    glBindTexture(GL_TEXTURE_2D, tex1);                                                             //Bind texture as Current texture
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);                                   //Set S parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);                                   //Set T parameter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);                               //Set Minification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                               //Set Magnification
    
    stbi_set_flip_vertically_on_load(1);                                                            //Flip image vertically
    img = stbi_load("awesomeface.png", &width, &height, &nrchannel, 0);                             //Load image data into array
    
    
    if(img){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);   //Load image into texture
        glGenerateMipmap(GL_TEXTURE_2D);                                                            //Generate mipmap of current texture
        stbi_image_free(img);                                                                       //free the image
    }
    else{
        printf("Image did not load.\n");
        exit(EXIT_FAILURE);
    }
    
    //------------------------------------------------------
    //Buffers
    //------------------------------------------------------
   
    //Vertex Array
    glGenVertexArrays(1, &vao);                                                        //Generate Vertex Array that will hold the array buffers
    glBindVertexArray(vao);                                                            //Bind Vertex Array
    
    //Array Cube buffer
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(c_vertices), c_vertices, GL_STATIC_DRAW);
    /*
    //Array Buffer
    glGenBuffers(1, &vbo);                                                             //gernerate array buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                                //bind Array buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);         //set data in array buffer to draw
    
    //Element Buffer
    glGenBuffers(1, &ebo);                                                             //generate element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);                                        //bind element array buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW); //set data in element array buffer to draw
    */
    
    //------------------------------------------------------
    //Set Attributes
    //------------------------------------------------------
    //Cube attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    //Cube Textures
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);
    /*
    //Position attributes in layout/index 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (GLvoid*)0);                    //define position attribute data
    glEnableVertexAttribArray(0);                                                                       //Activate layout 0
    
    //Color attributes in layout/index 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (GLvoid*)(3*sizeof(GL_FLOAT))); //defined the Color attribute
    glEnableVertexAttribArray(1);                                                                       //Activate layout 1
    
    //Texture attributes in layout/index 2
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(GL_FLOAT), (GLvoid*)(6*sizeof(GL_FLOAT))); //defined the Texture attribute
    glEnableVertexAttribArray(2);                                                                       //Activate layout 2
    */
    //------------------------------------------------------
    //Set Uniforms
    //------------------------------------------------------
    
    //Uniform Textures
    glUniform1i(glGetUniformLocation(c_program, "texture0"), 0);                          //Get location of texture0 in program and set it to 0
    glUniform1i(glGetUniformLocation(c_program, "texture1"), 1);                          //Get location of texture1 in program and set it to 1
    
    glEnable(GL_DEPTH_TEST);
    //------------------------------------------------------
    //Loop Starts Here
    //------------------------------------------------------
    while(!glfwWindowShouldClose(window)){
        
        //Clear Window screen
        glClearColor(1.0, 1.0, 1.0, 1.0);                                               //Set a clear color to white
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);                             //Clear color with the clear color
        
        //Textures
        glActiveTexture(GL_TEXTURE0);                                                   //Activate textures in Texture 0
        glBindTexture(GL_TEXTURE_2D, tex0);                                             //Bind tex0
        glActiveTexture(GL_TEXTURE1);                                                   //Activate textures in Texture 1
        glBindTexture(GL_TEXTURE_2D, tex1);                                             //Bind tex1
        
        //mvp matrix
        for(int i = 0; i < 10; i++){
            glmc_identity(model);
            glmc_translate(model, cube_Positions[i], temp);
            glmc_vec3(1.0, 0.3, 0.5, axis);
            double angle = 20.0 * i;
            glmc_rotate(temp, angle, axis, model);
            //glmc_rotate(model, -glfwGetTime()*toRadians(50.0), axis, temp);                  //set new rotation for model
            //mat4Copy(temp, model);                                                          //copy temp to model
            mat4DoubleToFloat(model, m4_out);                                               //convert double type to float
            glUniformMatrix4fv(glGetUniformLocation(c_program, "model"), 1, GL_FALSE, m4_out); //set uniform matrix model
            mat4DoubleToFloat(view, m4_out);                                                //convert view to float matrix
            glUniformMatrix4fv(glGetUniformLocation(c_program, "view"), 1, GL_FALSE, m4_out); //set uniform view matrix
        
            mat4DoubleToFloat(projection, m4_out);                                          //convert Projection to float
            glUniformMatrix4fv(glGetUniformLocation(c_program, "projection"), 1, GL_FALSE, m4_out); //set uniform projection matrix
        
            //Draw
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);                           //Reads Element Buffer and draws
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
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

void mat4DoubleToFloat(t_mat4 in, float* out){
    if(in == NULL || out == NULL)
    return;
    
    for(int i = 0; i< 16; i++){
        out[i] = (float)in[i];
    }
}

void mat4Copy(t_mat4 in, t_mat4 out){
    
    for(int i = 0; i< 16; i++){
        out[i] = (float)in[i];
    }
}

double toRadians(double degrees){
    return degrees*M_PI/180.0;
}

void mat4Transpose(t_mat4 in, t_mat4 out){

    // 0  1  2  3   -> 0  4  8 12
    // 4  5  6  7      1  5  9 13
    // 8  9 10 11      2  6 10 14
    //12 13 14 15      3  7 11 15
    
    out[0] = in[0];
    out[1] = in[4];
    out[2] = in[8];
    out[3] = in[12];
    
    out[4] = in[1];
    out[5] = in[5];
    out[6] = in[9];
    out[7] = in[13];
    
    out[8] = in[2];
    out[9] = in[6];
    out[10] = in[10];
    out[11] = in[14];
    
    out[12] = in[3];
    out[13] = in[7];
    out[14] = in[11];
    out[15] = in[15];
    
}

void zeroMat4(t_mat4 in){
    for(int i = 0; i < 16; i++){
        in[i] = 0.0;
    }
}

void test(t_vec4 frustum, t_mat4 dest)
{
    /*
    t_vec4        clip;
    double        rl;
    double        tb;
    double        fn;
    
    clip[TOP] = frustum[NEAR] * tan(frustum[FOV] * M_PI / 360.0);
    clip[RIGHT] = clip[TOP] * frustum[ASPECT];
    clip[LEFT] = -clip[RIGHT];
    clip[BOTTOM] = -clip[TOP];
    rl = clip[RIGHT] - clip[LEFT];
    tb = clip[TOP] - clip[BOTTOM];
    fn = frustum[FAR] - frustum[NEAR];
    dest[0] = (frustum[NEAR] * 2.0) / rl;
    dest[1] = 0.0;
    dest[2] = 0.0;
    dest[3] = 0.0;
    dest[4] = 0.0;
    dest[5] = (frustum[NEAR] * 2.0) / tb;
    dest[6] = 0.0;
    dest[7] = 0.0;
    dest[8] = (clip[RIGHT] + clip[LEFT]) / rl;
    dest[9] = (clip[TOP] + clip[BOTTOM]) / tb;
    dest[10] = -(frustum[FAR] + frustum[NEAR]) / fn;
    dest[11] = -1.0;
    dest[12] = 0.0;
    dest[13] = 0.0;
    dest[14] = -(frustum[FAR] * frustum[NEAR] * 2.0) / fn;
    dest[15] = 0.0;
    */
    
    // 0  1  2  3
    // 4  5  6  7
    // 8  9 10 11
    //12 13 14 15
    double f, fn;
    zeroMat4(dest);
    f = 1/tan(frustum[FOV]*0.5);
    fn = 1 / (frustum[NEAR]-frustum[FAR]);
    
    dest[0] = f / frustum[ASPECT];
    dest[5] = f;
    dest[10] = (frustum[NEAR] + frustum[FAR]) * fn;
    dest[11] = -1.0;
    dest[14] = 2.0 * fn * frustum[NEAR] * frustum[FAR];
    
}
