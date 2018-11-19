#include "./src/branch.h"
#include "./src/triangle_branch.h"
#define PI 3.1415
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <math.h>
#include <vector>
#include <iostream>
#define INIT_POINT { 0, -1 }
#define WINSIZE 800

branch *br = NULL;
int op = 0;
double rX = 0;
double rY = 0;
double rZ = 0;

void drawBranch( branch *br, double initialPoint[2] ) {

    for ( int i = 0; i < br->get_childs().size(); i++ ) {
        glLineWidth((br->get_childs())[i]->get_width());
        glBegin(GL_LINES);
            glColor3f(1.0, 1.0, 1.0);
            glVertex2f( initialPoint[0] , initialPoint[1] );
            glVertex2f( initialPoint[0] + cos(((br->get_childs())[i])->get_angle()) * (br->get_childs()[i])->get_length() / WINSIZE, initialPoint[1] + sin((br->get_childs()[i])->get_angle()) * (br->get_childs()[i])->get_length() / WINSIZE);
        glEnd();
        double tail[] = {(initialPoint[0] + cos((br->get_childs()[i])->get_angle()) * (br->get_childs()[i])->get_length() / WINSIZE) , (initialPoint[1] + sin((br->get_childs()[i])->get_angle()) * (br->get_childs()[i])->get_length() / WINSIZE)};

        try {
            drawBranch ( br->get_childs()[i] , tail );
        } catch (const std::bad_alloc &e) {
            std::cout << "Allocation failed " << e.what() << " at level: " << (br->get_childs()[i])->get_level() << std::endl;
        }
    }

}

void drawTree() {

    double initialPoint[] = INIT_POINT;
    if (op) {
        br = NULL;
        br = new branch( 4, 300 + rZ, 20, PI/2 );
    } else {
        br = NULL;
        br = new triangle_branch( 4 , 300 + rZ, 20, PI/2);
    }

    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glLineWidth(br->get_width());
    glBegin(GL_LINES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex2f( initialPoint[0] + rX , initialPoint[1] + rY );
        glVertex2f( initialPoint[0] + rX, initialPoint[1] +  br->get_length()/WINSIZE + rY);
    glEnd();

    double tail[] = {(initialPoint[0]) + rX , (initialPoint[1] + br->get_length() / WINSIZE + rY)};
    drawBranch ( br, tail );

    delete br;
    glFlush();
    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y) {

    std::cout << key << std::endl;
    if (key == 'w') {
        rY += 0.1;
    }
    else if (key == 's') {
        rY -= 0.1;
    }
    else if (key == 'a') {
        rX -= 0.1;
    }
    else if (key == 'd') {
        rX += 0.1;
    }
    else if (key == '+') {
        rZ += 10;
    }
    else if (key == '-') {
        rZ -= 10;
    }
    else if (key == 'c') {
        op = 1;
    }
    else if (key == 't') {
        op = 0;
    }



    glutPostRedisplay();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(1600, 900);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tree Fractal");
    glutDisplayFunc(drawTree);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;

}
