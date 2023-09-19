#include <GL/glew.h>
#include <GL/freeglut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

GLuint textureID_background;

void background_texture_load() {
   // Load and bind texture
   int width, height, numChannels;
   unsigned char* textureData = stbi_load("background.jpg", &width, &height, &numChannels, 0);

   if (!textureData) {
       std::cerr << "Failed to load texture." << std::endl;
       return;
   }

   glGenTextures(1, &textureID_background);
   glBindTexture(GL_TEXTURE_2D, textureID_background);

   // Set texture parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // Load texture data
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
   glGenerateMipmap(GL_TEXTURE_2D);

   stbi_image_free(textureData);
}

void background_rectangle() {
   //glLoadIdentity();
   glBegin(GL_QUADS);
   glTexCoord2f(0, 1);
   glVertex2f(0, 0);

   glTexCoord2f(1, 1);
   glVertex2f(800, 0);

   glTexCoord2f(1, 0);
   glVertex2f(800, 600);

   glTexCoord2f(0, 0);
   glVertex2f(0, 600);
   glEnd();
   glFlush();
}

void init() {
   
   background_texture_load();
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 800, 0, 600, -1, 1); // Set orthographic projection

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);


   glLoadIdentity();

   // Draw background with the texture
   glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, textureID_background);

   background_rectangle();
   
   glDisable(GL_TEXTURE_2D);

   glutSwapBuffers();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Background with Texture");
   glewInit();

   init();

   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
