#include "./src/branch.h"
#define PI 3.1415
#include "GL/freeglut.h"
#include "GL/gl.h"
#include <math.h>
#include <vector>
#include <iostream>
#define INIT_POINT { 0, -1 }
#define WINSIZE 800

branch *br = NULL;
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
    br = new branch( 5, 300 + rZ, 20, PI/2 );

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

void keyboard(int key, int x, int y) {

    std::cout << key << std::endl;
    if (key == GLUT_KEY_RIGHT) {
        rX += 0.1;
    }
    else if (key == GLUT_KEY_LEFT) {
        rX -= 0.1;
    }
    else if (key == GLUT_KEY_DOWN) {
        rY -= 0.1;
    }
    else if (key == GLUT_KEY_UP) {
        rY += 0.1;
    }
    else if (key == 112) {
        rZ += 10;
    }
    else if (key == 114) {
        rZ -= 10;
    }

    glutPostRedisplay();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(WINSIZE, WINSIZE);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Tree Fractal");
    glutDisplayFunc(drawTree);
    glutSpecialFunc(keyboard);
    glutMainLoop();
    return 0;

}
