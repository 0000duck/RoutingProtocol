//#include<gl/glut.h>
//#include<math.h>
//
//const int n = 40;
//const GLfloat R = 0.5f;
//const GLfloat Pi = 3.1415926536f;
//const GLfloat factor = 0.1f;
//
////======================正六/七边形=======================
//void myDisplay0(void)
//{
//	GLfloat arr[][3] = { {0.5,1,1 },{ 1, 0.5,0.3 },{ 0.2, 0.5,0.4 },{ 0.5,1,0.1 },{ 1, 0.5,1 },{ 0.2, 0.2,0.4 } ,{ 0.5,1,1 },{ 0.2, 0.5,1 },{ 0.2, 0.3,0.4 } ,{ 0.5,1,0.7 },{ 1, 0.5,0.2 },{ 0.5, 0.2,0.6 } };
//
//	int i;
//	GLfloat j = 0.1f;;
//
//
//	glClear(GL_COLOR_BUFFER_BIT);//表示清除颜色
//		glBegin(GL_LINES);//折线
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
//		glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区等待）
//}
//
//////=========================画第一个图形============================
//void myDisplay1(void)
//{
//	GLfloat R1 = 0.25f;
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//这两个点画X轴
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//这两个点画y轴
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
//	////=========================画第二个图形============================
//void myDisplay2(void)
//{
//	GLfloat R1 = 0.25f;
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//这两个点画X轴
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//这两个点画y轴
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
//	//////=========================画 真·第三个图形============================
//void myDisplay3(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//这两个点画X轴
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//这两个点画y轴
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
//	//////=========================画第四个图形============================
//void myDisplay41(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//这两个点画X轴
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//这两个点画y轴
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
//	//////=========================扫描实现第四个图形============================
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
//	//////=========================画第五个图形============================
//void myDisplay51(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//	GLfloat x;
//	GLfloat y;
//	glBegin(GL_LINES);
//	glVertex2f(-1.0f, 0.0f);
//	glVertex2f(1.0f, 0.0f);//这两个点画X轴
//	glVertex2f(0.0f, -1.0f);
//	glVertex2f(0.0f, 1.0f);//这两个点画y轴
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
//	//////=========================扫描实现第五个图形============================
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
//int main(int argc, char*argv[])//带命令行参数的main函数
//{
//	//以glut开头的函数都是GLUT工具包所提供的函数
//
//	//对GLUT进行初始化，这个函数必须在其它的GLUT使用之前调用一次。
//	//格式死板，一般直接照抄
//	glutInit(&argc, argv);
//
//	//设置显示方式，其中GLUT_RGB表示使用RGB颜色，与之对应的还有GLUT_INDEX（表示使用索引颜色）
//	//GLUT_SINGLE表示使用单缓冲，与之对应的还有GLUT_DOUBLE（使用双缓冲）
//	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
//
//	//设置窗口在屏幕中的位置
//	glutInitWindowPosition(100, 100);
//
//	//设置窗口大小
//	glutInitWindowSize(400, 400);
//
//	//根据前面设置的信息创建窗口。参数将被作为窗口的标题
//	//窗口被创建后，并不立即显示到屏幕上。需要调用glutMainLoop才能看到窗口
//	glutCreateWindow("心形线");
//
//	//每当GLUT确定一个窗口的内容需要重新显示时，通过glutDisplayFunc()所注册的那个回调函数就会被执行
//	//应该把重绘场景所需要的所有代码都放在这个显示回调函数里
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
//	//所有已经创建的窗口将会在此时显示，这些窗口的渲染也开始生效
//	//事件处理循环开始启动，已注册的显示回调函数被触发。一旦进入循环，它就永远不会退出
//	glutMainLoop();
//	return 0;
//}