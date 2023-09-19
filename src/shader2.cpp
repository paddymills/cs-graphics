// Details  - https://www.youtube.com/watch?v=Rin5Cp-Hhj8&ab_channel=GetIntoGameDev
#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

// Vertex shader source code
const char* vertexShaderSource = R"(
   #version 330 core

   layout(location = 0) in vec3 vertexPosition;
   out vec4 vertexColor;

   void main() {
       gl_Position = vec4(vertexPosition, 1.0); 
       vertexColor = vec4(vertexPosition * 0.5 + 0.5 , 1.0);
   }
)";

// Fragment shader source code
const char* fragmentShaderSource = R"(
   #version 330 core

   in vec4 vertexColor;
   out vec4 fragColor;

   void main() {
       fragColor = vertexColor + 0.0;
   }
)";

GLuint VAO, VBO, shaderProgram;

void init() {
   // Create Vertex Array Object (VAO)
   glGenVertexArrays(1, &VAO);
   glBindVertexArray(VAO);

   // Create Vertex Buffer Object (VBO)
   glGenBuffers(1, &VBO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);

   // Define the vertices of a triangle
   GLfloat vertices[] = {
       -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
   };

   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   // Load and compile shaders
   GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
   glCompileShader(vertexShader);

   GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
   glCompileShader(fragmentShader);

   // Create and link the shader program
   shaderProgram = glCreateProgram();
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   glLinkProgram(shaderProgram);

   glUseProgram(shaderProgram);

   // Specify the layout of the vertex data
   GLint posAttrib = glGetAttribLocation(shaderProgram, "vertexPosition");
   glEnableVertexAttribArray(posAttrib);
   glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBindVertexArray(VAO);
   glDrawArrays(GL_TRIANGLES, 0, 3);
   glutSwapBuffers();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowSize(800, 600);
   glutCreateWindow("Vertex Shading with GLSL");
   glewInit();

   init();

   glutDisplayFunc(display);
   glutMainLoop();
   return 0;
}
