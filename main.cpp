#include <iostream>
#include <GL/glut.h>

using namespace std;

void display();
void normalKeys(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);

GLfloat offset_x[2] = {0, 0};
GLfloat offset_y[2] = {0, 0};
GLfloat speed = 0.1;

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Keyboard Test");
    glutDisplayFunc(display);
    glutKeyboardFunc(normalKeys);
    glutSpecialFunc(specialKeys);

    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-5, 5, -5, 5);
//    glPointSize(10);

    glutMainLoop();

    return 0;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Perform transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(offset_x[0], offset_y[0], 0);
    glScalef(0.05, 0.05, 1);

    // Draw a square
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    glLoadIdentity();
    glTranslatef(offset_x[1], offset_y[1], 0);
    glScalef(0.05, 0.05, 1);

    // Draw a square
    glColor3f(1, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    glFlush();
}

void normalKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            offset_y[0] += speed;
//            cout << "Offset y: " << offset_y << endl;
            if (offset_y[0] >= 0.93)
                offset_y[0] = 0.93;
            break;
        case 's':
            offset_y[0] -= speed;
            if (offset_y[0] <= -0.93)
                offset_y[0] = (GLfloat) -0.93;
            break;
        case 'd':
            offset_x[0] += speed;
            if (offset_x[0] >= 0.93)
                offset_x[0] = 0.93;
            break;
        case 'a':
            offset_x[0] -= speed;
            if (offset_x[0] <= -0.93)
                offset_x[0] = (GLfloat) -0.93;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            offset_y[1] += speed;
//            cout << "Offset y: " << offset_y << endl;
            if (offset_y[1] >= 0.93)
                offset_y[1] = 0.93;
            break;
        case GLUT_KEY_DOWN:
            offset_y[1] -= speed;
            if (offset_y[1] <= -0.93)
                offset_y[1] = (GLfloat) -0.93;
            break;
        case GLUT_KEY_RIGHT:
            offset_x[1] += speed;
            if (offset_x[1] >= 0.93)
                offset_x[1] = 0.93;
            break;
        case GLUT_KEY_LEFT:
            offset_x[1] -= speed;
            if (offset_x[1] <= -0.93)
                offset_x[1] = (GLfloat) -0.93;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}