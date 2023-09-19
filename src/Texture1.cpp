#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint VAO, VBO, textureID;

void init() {
   // Create Vertex Array Object (VAO)
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   // Create Vertex Buffer Object (VBO)
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   // Define the vertices and texture coordinates of a triangle
   GLfloat vertices[] = {
       -0.6f, -0.6f, 0.0f,  // Bottom-left vertex
        0.6f, -0.6f, 0.0f,  // Bottom-right vertex
        0.0f,  0.6f, 0.0f   // Top vertex
   };

   GLfloat texCoords[] = {
       0.0f, 0.0f,  // Bottom-left texture coordinate
       1.0f, 0.0f,  // Bottom-right texture coordinate
       0.5f, 1.0f   // Top texture coordinate
   };

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(texCoords), NULL, GL_STATIC_DRAW);
   glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
   glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(texCoords), texCoords);

   // Load texture
   int width, height, numChannels;
   unsigned char* textureData = stbi_load("texture.jpg", &width, &height, &numChannels, 0);

   if (!textureData) {
       std::cerr << "Failed to load texture." << std::endl;
       return;
   }

   glGenTextures(1, &textureID);
   glBindTexture(GL_TEXTURE_2D, textureID);

   // Set texture parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // Load texture data
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
   glGenerateMipmap(GL_TEXTURE_2D);

   stbi_image_free(textureData);

   // Specify the layout of the vertex data
   glVertexPointer(3, GL_FLOAT, 0, 0);
   glEnableClientState(GL_VERTEX_ARRAY);

   glTexCoordPointer(2, GL_FLOAT, 0, (void*)sizeof(vertices));
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindVertexArray(VAO);

   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureID);

   glDrawArrays(GL_TRIANGLES, 0, 3);

   glDisable(GL_TEXTURE_2D);
   glutSwapBuffers();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Texture Mapping on Triangle");
   glewInit();

   init();

   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
