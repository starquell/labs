#include <iostream>
#include <GL/freeglut.h>
#include <cmath>

using namespace std;

int count = 0;

struct Point{
    float x,   y;
};

Point p[6];                  // massive of coordinates

void Calculating() {

    float first[3] = {0.0};             //massive of sides
    for (int i = 0; i < 3; ++i)
        first[i] = hypotf(p[i].x - p[(i + 1) % 3].x, p[i].y - p[(i + 1) % 3].y);

    float second[3] = {
            hypotf(p[3].x - p[4].x, p[3].y - p[4].y),
            hypotf(p[4].x - p[5].x, p[4].y - p[5].y),
            hypotf(p[5].x - p[3].x, p[5].y - p[3].y)
    };

    int div[9] = {0};   //massive of sides' relations

    for (int i = 0; i < 3; ++i)
        div[i] = int(round((first[i] * 1 / second[i]) / 1));

    for (int i = 3; i < 6; ++i) {
        div[i] = int(round((first[i - 3] * 1 / second[i - 2]) / 1));
        if (i == 5)
            div[i] = int(round((first[i - 3] * 1 / second[0]) / 1));
    }

    for (int i = 6; i < 9; ++i) {
        div[i] = int(round((first[i - 6] * 1 / second[i - 6]) / 1));
        if (i == 6)
            div[i] = int(round((first[i - 6] * 1 / second[2]) / 1));
    }

    bool is = true;

    for (int c = 0, i = 0; c < 9; c += 3, ++i){
        if (div[c] == div[c + 1] && div[c] == div[c + 2]) {
            cout << "_______________________________________" << endl
                 << "Triangles are similar" << endl
                 << "_______________________________________" << endl;

            double xmovevector = (p[0].x + p[1].x + p[2].x) / 3 - (p[3].x + p[4].x + p[5].x) / 3;
            double ymovevector = (p[0].y + p[1].y + p[2].y) / 3 - (p[3].y + p[4].y + p[5].y) / 3;
            cout << "Vector for movement - (" << xmovevector << " ," << ymovevector << ")" << endl;

            cout << "Coefficient of similarity = " << first[0]/second[0] << endl;


            double arccos = acos((fabs(p[1+i].x - p[0+i].x) * fabs(p[4].x - p[3].x) +
                                  fabs(p[1+i].y - p[0+i].y) * fabs(p[4].y - p[3].y)) / (first[0+i] * second[0+i]));
            if(i == 2){
                arccos = acos((fabs(p[1+i].x - p[0+i].x) * fabs(p[4].x - p[3].x) +
                                  fabs(p[1+i].y - p[0+i].y) * fabs(p[4].y - p[3].y)) / (first[0+i] * second[0]));}
            cout << "Angle for combination = " << round(((arccos * 180) / 3.14) * 10) / 10 << endl;

            is = false;
            break;

        } if (i == 2 && is){
            cout << "________________________________" << endl
                 << "Triangles aren't similar" << endl;
        }
    }
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w , h, 0, -1, 1);
}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(255, 255, 255);
    glPointSize(8);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);

    for(int i = 0; i < count; ++i) {
        glVertex2f(p[i].x, p[i].y);
    };

    glEnd();
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && count < 6) {

        if(x%6 <= 3)
           x-= x % 6;
       if(x%6 >= 4)
           x+= 6 - x % 6;
       if(y%6 <= 3)
            y-= y % 6;
       if(y%6 >= 4)
            y+= 6 - y % 6;

        p [count].x = x;
        p [count].y = y;

        cout << x << " " << y <<endl;
        if (count == 5)
            Calculating();
        ++count;
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glClearColor(1,0,0,1.0);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1000, 200);

    glutCreateWindow("our triangles");
    glClearColor(0, 0, 0, 1);

    cout<<"Clicked points:"<<endl;
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
