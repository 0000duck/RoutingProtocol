//#include<GL/GLUT.H>    
//#include <windows.h>        
//#include <math.h>        
//#include <gl/GL.h>        
//
//#define pi 3.1415927f;  
//float a = 0.5f;
//float u = sqrtf(2.0) / 3;
//float v = float(1 / 3);
//float t = sqrtf(6.0) / 3;
//
//static const GLfloat vertex_list[][3] = {
//	0.0f   , 0.0f  ,  a   ,
//	-2 * a*u , 0,0   , -a*v ,
//	a*u    , a*t   , -a*v ,
//	a*u    , -a*t  , -a*v ,
//};
//
//static const GLint index_list[][3] = {
//	0, 1, 2,
//	0, 1, 2,
//	0, 1, 3,
//	1, 2, 3,
//};
//
//
//
//void myDisplay(void) {
//	glClear(GL_COLOR_BUFFER_BIT);
//	glRotatef(45, 1, 1, 1);
//	glFrontFace(GL_CCW);
//
//	for (int i = 0; i < 4; ++i)      // 有四个面，循环六次  
//	{
//		glPolygonMode(GL_FRONT, GL_FILL);//设置正面为填充模式
//		//glBegin(GL_LINE_LOOP);
//			glBegin(GL_POLYGON);//按逆时针绘制
//		for (int j = 0; j < 3; ++j)     // 每个面有四个顶点，循环四次  
//		{
//			//glColor3f(0.2f*j, 0.5f, 0.5f);
//			glColor3f(i & 0x02, i & 0x06, i & 0x01);
//			glVertex3fv(vertex_list[index_list[i][j]]);
//		}
//		glEnd();
//
//		//void glColor3f(GLfloat red, GLfloat green, GLfloat blue);
//		//void glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
//		//将浮点数作为参数，其中0.0表示不使用该种颜色，而1.0表示将该种颜色用到最多。
//		//ex:		glColor3f(1.0f, 0.0f, 0.0f);    表示不使用绿、蓝色，而将红色使用最多，于是得到最纯净的红色。
//		//		glColor3f(0.0f, 1.0f, 1.0f);    表示使用绿、蓝色到最多，而不使用红色。混合的效果就是浅蓝色。
//		//		glColor3f(0.5f, 0.5f, 0.5f);    表示各种颜色使用一半，效果为灰色。
//		//注意：glColor系列函数，在参数类型不同时，表示“最大”颜色的值也不同。
//		//	采用f和d做后缀的函数，以1.0表示最大的使用。
//		//	采用b做后缀的函数，以127表示最大的使用。
//		//	采用ub做后缀的函数，以255表示最大的使用。
//		//	采用s做后缀的函数，以32767表示最大的使用。
//		//	采用us做后缀的函数，以65535表示最大的使用。
//		//glColor3f(0.5f, 0.5f, 0.5f);
//		//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);
//		//glFlush();
//	}
//
//
//	glFlush();
//}
//
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("opengl1");
//	glutDisplayFunc(&myDisplay);
//	glutMainLoop();
//	return 0;
//}