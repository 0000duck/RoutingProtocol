//#include <GL/glut.h>
//#include <math.h>
//
//const GLint n = 100;
//const GLint m = 12;
//const GLfloat R = 0.5f;
//const GLfloat Pi = 3.1415926f;
//
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_LINE_LOOP);
//	glPointSize(3.0f);
//	for (int i = 0; i < n; ++i)
//	{
//		glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
//	}
//	for (float a = 0; a<=2*Pi;a+=Pi/m)
//	{
//		glVertex2f(R*cos(a) + R*sin(a), R*sin(a) - R*cos(a));
//		for (int i = 0; i < m; ++i)
//		{
//			glVertex2f(R*cos(2 * Pi / m * i), R*sin(2 * Pi / m * i));
//			glVertex2f(R*cos(a) + R*sin(a), R*sin(a) - R*cos(a));
//		}
//	}
//	glEnd();
//	glFlush();
//}
//
//
//int main(int argc, char*argv[])//�������в�����main����
//{
//	//��glut��ͷ�ĺ�������GLUT���߰����ṩ�ĺ���
//
//	//��GLUT���г�ʼ�����������������������GLUTʹ��֮ǰ����һ�Ρ�
//	//��ʽ���壬һ��ֱ���ճ�
//	glutInit(&argc, argv);
//
//	//������ʾ��ʽ������GLUT_RGB��ʾʹ��RGB��ɫ����֮��Ӧ�Ļ���GLUT_INDEX����ʾʹ��������ɫ��
//	//GLUT_SINGLE��ʾʹ�õ����壬��֮��Ӧ�Ļ���GLUT_DOUBLE��ʹ��˫���壩
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//
//	//���ô�������Ļ�е�λ��
//	//glutInitWindowPosition(100, 100);
//	glutInitWindowPosition(100, 100);
//
//	//���ô��ڴ�С
//	glutInitWindowSize(500, 500);
//
//	//����ǰ�����õ���Ϣ�������ڡ�����������Ϊ���ڵı���
//	//���ڱ������󣬲���������ʾ����Ļ�ϡ���Ҫ����glutMainLoop���ܿ�������
//	glutCreateWindow("evolent");
//
//	//ÿ��GLUTȷ��һ�����ڵ�������Ҫ������ʾʱ��ͨ��glutDisplayFunc()��ע����Ǹ��ص������ͻᱻִ��
//	//Ӧ�ð��ػ泡������Ҫ�����д��붼���������ʾ�ص�������
//	glutDisplayFunc(&myDisplay);
//
//	//�����Ѿ������Ĵ��ڽ����ڴ�ʱ��ʾ����Щ���ڵ���ȾҲ��ʼ��Ч
//	//�¼�����ѭ����ʼ��������ע�����ʾ�ص�������������һ������ѭ����������Զ�����˳�
//	glutMainLoop();
//	return 0;
//}