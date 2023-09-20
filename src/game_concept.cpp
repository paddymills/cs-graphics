#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

GLuint backgroundTexture;
GLuint characterTexture;


GLfloat characterX = -0.8f; // Character's X position
GLfloat characterY = -0.65f; // Character's Y position
GLfloat characterVelocityX = 0.0f;
GLfloat characterVelocityY = 0.0f;
bool isJumping = false;

GLfloat objectX = -0.8f; // Character's X position
GLfloat objectY = -0.65f; // Character's Y position
GLfloat objectVelocityX = 0.0f;
GLfloat objectVelocityY = 0.0f;
bool isFired;

GLfloat gravity = -0.001f;

void init() {
    // Load and bind the background texture
    int bgWidth, bgHeight, bgChannels;
    unsigned char* bgImage = stbi_load("background.jpg", &bgWidth, &bgHeight, &bgChannels, 0);

    if (!bgImage) {
        std::cerr << "Failed to load the background texture." << std::endl;
        return;
    }

    glGenTextures(1, &backgroundTexture);
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    // Set texture parameters for the background
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load data for the background texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bgWidth, bgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, bgImage);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bgImage);

    // Load and bind the character texture
    int charWidth, charHeight, charChannels;
    unsigned char* charImage = stbi_load("character.png", &charWidth, &charHeight, &charChannels, 0);

    if (!charImage) {
        std::cerr << "Failed to load the character texture." << std::endl;
        return;
    }

    glGenTextures(1, &characterTexture);
    glBindTexture(GL_TEXTURE_2D, characterTexture);

    // Set texture parameters for the character
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load data for the character texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, charWidth, charHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, charImage);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(charImage);

    
}

void display() {
    printf("Display");
    //init();
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    // Draw the background texture
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(-1.0f, -1.0f);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(-1.0f, 1.0f);

    glEnd();

    
    // Draw the character texture on top of the background
    glBindTexture(GL_TEXTURE_2D, characterTexture);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(characterX, characterY);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(characterX + 0.1f, characterY);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(characterX + 0.1f, characterY + 0.1f);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(characterX, characterY + 0.1f);

    glEnd();

    
    // Draw the object texture
    if (isFired) {
        glBindTexture(GL_TEXTURE_2D, characterTexture);
        glBegin(GL_QUADS);

            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(objectX, objectY);

            glTexCoord2f(1.0f, 1.0f);
            glVertex2f(objectX + 0.1f, objectY);

            glTexCoord2f(1.0f, 0.0f);
            glVertex2f(objectX + 0.1f, objectY + 0.1f);

            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(objectX, objectY + 0.1f);

        glEnd();
    }

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
        characterVelocityX = -0.01f;
        break;
    case 'd':
    case 'D':
        characterVelocityX = 0.01f;
        break;
    case 'f':
    case 'F':
        if (!isFired) {
            objectX = characterX;
            objectY = characterY;

            objectVelocityX = 0.01f;
            objectVelocityY = 0.02f;
            isFired = true;
        }
        break;
    case ' ':
        if (!isJumping) {
            characterVelocityY = 0.02f;
            isJumping = true;
        }
        break;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    switch (key) {
    case 'a':
    case 'A':
    case 'd':
    case 'D':
        characterVelocityX = 0.0f;
        break;
    }
}
void update(int value) {
    characterX += characterVelocityX;

    if (isJumping) {
        characterY += characterVelocityY;
        characterVelocityY += gravity;

        // Check for ground
        if (characterY < -0.65f) {
            characterY = -0.65f;
            characterVelocityY = 0.0f;
            isJumping = false;
        }
    }

    if (isFired) {
        objectX += objectVelocityX;
        objectY += objectVelocityY;
        objectVelocityY += gravity;

        // Check for ground
        if (objectY < -0.65f) {
            objectY = -0.65f;
            objectVelocityY = 0.01f;
        }

        if (objectX > 1 || objectY > 1)
            isFired = false;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // 60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Two Textured Images (Background and Character)");
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);

    glewInit();

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
