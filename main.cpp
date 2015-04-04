#include <iostream>
#include <sstream>
#include <GL/freeglut.h>

#define NUM_SQUARES 2

using namespace std;

void init();
void display();
void idleFunc();
void normalKeys(unsigned char key, int x, int y);
void normalKeysUp(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

GLfloat xPos[NUM_SQUARES];
GLfloat yPos[NUM_SQUARES];
GLfloat color[NUM_SQUARES][3];
GLfloat speed = 0.001;
GLint curSquare;
stringstream strstream1, strstream2;

enum key_state {
    INACTIVE, ACTIVE
} keyStatus[127];

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Keyboard Test");
    glutDisplayFunc(display);
    glutKeyboardFunc(normalKeys);
    glutKeyboardUpFunc(normalKeysUp);
    glutSpecialFunc(specialKeys);
    glutIdleFunc(idleFunc);

    init();

    glutMainLoop();

    return 0;
}

void init() {

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-5, 5, -5, 5);

    for (int i = 0; i < NUM_SQUARES; ++i) {
        xPos[i] = yPos[i] = 0;
        color[i][0] = (rand()/(float)(RAND_MAX + 1)) + 1;
        color[i][1] = (rand()/(GLfloat)(RAND_MAX + 1)) + 1;
        color[i][2] = (rand()/(GLfloat)(RAND_MAX + 1)) + 1;
    }
    curSquare = NUM_SQUARES - 1;

    strstream1 << "Choose 1-" << NUM_SQUARES << " to select the square";
    strstream2 << "Square selected: " << curSquare+1;

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glColor3f(0, 0, 0);
    glRasterPos2f((GLfloat) -0.9, 0.9);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char const *) strstream1.str().c_str());

    glLoadIdentity();
    glRasterPos2d((GLfloat) -0.9, 0.7);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char const *) strstream2.str().c_str());

    glPushMatrix();
    for (int i = 0; i < NUM_SQUARES; ++i) {
        glLoadIdentity();
        glTranslatef(xPos[i], yPos[i], 0);
        glScalef(0.05, 0.05, 1);

        glColor3fv(color[i]);

        glBegin(GL_POLYGON);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();
    }
    glPopMatrix();

    glFlush();
}

void idleFunc() {

    for (int i = 0; i < NUM_SQUARES; ++i) {
        if (keyStatus['1'+i]) {
            curSquare = i;
            strstream2.str("");
            strstream2 << "Square selected: " << curSquare+1;
            break;
        }
    }

    if (keyStatus['w']) {
        yPos[curSquare] += speed;
        if (yPos[curSquare] >= 0.93)
            yPos[curSquare] = 0.93;
    }
    if (keyStatus['s']) {
        yPos[curSquare] -= speed;
        if (yPos[curSquare] <= -0.93)
            yPos[curSquare] = (GLfloat) -0.93;
    }
    if (keyStatus['d']) {
        xPos[curSquare] += speed;
        if (xPos[curSquare] >= 0.93)
            xPos[curSquare] = 0.93;
    }
    if (keyStatus['a']) {
        xPos[curSquare] -= speed;
        if (xPos[curSquare] <= -0.93)
            xPos[curSquare] = (GLfloat) -0.93;
    }
    glutPostRedisplay();
}

void normalKeys(unsigned char key, int x, int y) {
    keyStatus[key] = ACTIVE;
}

void normalKeysUp(unsigned char key, int x, int y) {
    keyStatus[key] = INACTIVE;
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            yPos[1] += speed;
            if (yPos[1] >= 0.93)
                yPos[1] = 0.93;
            break;
        case GLUT_KEY_DOWN:
            yPos[1] -= speed;
            if (yPos[1] <= -0.93)
                yPos[1] = (GLfloat) -0.93;
            break;
        case GLUT_KEY_RIGHT:
            xPos[1] += speed;
            if (xPos[1] >= 0.93)
                xPos[1] = 0.93;
            break;
        case GLUT_KEY_LEFT:
            xPos[1] -= speed;
            if (xPos[1] <= -0.93)
                xPos[1] = (GLfloat) -0.93;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}