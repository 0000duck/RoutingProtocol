//#include<gl/glut.h>
//#include<math.h>
//
//const int n = 40;
//const GLfloat R = 0.5f;
//const GLfloat Pi = 3.1415926536f;
//const GLfloat factor = 0.1f;
//
////======================����/�߱���=======================
//void myDisplay0(void)
//{
//	GLfloat arr[][3] = { {0.5,1,1 },{ 1, 0.5,0.3 },{ 0.2, 0.5,0.4 },{ 0.5,1,0.1 },{ 1, 0.5,1 },{ 0.2, 0.2,0.4 } ,{ 0.5,1,1 },{ 0.2, 0.5,1 },{ 0.2, 0.3,0.4 } ,{ 0.5,1,0.7 },{ 1, 0.5,0.2 },{ 0.5, 0.2,0.6 } };
//
//	int i;
//	GLfloat j = 0.1f;;
//
//
//	glClear(GL_COLOR_BUFFER_BIT);//��ʾ�����ɫ
//		glBegin(GL_LINES);//����
//		//glShadeModel(GL_FLAT);
//		//glColor3f(1.0f, 0.0f, 0.0f);
//		for (i = 1; i < n ; i++)
//		{
//		//	glColor3f(arr[i % 10][0], arr[i % 10][1], arr[i % 10][2]);
//			glColor3f(i & 0x02, i & 0x06, i & 0x01);
//			//glVertex2f(R*cos(2 * Pi /6*i), R*sin(2 * Pi / 6*i ));
//			glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//			glVertex2f(R*cos(2 * Pi / 7 * (i+1)), R*sin(2 * Pi / 7 * (i+1)));
//		}
//		glEnd();
//		glFlush();//��֤ǰ���OpenGL��������ִ�У��������������ڻ������ȴ���
//}
//
//////=========================����һ��ͼ��============================
//void myDisplay1(void)
//{
//	GLfloat R1 = 0.25f;
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//�������㻭X��
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//�������㻭y��
//	glEnd();
//
//	glBegin(GL_LINE_STRIP);
//	for (GLfloat i = 0; i<2 * Pi; i += 0.01f)
//	{
//		glVertex2f(R1*(2 * sin(i) - sin(2 * i)), R1*(2 * cos(i) - cos(2 * i)));
//	}
//	glEnd();
//	glFlush();
//
//}
//
//	////=========================���ڶ���ͼ��============================
//void myDisplay2(void)
//{
//	GLfloat R1 = 0.25f;
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//�������㻭X��
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//�������㻭y��
//	glEnd();
//
//	glBegin(GL_LINE_STRIP);
//	for (GLfloat i = 0; i<61; i++)
//	{
//		glVertex2f(0.0005*(-pow(i, 2) + 40 * i + 1200)*sin(Pi*i / 180), 0.0005*(-pow(i, 2) + 40 * i + 1200)*cos(Pi*i / 180));
//	}
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	for (GLfloat i = 0; i<61; i++) 
//	{
//		glVertex2f(-0.0005*(-pow(i, 2) + 40 * i + 1200)*sin(Pi*i / 180), 0.0005*(-pow(i, 2) + 40 * i + 1200)*cos(Pi*i / 180));
//	}
//	glEnd();
//	glFlush();
//
//
//
//	//for (GLfloat x = 1; x<n; x++)
//	//for (GLfloat x = 0; x < 2 * Pi; x += 0.01f)
//	//for (GLfloat x = 1; x < n; x++)
//	//{
//	//	//x = 16 * sin(i)*sin(i)*sin(i) / 20;
//	//	y = (pow(x, 2 / 3) + pow((pow(x, 4 / 3) - 4 * x*x + 4), 1 / 2))/2;
//	//	glVertex2f(x/50, y/50);
//	//}
//
//}
//
//	//////=========================�� �桤������ͼ��============================
//void myDisplay3(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//�������㻭X��
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//�������㻭y��
//	glEnd();
//
//	glBegin(GL_LINE_STRIP);
//	for (GLfloat i = -1; i <= 1; i += 0.01f)
//	{
//
//		x = sin(i)*cos(i)*log(fabs(i));
//		y = sqrt(fabs(i))*cos(i);
//		glVertex2f(x, y);
//	}
//	glEnd();
//	glFlush();
//}
//
//	//////=========================�����ĸ�ͼ��============================
//void myDisplay41(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//�������㻭X��
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//�������㻭y��
//	glEnd();
//	
//	glBegin(GL_LINE_STRIP);
//	for (double x = -6; x < 6; x += 0.01f)
//	{
//		double y = 2 * (fabs(x) + x * x - 6) / (3 * (fabs(x) + x * x + 2)) + sqrt(36 - x * x);
//		glVertex2f(x / 10, y / 10 - 0.05f);
//	}
//	glEnd();
//	glBegin(GL_LINE_STRIP);
//	for (double x = -6; x < 6; x += 0.01f)
//	{
//		double y = 2 * (fabs(x) + x * x - 6) / (3 * (fabs(x) + x * x + 2)) - sqrt(36 - x * x);
//		glVertex2f(x / 10, y / 10 - 0.05f);
//	}
//	glEnd();
//	glFlush();
//}
//
//	//////=========================ɨ��ʵ�ֵ��ĸ�ͼ��============================
//void myDisplay42(void)
//{
//	GLfloat i;
//	GLfloat j;
//	glClear(GL_COLOR_BUFFER_BIT);
//	glBegin(GL_POINTS);
//	for (i = -5.0f; i < 5.0f; i += 0.001f)
//	{
//		for (j = -5.0f; j < 5.0f; j += 0.001f)
//		{
//			if (pow(i*i + j*j - 1, 3) - i*i*j*j*j < 0.0001f &&pow(i*i + j*j - 1, 3) - i*i*j*j*j > -0.0001f)
//				glVertex2f(i / 2, j / 2);
//		}
//	}
//	glEnd();
//	glFlush();
//
//}
//
//	//////=========================�������ͼ��============================
//void myDisplay51(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//�������㻭X��
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//�������㻭y��
//	glEnd();
//
//	glBegin(GL_LINE_STRIP);
//	for (GLfloat i = 0; i<2 * Pi; i += 0.01f)
//	{
//		x = 16 * sin(i)*sin(i)*sin(i)/30;
//		y = (13 * cos(i) - 5 * cos(2 * i) - 2 * cos(3 * i) - cos(4 * i))/30;
//		glVertex2f(x, y);
//	}
//	glEnd();
//	glFlush();
//}
//
//	//////=========================ɨ��ʵ�ֵ����ͼ��============================
//void myDisplay52(void)
//{
//GLfloat i;
//GLfloat j;
//GLfloat m;
//glClear(GL_COLOR_BUFFER_BIT);
//glBegin(GL_POINTS);
//for (i = -10.0f; i < 10.0f; i += 0.01f)
//{
//	for (j = -10.0f; j < 10.0f; j += 0.01f)
//	{
//		m = 2 * (fabs(i) + i*i - 6) / (3 * (fabs(i) + i*i + 2));
//		if ((j - m)*(j - m) + i*i < 37.0f && (j - m)*(j - m) + i*i > 35.0f)
//			glVertex2f(i / 10, j / 10);
//	}
//}
//glEnd();
//glFlush();
//}
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
//	glutInitWindowPosition(100, 100);
//
//	//���ô��ڴ�С
//	glutInitWindowSize(400, 400);
//
//	//����ǰ�����õ���Ϣ�������ڡ�����������Ϊ���ڵı���
//	//���ڱ������󣬲���������ʾ����Ļ�ϡ���Ҫ����glutMainLoop���ܿ�������
//	glutCreateWindow("������");
//
//	//ÿ��GLUTȷ��һ�����ڵ�������Ҫ������ʾʱ��ͨ��glutDisplayFunc()��ע����Ǹ��ص������ͻᱻִ��
//	//Ӧ�ð��ػ泡������Ҫ�����д��붼���������ʾ�ص�������
//
//
//	glutDisplayFunc(&myDisplay0);
//	//glutDisplayFunc(&myDisplay1);
//	//glutDisplayFunc(&myDisplay2);
//	//glutDisplayFunc(&myDisplay3);
//	//glutDisplayFunc(&myDisplay41);
//	//glutDisplayFunc(&myDisplay42);
//	//glutDisplayFunc(&myDisplay51);
//	//glutDisplayFunc(&myDisplay52);
//
//	//�����Ѿ������Ĵ��ڽ����ڴ�ʱ��ʾ����Щ���ڵ���ȾҲ��ʼ��Ч
//	//�¼�����ѭ����ʼ��������ע�����ʾ�ص�������������һ������ѭ����������Զ�����˳�
//	glutMainLoop();
//	return 0;
//}