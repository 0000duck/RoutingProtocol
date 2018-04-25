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
//	//glutInitWindowPosition(100, 100);
//	glutInitWindowPosition(100, 100);
//
//	//设置窗口大小
//	glutInitWindowSize(500, 500);
//
//	//根据前面设置的信息创建窗口。参数将被作为窗口的标题
//	//窗口被创建后，并不立即显示到屏幕上。需要调用glutMainLoop才能看到窗口
//	glutCreateWindow("evolent");
//
//	//每当GLUT确定一个窗口的内容需要重新显示时，通过glutDisplayFunc()所注册的那个回调函数就会被执行
//	//应该把重绘场景所需要的所有代码都放在这个显示回调函数里
//	glutDisplayFunc(&myDisplay);
//
//	//所有已经创建的窗口将会在此时显示，这些窗口的渲染也开始生效
//	//事件处理循环开始启动，已注册的显示回调函数被触发。一旦进入循环，它就永远不会退出
//	glutMainLoop();
//	return 0;
//}