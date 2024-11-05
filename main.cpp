#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

// Camera and rotation variables
GLfloat camY = 2.0;
GLfloat sceRY = 0.0;

// Lighting settings
void light0() {
    GLfloat amb[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat diff[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat spec[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat pos[] = { 10, 10, 5, 1.0 };

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
    GLfloat specRef[] = { 0.7, 0.7, 0.7, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specRef);
    glMateriali(GL_FRONT, GL_SHININESS, 128);
}

// Grid for visualization
void drawGrid() {
    glColor3f(0.5f, 0.5f, 0.5f); // Gray grid lines
    GLfloat step = 1.0f;
    GLint line;
    glBegin(GL_LINES);
    for (line = -20; line <= 20; line += step) {
        glVertex3f(line, -0.1, 20);
        glVertex3f(line, -0.1, -20);
        glVertex3f(20, -0.1, line);
        glVertex3f(-20, -0.1, line);
    }
    glEnd();
}

void drawAxes() {
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0); glVertex3f(-200, 0, 0); glVertex3f(200, 0, 0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(0, -200, 0); glVertex3f(0, 200, 0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0, 0, -200); glVertex3f(0, 0, 200);
    glEnd();
}

// Function to render the track layout (basic Marina Bay circuit path)
void drawTrack() {
    glColor3f(0.7f, 0.7f, 0.7f); // Gray color for track
    glLineWidth(4.0f); // Thicker lines for track
    glBegin(GL_LINE_STRIP);

    // Define vertices for a simplified track path
    glVertex3f(-10.0f, 0.0f, -8.0f);
    glVertex3f(-6.0f, 0.0f, -6.0f);
    glVertex3f(-2.0f, 0.0f, -4.0f);
    glVertex3f(2.0f, 0.0f, -3.0f);
    glVertex3f(6.0f, 0.0f, -1.0f);
    glVertex3f(8.0f, 0.0f, 2.0f);
    glVertex3f(6.0f, 0.0f, 6.0f);
    glVertex3f(2.0f, 0.0f, 8.0f);
    glVertex3f(-2.0f, 0.0f, 10.0f);
    glVertex3f(-6.0f, 0.0f, 8.0f);
    glVertex3f(-8.0f, 0.0f, 4.0f);

    glEnd();
    glLineWidth(1.0f); // Reset line width
}

// Buildings for basic cityscape
void drawBuilding(float x, float z, float width, float height) {
    glPushMatrix();
    glTranslatef(x, height / 2, z);
    glScalef(width, height, width);
    glColor3f(0.3f, 0.3f, 0.7f); // Blueish color for buildings
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawCityscape() {
    drawBuilding(-12.0f, -10.0f, 1.5f, 4.0f);
    drawBuilding(10.0f, 8.0f, 2.0f, 5.0f);
    drawBuilding(4.0f, 6.0f, 1.5f, 3.0f);
    drawBuilding(-8.0f, 6.0f, 2.5f, 6.0f);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Camera setup
    gluLookAt(0.0, 5.0 + camY, 15.0,   // Camera position
              0.0, 0.0, 0.0,           // Look-at point
              0.0, 1.0, 0.0);          // Up direction
    glRotatef(sceRY, 0.0, 1.0, 0.0);

    drawGrid();
    drawAxes();
    setLighting();

    // drawTrack();
    // drawCityscape();

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
    glMatrixMode(GL_MODELVIEW);
}

// Special keys for camera rotation and height
void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) camY += 0.2;
    if (key == GLUT_KEY_DOWN) camY -= 0.2;
    if (key == GLUT_KEY_LEFT) sceRY -= 2.0;
    if (key == GLUT_KEY_RIGHT) sceRY += 2.0;
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
    glutCreateWindow("Marina Bay Circuit Starter");
    
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboardSpecial);
    glutMainLoop();
    return 0;
}
