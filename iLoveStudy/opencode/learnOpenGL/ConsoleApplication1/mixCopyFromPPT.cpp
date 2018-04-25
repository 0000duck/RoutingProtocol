//#include<gl/glut.h>
//
//
//void setLight(void)
//{
//	static const GLfloat light_position[] = { 1.0f, 1.0f, -1.0f, 1.0f };
//	static const GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
//	static const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	static const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
//	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
//	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
//	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_DEPTH_TEST);
//}
////每一个球体颜色不同。所以它们的材质也都不同。这里用一个函数来设置材质。
//void setMatirial(const GLfloat mat_diffuse[4], GLfloat mat_shininess)
//{
//	static const GLfloat mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	static const GLfloat mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mat_diffuse);
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
//	glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
//}
//
//
//void myDisplay(void)
//{
//	// 定义一些材质颜色
//	const static GLfloat red_color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//	const static GLfloat green_color[] = { 0.0f, 1.0f, 0.0f, 0.3333f };
//	const static GLfloat blue_color[] = { 0.0f, 0.0f, 1.0f, 0.5f };
//	// 清除屏幕
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	// 启动混合并设置混合因子
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	// 设置光源
//	setLight();
//	// 以(0, 0, 0.5)为中心，绘制一个半径为.3的不透明红色球体（离观察者最远）
//	setMatirial(red_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.0f, 0.0f, 0.5f);
//	glutSolidSphere(0.3, 30, 30);
//	glPopMatrix();
//	// 下面将绘制半透明物体了，因此将深度缓冲设置为只读
//	glDepthMask(GL_FALSE);
//	// 以(0.2, 0, -0.5)为中心，绘制一个半径为.2的半透明蓝色球体（离观察者最近）
//	setMatirial(blue_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.2f, 0.0f, -0.5f);
//	glutSolidSphere(0.2, 30, 30);
//	glPopMatrix();
//	// 以(0.1, 0, 0)为中心，绘制一个半径为.15的半透明绿色球体（在前两球之间）
//	setMatirial(green_color, 30.0);
//	glPushMatrix();
//	glTranslatef(0.1, 0, 0);
//	glutSolidSphere(0.15, 30, 30);
//	glPopMatrix();
//	// 完成半透明物体的绘制，将深度缓冲区恢复为可读可写的形式
//	glDepthMask(GL_TRUE);
//	glutSwapBuffers();
//	glFlush();
//
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
//	glutCreateWindow("混合CopyFromPPT");
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