#include <iostream>
#include <sstream>
#include <GL/freeglut.h>

#define NUM_SQUARES 4

using namespace std;

void init();
void display();
void idleFunc();
void normalKeys(unsigned char key, int x, int y);
void normalKeysUp(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void reshape(int w, int h);
void displayMessages();

GLfloat xPos[NUM_SQUARES];
GLfloat yPos[NUM_SQUARES];
GLfloat color[NUM_SQUARES][3];
GLfloat speed = 0.001;
GLint curSquare;
stringstream strstream1, strstream2, strstream3;

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
    glutReshapeFunc(reshape);

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
    strstream3 << "Help:\n\tw - up\n\ts - down\n\td - right\n\ta - left" << endl;

}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2, 2, -2 * (GLfloat) h / (GLfloat) w, 2 * (GLfloat) h / (GLfloat) w, -2, 2);
    else
        glOrtho(-2 * (GLfloat) w / (GLfloat) h, 2 * (GLfloat) w / (GLfloat) h, -2, 2, -2, 2);
    glMatrixMode(GL_MODELVIEW);
}

void displayMessages() {

    glLoadIdentity();
    glColor3f(0, 0, 0);
    glRasterPos2f((GLfloat) -1.9, 1.5);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, (unsigned char const *) strstream1.str().c_str());

    glLoadIdentity();
    glRasterPos2d((GLfloat) -1.9, 1.2);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char const *) strstream2.str().c_str());

    glLoadIdentity();
    glRasterPos2d((GLfloat) -1.9, -1.2);
    glutBitmapString(GLUT_BITMAP_HELVETICA_12, (unsigned char const *) strstream3.str().c_str());
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    displayMessages();

//    glPushMatrix();
    for (int i = 0; i < NUM_SQUARES; ++i) {
        glLoadIdentity();
        glTranslatef(xPos[i], yPos[i], 0);
        glScalef(0.1, 0.1, 1);

        glColor3fv(color[i]);

        glBegin(GL_POLYGON);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, 1);
        glVertex2f(-1, 1);
        glEnd();

        if (i == curSquare) {
            glColor3f(0, 0, 0);
            glBegin(GL_LINE_LOOP);
            glVertex2f(-1, -1);
            glVertex2f(1, -1);
            glVertex2f(1, 1);
            glVertex2f(-1, 1);
            glEnd();
        }

        glLoadIdentity();
        glColor3f(0, 0, 0);
        glRasterPos2f((GLfloat) (xPos[i]-0.02), (GLfloat) (yPos[i]-0.02));
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, '1'+i);
    }
//    glPopMatrix();

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
        if (yPos[curSquare] >= 1.9)
            yPos[curSquare] = 1.9;
    }
    if (keyStatus['s']) {
        yPos[curSquare] -= speed;
        if (yPos[curSquare] <= -1.9)
            yPos[curSquare] = (GLfloat) -1.9;
    }
    if (keyStatus['d']) {
        xPos[curSquare] += speed;
        if (xPos[curSquare] >= 1.9)
            xPos[curSquare] = 1.9;
    }
    if (keyStatus['a']) {
        xPos[curSquare] -= speed;
        if (xPos[curSquare] <= -1.9)
            xPos[curSquare] = (GLfloat) -1.9;
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