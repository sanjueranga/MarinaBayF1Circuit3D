#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

//GLfloat camY = 2.0;
GLfloat sceRY = 0.0;
GLfloat sceTX = 0.0;
GLfloat sceTZ = 0.0;

#define M_PI 3.14159265358979323846


GLfloat camX = 0.0, camY = 2.0, camZ = 5.0;
GLfloat camAngleX = 0.0, camAngleY = 0.0;  

GLfloat moveSpeed = 0.5f;
GLfloat rotateSpeed = 5.0f;

float rotationAngle = 0.0f; // Global variable for rotation

void update() {
    rotationAngle += 0.25f; // Adjust speed by changing this value
    if (rotationAngle > 360.0f) {
        rotationAngle -= 360.0f;
    }
    glutPostRedisplay();
}
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

    GLfloat trackWidth = 1.5f;  // Set track width here

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
    {56.5f, 0.0f, -44.0f},
    {56.5f, 0.0f, 20.0f},
    {53.5f, 0.0f, 45.0f},
    {1.5f, 0.0f, 45.0f},
    {-12.0f, 0.0f, 21.5f},
    {-15.0f, 0.0f, 21.5f},
    {-17.0f, 0.0f, 22.0f},
    {-20.0f, 0.0f, 25.0f},
    {-20.5f, 0.0f, 29.0f},
    {-59.5f, 0.0f, 45.0f},
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

 
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        glVertex3f(bayVertices[i][0], bayVertices[i][1], bayVertices[i][2]);
    }
    glVertex3f(bayVertices[0][0], bayVertices[0][1], bayVertices[0][2]); // Close the fan
    glEnd();

   
    glColor3f(0.0, 0.5, 0.5); // Outline color
    glLineWidth(2.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        glVertex3f(bayVertices[i][0], bayVertices[i][1], bayVertices[i][2]);
    }
    glEnd();
}

void fillBayOutlineWithLand() {
    GLfloat minZ = 1e9, maxZ = -1e9;

    GLfloat extraSpace = 1.0f; // Extend upper boundary

    // Calculate minZ and maxZ
    for (int i = 0; i < sizeof(bayVertices) / sizeof(bayVertices[0]); i++) {
        if (bayVertices[i][2] < minZ) minZ = bayVertices[i][2];
        if (bayVertices[i][2] > maxZ) maxZ = bayVertices[i][2];
    }

    GLfloat stepZ = 0.1f;  

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

     
        GLfloat minX = -60.6f;
        GLfloat maxX = 56.5f;  

        GLfloat prevX = minX;

        for (int i = 0; i < count; i += 2) {
            // Fill land between previous X and current intersection
            glColor3f(0.6, 0.3, 0.1);
            glVertex3f(prevX, 0.0f, z);
            glVertex3f(prevX, 0.0f, z + stepZ);
            glVertex3f(intersections[i], 0.0f, z + stepZ);
            glVertex3f(intersections[i], 0.0f, z);

            // Fill water between pairs of intersections
            if (i + 1 < count) {
                glColor3f(0.0, 0.0, 1.0);
                glVertex3f(intersections[i], 0.0f, z);
                glVertex3f(intersections[i], 0.0f, z + stepZ);
                glVertex3f(intersections[i + 1], 0.0f, z + stepZ);
                glVertex3f(intersections[i + 1], 0.0f, z);

                prevX = intersections[i + 1];
            }
        }

        // Fill remaining land to the right of the last intersection
        glColor3f(0.6, 0.3, 0.1);
        glVertex3f(prevX, 0.0f, z);
        glVertex3f(prevX, 0.0f, z + stepZ);
        glVertex3f(maxX, 0.0f, z + stepZ);
        glVertex3f(maxX, 0.0f, z);
    }

    glEnd();
}


void drawCylinder(float radius, float height, float r, float g, float b) {
    GLUquadric* quad = gluNewQuadric();
    glColor3f(r, g, b);
    gluCylinder(quad, radius, radius, height, 16, 16);  // Draw cylinder
    gluDeleteQuadric(quad);
}



 void drawSingaporeFlyerWheel() {
    const int numSegments = 36;
    const float radius = 5.0f;  
    const float capsuleRadius = 0.19f;
    const float capsuleHeight = 0.6f;
    const float centerX = 0.0f, centerY = 7.0f, centerZ = 0.0f;
    const float forkArmHeight = 6.0f;
    const float forkArmSpacing = 2.0f;
    const float forkRadius = 0.25f;
    const float axisHeight = 2.0f;
    const float axisRadius = 0.2f;


    glPushMatrix();


    glTranslatef(0.0f, 7.0f, 0.0f); // Move to center point
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z axis
    glTranslatef(0.0f, -7.0f, 0.0f);
     
    glColor3f(0.8, 0.8, 0.8); // Gray color for the wheel
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(x, y, centerZ-0.15f);
    }
    glEnd();

    glColor3f(0.8, 0.8, 0.8); // Gray color for the wheel
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(x, y, centerZ+0.15f);
    }
    glEnd();

    glBegin(GL_LINES);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(centerX, centerY, centerZ+0.35f);
        glVertex3f(x, y, centerZ+0.15f);
    }
    glEnd();


    // Draw the spokes
    glBegin(GL_LINES);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = centerX + radius * cos(angle);
        float y = centerY + radius * sin(angle);
        glVertex3f(centerX, centerY, centerZ-0.35f);
        glVertex3f(x, y, centerZ-0.15f);            
    }
    glEnd();

 
    for (int i = 0; i < numSegments; i++) {
        float angle = 2.0f * M_PI * i / numSegments;
        float x = centerX + (radius+0.25f) * cos(angle);
        float y = centerY + (radius + 0.25f) * sin(angle);

        // Position each capsule
        glPushMatrix();
        glTranslatef(x, y, centerZ-0.25f);
        glRotatef(angle * 180.0f / M_PI, 0.0f, 0.0f, 1.0f);
        drawCylinder(capsuleRadius, capsuleHeight, 0.0f, 0.0f, 1.0f);
        glPopMatrix();
    }

    glPopMatrix(); 


    glPushMatrix();
    glTranslatef(centerX , centerY - (radius+0.8f), centerZ - forkArmSpacing / 2.0f);
    glRotatef(90.0, -1.0f, 0.0f, 0.0f);
    drawCylinder(forkRadius, forkArmHeight, 0.6f, 0.6f, 0.6f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centerX , centerY - (radius + 0.8f), centerZ + forkArmSpacing / 2.0f);
    glRotatef(90.0, -1.0f, 0.0f, 0.0f);
    drawCylinder(forkRadius, forkArmHeight, 0.6f, 0.6f, 0.6f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(centerX,centerY, centerZ - forkArmSpacing / 2.0f);
    glRotatef(90.0, 0.0f, 0.0f, 1.0f);
    drawCylinder(axisRadius, axisHeight, 0.6f, 0.6f, 0.6f);
    glPopMatrix();

 }





 void drawArc(float cx, float cy, float r, float startAngle, float endAngle, float z) {
     glBegin(GL_LINE_STRIP);
     for (float theta = startAngle; theta <= endAngle; theta += 0.01f) {
         float x = cx + r * cos(theta);
         float y = cy + r * sin(theta);
         glVertex3f(x, y, z);
     }
     glEnd();
 }


 void drawLine(float x1, float y1, float x2, float y2, float z) {
     glBegin(GL_LINES);
     glVertex3f(x1, y1, z);
     glVertex3f(x2, y2, z);
     glEnd();
 }


 void drawReuleauxBaseWithLines(float r, float height) {
     float angleOffset = 2.0f * M_PI / 3.0f;

     float prevX, prevY, firstX, firstY;

     // Bottom face (z=0)
     glColor3f(1.0f, 0.5f, 0.5f);
     for (int i = 0; i < 3; i++) {
         float cx = r * cos(i * angleOffset);
         float cy = r * sin(i * angleOffset);
         float startAngle = i * angleOffset - M_PI / 3.0f;
         float endAngle = i * angleOffset + M_PI / 3.0f;

         // Calculate arc endpoints
         float startX = cx + r * cos(startAngle);
         float startY = cy + r * sin(startAngle);
         float endX = cx + r * cos(endAngle);
         float endY = cy + r * sin(endAngle);

         // Draw arc
         drawArc(cx, cy, r, startAngle, endAngle, 0.0f); // Bottom face z=0

       
         if (i > 0) {
             drawLine(prevX, prevY, startX, startY, 0.0f);
         }
         else {
             firstX = startX;
             firstY = startY;
         }
         prevX = endX;
         prevY = endY;
     }
   
     drawLine(prevX, prevY, firstX, firstY, 0.0f);

     glColor3f(0.5f, 0.5f, 1.0f);
     for (int i = 0; i < 3; i++) {
         float cx = r * cos(i * angleOffset);
         float cy = r * sin(i * angleOffset);
         float startAngle = i * angleOffset - M_PI / 3.0f;
         float endAngle = i * angleOffset + M_PI / 3.0f;

         // Calculate arc endpoints
         float startX = cx + r * cos(startAngle);
         float startY = cy + r * sin(startAngle);
         float endX = cx + r * cos(endAngle);
         float endY = cy + r * sin(endAngle);

         // Draw arc
         drawArc(cx, cy, r, startAngle, endAngle, height); // Top face z=height

         // Draw line connecting previous arc to current arc
         if (i > 0) {
             drawLine(prevX, prevY, startX, startY, height); // Connect arcs
         }
         else {
             firstX = startX;
             firstY = startY;
         }
         prevX = endX;
         prevY = endY;
     }
   
     drawLine(prevX, prevY, firstX, firstY, height);

   
     glColor3f(0.7f, 0.7f, 0.7f);
     glBegin(GL_QUADS);
     for (int i = 0; i < 3; i++) {
         float cx = r * cos(i * angleOffset);
         float cy = r * sin(i * angleOffset);
         float startAngle = i * angleOffset - M_PI / 3.0f;
         float endAngle = i * angleOffset + M_PI / 3.0f;

         for (float theta = startAngle; theta < endAngle; theta += 0.1f) {
             float x1 = cx + r * cos(theta);
             float y1 = cy + r * sin(theta);
             float x2 = cx + r * cos(theta + 0.1f);
             float y2 = cy + r * sin(theta + 0.1f);

             glVertex3f(x1, y1, 0.0f);      
             glVertex3f(x2, y2, 0.0f);    
             glVertex3f(x2, y2, height);    
             glVertex3f(x1, y1, height);    
         }
     }
     glEnd();
 }


 void fillTrianglesBetweenArcs(float r, float height) {
     float angleOffset = 2.0f * M_PI / 3.0f; // 120 degrees in radians

     glColor3f(0.0f, 1.0f, 0.0f); // Set color to green
     glBegin(GL_TRIANGLES);

     for (int i = 0; i < 3; i++) {
         float cx = r * cos(i * angleOffset); // Center of current arc
         float cy = r * sin(i * angleOffset);

         float startAngle = i * angleOffset - M_PI / 3.0f;
         float endAngle = i * angleOffset + M_PI / 3.0f;

         // Arc endpoints
         float startX = cx + r * cos(startAngle);
         float startY = cy + r * sin(startAngle);
         float endX = cx + r * cos(endAngle);
         float endY = cy + r * sin(endAngle);

         // Draw the triangle
         glVertex3f(cx, cy, height);       // Center of the arc
         glVertex3f(startX, startY, height); // Start of the arc
         glVertex3f(endX, endY, height);   // End of the arc
     }

     glEnd();
 }

 void drawStackedBase2() {

     const float centerX = 0.0f, centerY = 5.0f, centerZ = 0.0f;


     glPushMatrix();
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(3.0f, 0.2f);
     glPopMatrix();

     glPushMatrix();
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(2.5f, 0.2f);
     glPopMatrix();


    // glPushMatrix();
     //glTranslatef(centerX,1.5f , centerZ);
     //glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     //drawReuleauxBaseWithLines(2.5f, 1.5f);
     //glPopMatrix();



     //glPushMatrix();
    // glTranslatef(centerX,3.0f , centerZ );
     //glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     //drawReuleauxBaseWithLines(2.0f, 1.5f);
     //glPopMatrix();
 }


 // Function to draw and fill the gap between two Reuleaux bases
 void drawFilledGapBetweenReuleaux(float r1, float r2, float height) {
     float angleOffset = 2.0f * M_PI / 3.0f; // 120 degrees in radians

     glBegin(GL_QUADS);
     glColor3f(0.7f, 0.7f, 0.7f); // Use the color for the gap

     for (int i = 0; i < 3; i++) {
         float cx1 = r1 * cos(i * angleOffset); // Center of current arc (larger radius)
         float cy1 = r1 * sin(i * angleOffset);

         float cx2 = r2 * cos(i * angleOffset); // Center of current arc (smaller radius)
         float cy2 = r2 * sin(i * angleOffset);

         float startAngle = i * angleOffset - M_PI / 3.0f;
         float endAngle = i * angleOffset + M_PI / 3.0f;

         for (float theta = startAngle; theta < endAngle; theta += 0.1f) {
             // Points on the larger arc
             float x1_start = cx1 + r1 * cos(theta);
             float y1_start = cy1 + r1 * sin(theta);
             float x1_end = cx1 + r1 * cos(theta + 0.1f);
             float y1_end = cy1 + r1 * sin(theta + 0.1f);

             // Points on the smaller arc
             float x2_start = cx2 + r2 * cos(theta);
             float y2_start = cy2 + r2 * sin(theta);
             float x2_end = cx2 + r2 * cos(theta + 0.1f);
             float y2_end = cy2 + r2 * sin(theta + 0.1f);

             // Create quads between the larger and smaller arcs
             glVertex3f(x1_start, y1_start, 0.0f);
             glVertex3f(x1_end, y1_end, 0.0f);
             glVertex3f(x2_end, y2_end, 0.0f);
             glVertex3f(x2_start, y2_start, 0.0f);
         }
     }
     glEnd();
 }

 void drawStackedBase() {
     // Parameters for the first layer
     float outerRadius = 3.0f; // Outer radius of the first Reuleaux
     float innerRadius = 2.5f; // Inner radius of the first Reuleaux
     float height = 0.2f;      // Height of each Reuleaux layer

     // Draw the first layer
     glPushMatrix();
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(outerRadius, height); // Outer Reuleaux
     glPopMatrix();

     // Draw the second layer (gap-filled with the first)
     glPushMatrix();
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(innerRadius, height); // Inner Reuleaux
     drawFilledGapBetweenReuleaux(outerRadius, innerRadius, height); // Fill the gap
     glPopMatrix();

     // Parameters for the second stacked set
     float secondOuterRadius = innerRadius; // Outer radius for the second set
     float secondInnerRadius = 2.0f;        // Inner radius for the second set

     // Draw the third layer (outer of the second stacked set)
     glPushMatrix();
     glTranslatef(0.0f, 0.5f, 0.0f); // Move up to stack on top of the first set
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(secondOuterRadius, height);
     glPopMatrix();

     // Draw the fourth layer (inner of the second stacked set)
     glPushMatrix();
     glTranslatef(0.0f, 0.5f, 0.0f); // Move up to stack on top of the first set
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(secondInnerRadius, height);
     drawFilledGapBetweenReuleaux(secondOuterRadius, secondInnerRadius, height); // Fill the gap
     glPopMatrix();

     // Parameters for the third stacked set
     float thirdOuterRadius = secondInnerRadius; // Outer radius for the third set
     float thirdInnerRadius = 1.5f;             // Inner radius for the third set

     // Draw the fifth layer (outer of the third stacked set)
     glPushMatrix();
     glTranslatef(0.0f, 1.0f, 0.0f); // Move up to stack on top of the second set
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(thirdOuterRadius, height);
     glPopMatrix();

     // Draw the sixth layer (inner of the third stacked set)
     glPushMatrix();
     glTranslatef(0.0f, 1.0f, 0.0f); // Move up to stack on top of the second set
     glRotatef(90.0, -1.0f, 0.0f, 0.0f);
     drawReuleauxBaseWithLines(thirdInnerRadius, height);
     drawFilledGapBetweenReuleaux(thirdOuterRadius, thirdInnerRadius, height); // Fill the gap
     glPopMatrix();
 }


void drawSingaporeFlyer(){
    glPushMatrix();
    glTranslatef(25.5f, 0.0f, 18.5f);
    drawSingaporeFlyerWheel();
    drawStackedBase();
    glPopMatrix();
}

void drawCurvedTowerPair(float baseWidth, float height, float depth, float curvature) {
    glPushMatrix();
    
    float spacing = baseWidth * 1.5f;
    float segmentHeight = height / 20.0f;
    
    glColor3f(0.8f, 0.8f, 0.8f);
    
    // First tower - less curved
    for(int i = 0; i < 20; i++) {
        float y = i * segmentHeight;
        // Positive curve, reduced intensity
        float curveOffset = (curvature * 0.8f) * sin(y/height * M_PI);
        
        glPushMatrix();
        glTranslatef(curveOffset, y, 0.0f);
        
        glBegin(GL_QUADS);
        // Front face
        glVertex3f(-baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, depth/2);
        
        // Back face
        glVertex3f(-baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, segmentHeight, -depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, -depth/2);
        
        // Side faces
        glVertex3f(-baseWidth/2, 0.0f, -depth/2);
        glVertex3f(-baseWidth/2, 0.0f, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, -depth/2);
        
        glVertex3f(baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, -depth/2);
        glEnd();
        glPopMatrix();
    }
    
    // Second tower - more curved, opposite direction
    glPushMatrix();
    glTranslatef(spacing + baseWidth, 0.0f, 0.0f);
    // Add a slight rotation around Z axis (try adjusting the -5.0f angle as needed)
    glRotatef(6.0f, 0.0f, 0.0f, 0.5f);

    for(int i = 0; i < 20; i++) {
        float y = i * segmentHeight;
        float curveOffset = -(curvature * 3.0f) * sin(y/height * M_PI);
        
        glPushMatrix();
        glTranslatef(curveOffset, y, 0.0f);
            
        glBegin(GL_QUADS);
        // Same faces as first tower
        glVertex3f(-baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, depth/2);
        
        glVertex3f(-baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, segmentHeight, -depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, -depth/2);
        
        glVertex3f(-baseWidth/2, 0.0f, -depth/2);
        glVertex3f(-baseWidth/2, 0.0f, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, depth/2);
        glVertex3f(-baseWidth/2, segmentHeight, -depth/2);
        
        glVertex3f(baseWidth/2, 0.0f, -depth/2);
        glVertex3f(baseWidth/2, 0.0f, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, depth/2);
        glVertex3f(baseWidth/2, segmentHeight, -depth/2);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
    
    // Connecting elements
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    for(int i = 0; i < 20; i += 4) {
        float y = i * segmentHeight;
        float leftCurve = (curvature * 0.7f) * sin(y/height * M_PI);
        float rightCurve = -curvature * sin(y/height * M_PI);
        
        glVertex3f(leftCurve + baseWidth/2, y, 0.0f);
        glVertex3f(rightCurve + spacing + baseWidth/2, y, 0.0f);
        glVertex3f(rightCurve + spacing + baseWidth/2, y + segmentHeight, 0.0f);
        glVertex3f(leftCurve + baseWidth/2, y + segmentHeight, 0.0f);
    }
    glEnd();
    
    glPopMatrix();
}

void drawTopPlatform() {
    glPushMatrix();
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    float length = 10.0f;      // Reduced from 20.0f
    float width = 2.5f;        // Reduced from 5.0f
    float height = 0.5f;       // Reduced from 1.0f
    int segments = 100;        // Keep same smoothness
    float curveDepth = 0.5f;   // Reduced from 1.0f
    
    // Main platform
    glColor3f(0.8f, 0.8f, 0.8f);
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= segments; i++) {
        float t = (float)i / segments;
        float x = -length/2 + length * t;
        float z = curveDepth * sin(t * M_PI);
        
        glVertex3f(x, height, z + width/2);
        glVertex3f(x, height, z - width/2);
        glVertex3f(x, 0.0f, z + width/2);
        glVertex3f(x, 0.0f, z - width/2);
    }
    glEnd();
    
    // End cap (semicircle)
    int capSegments = 20;
    float endX = length/2;
    float endZ = curveDepth * sin(M_PI);
    
    // Top cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(endX, height, endZ);
    for(int i = 0; i <= capSegments; i++) {
        float angle = -M_PI/2 + (M_PI * i / capSegments);
        float capX = endX + (width/2) * cos(angle);
        float capZ = endZ + (width/2) * sin(angle);
        glVertex3f(capX, height, capZ);
    }
    glEnd();
    
    // Bottom cap
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(endX, 0.0f, endZ);
    for(int i = 0; i <= capSegments; i++) {
        float angle = -M_PI/2 + (M_PI * i / capSegments);
        float capX = endX + (width/2) * cos(angle);
        float capZ = endZ + (width/2) * sin(angle);
        glVertex3f(capX, 0.0f, capZ);
    }
    glEnd();
    
    glPopMatrix();
}


void drawMarinaBaySands() {
    glPushMatrix();
    // Adjust initial position for smaller scale
    glTranslatef(-14.0f, 0.0f, 28.0f);  // Reduced from (-10.0f, 0.0f, 28.0f)
    
    // Scaled down parameters
    float towerWidth = 0.75f;   // Reduced from 1.5f
    float towerHeight = 7.5f;   // Reduced from 15.0f
    float towerDepth = 2.5f;    // Reduced from 5.0f
    float curvature = 0.2f;     // Reduced from 0.4f
    
    // Rotate entire structure
    glRotatef(90, 0.0f, 0.0f, 0.0f);
    
    // Center pair
    drawCurvedTowerPair(towerWidth, towerHeight, towerDepth, curvature);

    // Left tower pair - reduce spacing
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.5f);  // Reduced from -7.0f
    glRotatef(8.0f, 0.0f, 1.0f, 0.0f);
    drawCurvedTowerPair(towerWidth, towerHeight, towerDepth, curvature);
    glPopMatrix();

    // Right tower pair
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 3.5f);   // Reduced from 7.0f
    glRotatef(-8.0f, 0.0f, 1.0f, 0.0f);
    drawCurvedTowerPair(towerWidth, towerHeight, towerDepth, curvature);
    glPopMatrix();

    // Top platform - adjust position for new scale
    glPushMatrix();
    glTranslatef(0.0f, 7.5f, 0.0f);   // Reduced from (2.0f, 15.0f, 0.0f)
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    drawTopPlatform();
    glPopMatrix();
        
    glPopMatrix();
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
    fillBayOutlineWithLand();

    glDisable(GL_DEPTH_TEST); 
    drawTrack();
    drawSingaporeFlyer();

   
    glEnable(GL_DEPTH_TEST);


    drawMarinaBaySands();


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

    if (key == 'Z')
        sceTX += 1;

    if (key == 'z')
        sceTX -= 1;


    glutPostRedisplay();
}

// Initialization function
void init(void) {
    glClearColor(0.0, 0.0, 0.1, 1.0);
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutIdleFunc(update);
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