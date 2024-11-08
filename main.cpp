#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLfloat camY = 2.0;          // Camera height
GLfloat sceRY = 0.0;        // Scene rotation around Y-axis
GLfloat sceTX = 0.0;        // Scene translation along X-axis
GLfloat sceTZ = 0.0;        // Scene translation along Z-axis

// Lighting setup
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
    glColor3f(0.5, 0.5, 0.5);  // Set grid color to a subdued grey
    glLineWidth(1.0);           // Keep grid line thin
    glBegin(GL_LINES);
    for (line = -50; line <= 50; line += step) {
        glVertex3f(line, -0.4, 50);
        glVertex3f(line, -0.4, -50);
        glVertex3f(50, -0.4, line);
        glVertex3f(-50, -0.4, line);
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

void drawTrackSegment(GLfloat x1, GLfloat z1, GLfloat x2, GLfloat z2, GLfloat width) {
    // Calculate the direction vector between the two points
    GLfloat dx = x2 - x1;
    GLfloat dz = z2 - z1;
    GLfloat length = sqrt(dx * dx + dz * dz);

    // Normalize the direction vector
    dx /= length;
    dz /= length;

    // Calculate the left and right offset vectors for width
    GLfloat offsetX = -dz * width / 2.0f;
    GLfloat offsetZ = dx * width / 2.0f;

    // Define the four corners of the quad
    glVertex3f(x1 + offsetX, 0.0f, z1 + offsetZ); // Left point on segment 1
    glVertex3f(x1 - offsetX, 0.0f, z1 - offsetZ); // Right point on segment 1
    glVertex3f(x2 - offsetX, 0.0f, z2 - offsetZ); // Right point on segment 2
    glVertex3f(x2 + offsetX, 0.0f, z2 + offsetZ); // Left point on segment 2
}

void drawTrack() {
    // Track vertices for the centerline of the track
    GLfloat trackVertices[][3] = {
        {-20.5f, 0.0f, -12.5f},
        {-21.5f, 0.0f, -18.4f},
        {-24.0f, 0.0f, -24.4f},
        {-26.9f, 0.0f, -23.0f},
        {-47.9f, 0.0f, -11.0f},
        {-48.3f, 0.0f, -9.0f},
        {-48.5f, 0.0f, -7.0f},
        {-47.4f, 0.0f, -5.0f},
        {-44.8f, 0.0f, -2.0f},
        {-46.8f, 0.0f,2.0f},
        {-47.0f, 0.0f,3.0f},
        {-44.5f, 0.0f,10.0f},
        {-44.0f, 0.0f, 14.8f},
        {-43.5f, 0.0f, 15.0f},
        {-31.0f, 0.0f, 0.0f},
        {-21.5f, 0.0f, -9.0f},
        {-15.0f, 0.0f, 4.5},
        {11.5f, 0.0f, 22.5f},
        {11.0f, 0.0f, 23.5f},
        {9.2f, 0.0f, 25.5f},
        {10.8f, 0.0f, 27.5f},
        {11.0f, 0.0f, 27.6f},
        {25.0f, 0.0f, 37.6f},
        {31.0f, 0.0f, 34.5f},
        {47.2f, 0.0f,2.2f},
        {44.0f, 0.0f,0.0f},
        {42.5f, 0.0f,-2.0f},
        {42.1f, 0.0f,-5.0f},
        {40.1f, 0.0f,-5.7f},
        {39.1f, 0.0f,-5.0f},
        {36.1f, 0.0f,-2.0f},
        {34.5f, 0.0f,0.0f},
        {33.0f, 0.0f,4.0f},
        {32.5f, 0.0f,10.0f},
        {29.5f, 0.0f,16.5f},
        {26.5f, 0.0f,17.0f},
        {4.0f, 0.0f,2.5f},
        {3.0f, 0.0f,1.5f},
        {1.3f, 0.0f,0.0f},
        {-9.5f, 0.0f,-18.5f},
        {-20.5f, 0.0f,-12.5f},
    };

    GLfloat trackWidth = 1.0f;  // Set track width here

    glColor3f(1.0, 1.0, 1.0);   // Track color

    glBegin(GL_QUADS);           // Use quads for each segment

    for (int i = 0; i < sizeof(trackVertices) / sizeof(trackVertices[0]) - 1; i++) {
        drawTrackSegment(trackVertices[i][0], trackVertices[i][2],
                         trackVertices[i + 1][0], trackVertices[i + 1][2],
                         trackWidth);
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
    if (key == GLUT_KEY_UP) camY += 0.5; // Zoom in
    if (key == GLUT_KEY_DOWN) camY -= 0.5; // Zoom out
    if (key == GLUT_KEY_LEFT) sceRY -= 2.0; // Rotate left
    if (key == GLUT_KEY_RIGHT) sceRY += 2.0; // Rotate right
    glutPostRedisplay();
}

// Keyboard input for additional controls
void keyboard(unsigned char key, int x, int y) {
    if (key == 's') sceTZ += 1; // Move camera forward
    if (key == 'w') sceTZ -= 1; // Move camera backward
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
