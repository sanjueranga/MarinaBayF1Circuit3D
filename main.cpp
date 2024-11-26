#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

GLfloat camY = 2.0;         
GLfloat sceRY = 0.0;      
GLfloat sceTX = 0.0;        
GLfloat sceTZ = 0.0;        

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


void drawGrid() {
    GLfloat step = 1.0f;
    GLint line;
    glColor3f(0.5, 0.5, 0.5);  
    glLineWidth(1.0);           
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
   
    GLfloat dx = x2 - x1;
    GLfloat dz = z2 - z1;
    GLfloat length = sqrt(dx * dx + dz * dz);

    // Normalize the direction vector
    dx /= length;
    dz /= length;

    GLfloat offsetX = -dz * width / 2.0f;
    GLfloat offsetZ = dx * width / 2.0f;

    // Define the four corners of the quad
    glVertex3f(x1 + offsetX, 0.0f, z1 + offsetZ); 
    glVertex3f(x1 - offsetX, 0.0f, z1 - offsetZ); 
    glVertex3f(x2 - offsetX, 0.0f, z2 - offsetZ); 
    glVertex3f(x2 + offsetX, 0.0f, z2 + offsetZ); 
}

void drawTrack() {
    // Track vertices for the centerline of the track
    GLfloat trackVertices[][3] = {
        {-20.5f, 0.0f, -22.5f},
        {-21.5f, 0.0f, -28.4f},
        {-24.0f, 0.0f, -34.4f},
        {-26.9f, 0.0f, -33.0f},
        {-47.9f, 0.0f, -21.0f},
        {-48.3f, 0.0f, -19.0f},
        {-48.5f, 0.0f, -17.0f},
        {-47.4f, 0.0f, -15.0f},
        {-44.8f, 0.0f, -12.0f},
        {-46.8f, 0.0f,-8.0f},
        {-47.0f, 0.0f,-7.0f},
        {-44.5f, 0.0f,0.0f},
        {-44.0f, 0.0f, 4.8f},
        {-43.5f, 0.0f, 5.0f},
        {-31.0f, 0.0f, -10.0f},
        {-21.5f, 0.0f, -19.0f},
        {-15.0f, 0.0f, -5.5},
        {11.5f, 0.0f, 12.5f},
        {11.0f, 0.0f, 13.5f},
        {9.2f, 0.0f, 15.5f},
        {10.8f, 0.0f, 17.5f},
        {11.0f, 0.0f, 17.6f},
        {25.0f, 0.0f, 27.6f},
        {31.0f, 0.0f, 24.5f},
        {47.2f, 0.0f,-7.8f},
        {44.0f, 0.0f,-10.0f},
        {42.5f, 0.0f,-12.0f},
        {42.1f, 0.0f,-15.0f},
        {40.1f, 0.0f,-15.7f},
        {39.1f, 0.0f,-15.0f},
        {36.1f, 0.0f,-12.0f},
        {34.5f, 0.0f,-10.0f},
        {33.0f, 0.0f,-6.0f},
        {32.5f, 0.0f,0.0f},
        {29.5f, 0.0f,6.5f},
        {26.5f, 0.0f,7.0f},
        {4.0f, 0.0f,-7.5f},
        {3.0f, 0.0f,-8.5f},
        {1.3f, 0.0f,-10.0f},
        {-9.5f, 0.0f,-28.5f},
        {-20.5f, 0.0f,-22.5f},
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


GLfloat bayVertices[][3] = {
    {-37.5f, 0.0f, -10.0f},
    {-12.0f, 0.0f, 5.0f},
    {-5.0f, 0.0f, 13.0f},
    {-3.0f, 0.0f, 17.0f},
    {22.0f, 0.0f, 30.0f},
    {26.0f, 0.0f, 31.0f},
    {31.0f, 0.0f, 30.7f},  
    {34.0f, 0.0f, 28.7f},  
    {37.0f, 0.0f, 25.7f},  
    {50.5f, 0.0f, -15.0f},  
    {56.5f, 0.0f, -24.0f}, 
    {56.5f, 0.0f, 20.0f},  
    {53.5f, 0.0f, 35.0f},  
    {1.5f, 0.0f, 35.0f},  
    {-12.0f, 0.0f, 21.5f}, 
    {-15.0f, 0.0f, 21.5f},  
    {-17.0f, 0.0f, 22.0f},  
    {-20.0f, 0.0f, 25.0f}, 
    {-20.5f, 0.0f, 29.0f},  
    {-59.5f, 0.0f, 35.0f},
    {-49.5f, 0.0f, 15.1f},
    {-39.9f, 0.0f, 6.5f},
    {-39.0f, 0.0f, 4.5f},
    {-37.0f, 0.0f, -3.5f},
    {-36.8f, 0.0f, -3.5f},
    {-54.6f, 0.0f, 2.0f},
    {-60.6f, 0.0f, 1.0f},
    {-60.6f, 0.0f, -3.0f},
    {-53.4f, 0.0f, -3.0f},
};

void drawBayOutline() {

    // Loop through the vertices and connect them
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        glVertex3f(bayVertices[i][0], bayVertices[i][1], bayVertices[i][2]);
    }
    glVertex3f(bayVertices[0][0], bayVertices[0][1], bayVertices[0][2]); // Close the fan
    glEnd();

    // Draw the outline on top
    glColor3f(0.0, 0.5, 0.5); // Outline color
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        glVertex3f(bayVertices[i][0], bayVertices[i][1], bayVertices[i][2]);
    }
    glEnd();
}

void fillBayOutlineWithLandDebug() {
    GLfloat minZ = 1e9, maxZ = -1e9;

    GLfloat extraSpace = 1.0f; // Extend upper boundary

    // Calculate minZ and maxZ
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        if (bayVertices[i][2] < minZ) minZ = bayVertices[i][2];
        if (bayVertices[i][2] > maxZ) maxZ = bayVertices[i][2];
    }


    // Find the Z range
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        if (bayVertices[i][2] < minZ) minZ = bayVertices[i][2];
        if (bayVertices[i][2] > maxZ) maxZ = bayVertices[i][2];
    }

    GLfloat stepZ = 0.1f;  // Step size for Z

    glBegin(GL_QUADS);

    for (GLfloat z = minZ; z <= maxZ + extraSpace; z += stepZ) {
        GLfloat intersections[128];
        int count = 0;

        // Find all X intersections at current Z
        for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
            int j = (i + 1) % (sizeof(bayVertices) / sizeof(bayVertices[0])); // Next vertex
            GLfloat z1 = bayVertices[i][2], z2 = bayVertices[j][2];
            GLfloat x1 = bayVertices[i][0], x2 = bayVertices[j][0];

            if ((z >= z1 && z <= z2) || (z >= z2 && z <= z1)) {
                GLfloat x = x1 + (x2 - x1) * (z - z1) / (z2 - z1);
                intersections[count++] = x;
            }
        }

        // Sort intersections
        for (int i = 0; i < count - 1; i++) {
            for (int j = i + 1; j < count; j++) {
                if (intersections[i] > intersections[j]) {
                    GLfloat temp = intersections[i];
                    intersections[i] = intersections[j];
                    intersections[j] = temp;
                }
            }
        }



        // Fill water and land alternately
        for (int i = 0; i < count - 1; i += 2) {
            // Water (blue)
            glColor3f(0.0, 0.0, 1.0);
            glVertex3f(intersections[i], 0.0f, z);
            glVertex3f(intersections[i], 0.0f, z + stepZ);
            glVertex3f(intersections[i + 1], 0.0f, z + stepZ);
            glVertex3f(intersections[i + 1], 0.0f, z);

            // Land (brown)
            if (i + 2 < count) {  // Check bounds
                glColor3f(0.6, 0.3, 0.1);
                glVertex3f(intersections[i + 1], 0.0f, z);
                glVertex3f(intersections[i + 1], 0.0f, z + stepZ);
                glVertex3f(intersections[i + 2], 0.0f, z + stepZ);
                glVertex3f(intersections[i + 2], 0.0f, z);
            }
        }
    }

    glEnd();
}

// Display function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // Camera setup
    gluLookAt(sceTX, camY, 5.0 + sceTZ,  
              0.0, 0.0, 0.0,         
              0.0, 1.0, 0.0);          
    glRotatef(sceRY, 0.0, 1.0, 0.0);

    drawGrid();
    drawAxes();
    setLighting();

    drawBayOutline();
    fillBayOutlineWithLandDebug();

    glDisable(GL_DEPTH_TEST); // Disable depth test while drawing the track
    drawTrack();

    glEnable(GL_DEPTH_TEST);  // Re-enable depth test for the land/water rendering



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


void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) camY += 0.5; 
    if (key == GLUT_KEY_DOWN) camY -= 0.5; 
    if (key == GLUT_KEY_LEFT) sceRY -= 2.0;
    if (key == GLUT_KEY_RIGHT) sceRY += 2.0;
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    if (key == 's') sceTZ += 1;
    if (key == 'w') sceTZ -= 1; 
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
