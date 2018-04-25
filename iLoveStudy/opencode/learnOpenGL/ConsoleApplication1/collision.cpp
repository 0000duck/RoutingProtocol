//#include <gl/glut.h>
//#include <cmath>
//#include <cstdlib>
//#include <windows.h>
//#include <ctime>
//
//const int n = 5;
//const GLfloat R = 0.5f;
//const GLfloat Pi = asin(1) * 2;
//static int day = 0;
//const int windowWidth = 900;
//const int windowHeight = 900;
//float ax, ay, bx, by, cx, cy;
//int flag = 0;
//int i = 0;
//float arr[6];
//int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
//int flaga = 1, flagb = 1, flagc = 1, flagd = 1, flage = 1, flagf = 1;
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	glEnable(GL_BLEND);
//	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glBlendFunc(GL_ONE, GL_ONE);
//
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//
//	glPushMatrix();
//	glTranslatef(ax, ay, 0.0f);
//	glColor4f(1, 0, 0, 0.5);
//	glBegin(GL_TRIANGLES);
//	glVertex2f(-0.7, -0.7);
//	glVertex2f(0.3, -0.7);
//	glVertex2f(-0.2, 0.3);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(bx, by, 0.0f);
//	glColor4f(0, 0, 1, 0.5);
//	glBegin(GL_POLYGON);
//	//for (int i = 0; i<n; ++i)
//	//glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
//	glVertex2f(0.0f, 0.0f);
//	glVertex2f(0.5f, 0.0f);
//	glVertex2f(0.5f, 0.5f);
//	glVertex2f(0.0f, 0.5f);
//	glVertex2f(-0.5f, 0.5f);
//	glEnd();
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(cx, cy, 0.0f);
//	glColor4f(0, 1, 0, 0.5);
//	glRectf(-0.5, -0.5, 0.5, 0.5);
//	glPopMatrix();
//
//	glutSwapBuffers();
//}
//
//void myIdle(void)
//{
//	int fa = 1, fb = 1, fc = 1, fd = 1, fe = 1, ff = 1;
//	Sleep(150);
//	if (ax - 0.7 <= -1 || ax + 0.3 >= 1) { flaga = -flaga; }
//	if (ay - 0.7 <= -1 || ay + 0.3 >= 1) { flagd = -flagd; }
//	if (bx - 0.5 <= -1 || bx + 0.5 >= 1) { flagb = -flagb; }
//	if (by <= -1 || by + 0.5 >= 1) { flage = -flage; }
//	if (cx - 0.5 <= -1 || cx + 0.5 >= 1) { flagc = -flagc; }
//	if (cy - 0.5 <= -1 || cy + 0.5 >= 1) { flagf = -flagf; }
//	if (flaga == fa) { a++; }
//	else a--;
//	if (flagd == fd) { d++; }
//	else d--;
//	if (flagb == fb) { b++; }
//	else b--;
//	if (flage == fe) { e++; }
//	else e--;
//	if (flagc == fc) { c++; }
//	else c--;
//	if (flagf == ff) { f++; }
//	else f--;
//	if (flag == 0)
//	{
//		for (int j = 0; j < 6; j++)arr[j] = (rand() % 10 - 5) / 100.0;
//
//		ax = arr[0];
//		bx = arr[1];
//		cx = arr[2];
//		ay = arr[3];
//		by = arr[4];
//		cy = arr[5];
//		flag = 1;
//	}
//	else
//	{
//		ax = arr[0] * a;
//		bx = arr[1] * b;
//		cx = arr[2] * c;
//		ay = arr[3] * d;
//		by = arr[4] * e;
//		cy = arr[5] * f;
//	}
//	myDisplay();
//}
//
//
//int main(int argc, char *argv[])
//{
//	srand(time(0));
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(500, 500);
//	glutCreateWindow("Åö×²");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}