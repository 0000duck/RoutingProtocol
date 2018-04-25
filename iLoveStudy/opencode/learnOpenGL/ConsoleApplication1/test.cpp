//#include <gl/glut.h>
//#include<math.h>
//
//#define WIDTH 400
//#define HEIGHT 400
//
//static GLfloat angle = 0.0f;
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	{
//		const int n = 40;
//		const GLfloat R = 0.2f;
//		const GLfloat Pi = 3.1415926536f;
//		int i;
//		GLfloat j = 0.1f;
//
//		glBegin(GL_LINES);//折线
//						  //glShadeModel(GL_FLAT);
//						  //glColor3f(1.0f, 0.0f, 0.0f);
//		for (i = 1; i < n; i++)
//		{
//			glColor3f(1.0f, 1.0f, 1.0f);
//			glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//			glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//		}
//		glEnd();
//		//glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区等待）
//	}
//
//
//	glutSwapBuffers();
//}
//void myIdle(void)
//{
//	angle += 0.1f;
//	if (angle >= 360.0f)
//		angle = 0.0f;
//	myDisplay();
//}
//
//int main(int argc, char* argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
//	glutInitWindowPosition(200, 200);
//	glutInitWindowSize(WIDTH, HEIGHT);
//	glutCreateWindow("OpenGL光照演示");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}