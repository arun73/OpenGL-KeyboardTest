#include <iostream>
#include <GL/glut.h>

using namespace std;

void display();
void keyboard(unsigned char key, int x, int y);

GLfloat offset_x = 0;
GLfloat offset_y = 0;
GLfloat speed = 0.01;

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("OpenGL Keyboard Test");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

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
    glTranslatef(offset_x, offset_y, 0);
    glScalef(0.05, 0.05, 1);

    // Draw a square
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w':
            offset_y += speed;
            break;
        case 's':
            offset_y -= speed;
            break;
        case 'a':
            offset_x -= speed;
            break;
        case 'd':
            offset_x += speed;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}