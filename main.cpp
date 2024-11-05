#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLfloat camY = 2.0;          // Camera height
GLfloat sceRY = 0.0;        // Scene rotation around Y-axis
GLfloat sceTX = 0.0;        // Scene translation along X-axis
GLfloat sceTZ = 0.0;        // Scene translation along Z-axis

// Vertices for drawing objects
float vertices[][3] = {
    {1, 1, -1}, { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 },
    { 1, -1, -1 }, { 1, -1, 1 }, { -1, -1, 1 }, { -1, -1, -1 },
    { 0, 1, 0 }
};

// Function to set up lighting
void light0() {
    GLfloat amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diff[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { -0.5, 1.0, -0.5, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void setLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    light0();
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

// Function to draw grid
void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;
    glBegin(GL_LINES);
    for (line = -20; line <= 20; line += step) {
        glVertex3f(line, -0.4, 20);
        glVertex3f(line, -0.4, -20);
        glVertex3f(20, -0.4, line);
        glVertex3f(-20, -0.4, line);
    }
    glEnd();
}

// Function to draw axes
void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-200, 0, 0); glVertex3f(200, 0, 0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0, -200, 0); glVertex3f(0, 200, 0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, -200); glVertex3f(0, 0, 200);
    glEnd();
}

// Function to render the track layout
void drawTrack() {
    GLfloat trackVertices[][2] = {
        { -0.8f, 0.2f }, { -0.6f, 0.4f }, { -0.4f, 0.6f }, // Left section
        { -0.2f, 0.8f }, { 0.0f, 0.9f }, { 0.2f, 0.8f },    // Top curve
        { 0.4f, 0.6f }, { 0.5f, 0.4f }, { 0.6f, 0.2f },     // Right section
        { 0.5f, 0.0f }, { 0.3f, -0.2f }, { 0.1f, -0.4f },   // Bottom right curve
        { -0.1f, -0.6f }, { -0.3f, -0.7f }, { -0.5f, -0.6f },// Bottom left curve
        { -0.7f, -0.4f }, { -0.8f, -0.2f }                  // Connect back to start
    };

    glColor3f(1.0, 1.0, 1.0);  // Track color (white)
    glLineWidth(2.0);          // Line thickness

    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(trackVertices) / sizeof(trackVertices[0]); i++) {
        glVertex2fv(trackVertices[i]);
    }
    glEnd();
}

// Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Camera setup
    gluLookAt(sceTX, camY, 5.0 + sceTZ,   // Camera position
              0.0, 0.0, 0.0,           // Look-at point
              0.0, 1.0, 0.0);          // Up direction
    glRotatef(sceRY, 0.0, 1.0, 0.0);

    drawGrid();
    drawAxes();
    setLighting();

    drawTrack();

    glPopMatrix();
    glutSwapBuffers();
}

// Window reshape handler
void reshape(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect_ratio, 1.0, 100.0);
}

// Special keys for camera rotation and height
void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) camY += 0.2; // Zoom in
    if (key == GLUT_KEY_DOWN) camY -= 0.2; // Zoom out
    if (key == GLUT_KEY_LEFT) sceRY -= 2.0; // Rotate left
    if (key == GLUT_KEY_RIGHT) sceRY += 2.0; // Rotate right
    glutPostRedisplay();
}

// Keyboard input for additional controls
void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') sceTZ += 1; // Move camera forward
    if (key == 's') sceTZ -= 1; // Move camera backward
    glutPostRedisplay();
}

// Initialization function
void init(void) {
    glClearColor(0.0, 0.0, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Marina Bay Circuit with Camera Controls");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    glutMainLoop();
    return 0;
}
