//#include<gl/glut.h>
//#include<math.h>
//
//const int n = 40;
//const GLfloat R = 0.15f;
//const GLfloat Pi = 3.1415926536f;
//const GLfloat factor = 0.1f;
//
//
////我们写：glClear(GL_COLOR_BUFFER_BIT);意思是把屏幕上的颜色清空。
//
////OpenGL用函数来定义清楚屏幕后屏幕所拥有的颜色。
////在RGB模式下，使用glClearColor来指定“空”的颜色，它需要四个参数，其参数的意义跟glColor4f相似。
////在索引颜色模式下，使用glClearIndex来指定“空”的颜色所在的索引，它需要一个参数，其意义跟glIndexi相似。
////	1 void myDisplay(void)
////	2 {
////	3      glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
////	4      glClear(GL_COLOR_BUFFER_BIT);
////	5      glFlush();
////	6 }
//
//
////“点”
//
////点”是一切的基础。 OpenGL提供了一系列函数指定一个点。它们都以glVertex开头，后面跟一个数字和1~2个字母。
////例如：
////glVertex2d
////glVertex2f
////glVertex3f
////glVertex3fv 等等。
////数字表示参数的个数：2表示有两个参数，3表示三个，4表示四个。
////字母表示参数的类型：
////s表示16位整数（OpenGL中将这个类型定义为GLshort），
////i表示32位整数（OpenGL中将这个类型定义为GLint和GLsizei），
////f 表示32位浮点数（OpenGL中将这个类型定义为GLfloat和GLclampf），
////d表示64位浮点数（OpenGL中将这个类型定义为GLdouble和GLclampd）。
////v表示传递的几个参数将使用指针的方式，见下面的例子。
////这些函数除了参数的类型和个数不同以外，功能是相同的。例如，以下五个代码段的功能是等效的：
////（一）glVertex2i(1, 3);
////（二）glVertex2f(1.0f, 3.0f);
////（三）glVertex3f(1.0f, 3.0f, 0.0f);
////（四）glVertex4f(1.0f, 3.0f, 0.0f, 1.0f);
////（五）GLfloat VertexArr3[] = { 1.0f, 3.0f, 0.0f };
////glVertex3fv(VertexArr3);
////OpenGL的很多函数都是采用这样的形式。
////
////OpenGL中描述一个面（线、点）的方法是glBegin / glEnd命令组：
////glBegin(形状);
////glVertex(顶点1);
////glVertex(顶点2);
////……
////glEnd();
////
////void glPointSize(GLfloat size);
////size必须大于0.0f，默认值为1.0f，单位为“像素”。
////注意：对于具体的OpenGL实现，点的大小都有个限度的，如果设置的size超过最大值，则设置可能会有问题
//
//
////“线”
//
////直线可以指定宽度
////void glLineWidth(GLfloat width);
////其用法跟glPointSize类似。
////
////与OpenGL画点函数十分类似，不同在于glBegin()中的符号常量。
////使用图元常量GL_LINES可连接每一对相邻定点而得到一组直线段。
////1 　glBegin(GL_LINES);
////2 　　    glVertex2iv(p1);
////3 　　    glVertex2iv(p2);
////4 　　    glVertex2iv(p3);
////5 　　    glVertex2iv(p4);
////6 　　    glVertex2iv(p5);
////7 　glEnd();
////上述代码可以画出线段p1-p2和p3-p4。
////
////　　使用GL_LINE_STRIP则可以获得折线，如果需要封闭的折线则需要重复某些点坐标。
////1 　　glBegin(GL_LINE_STRIP);
////2 　　    glVertex2iv(p1);
////3 　　    glVertex2iv(p2);
////4 　　    glVertex2iv(p3);
////5 　　    glVertex2iv(p4);
////6 　　    glVertex2iv(p5);
////7 　　glEnd();
////上述代码画出折线p1-p2-p3-p4-p5。
////生成封闭折线的常量是GL_LINE_LOOP。
//
//
////“虚线”
//
////首先，使用glEnable(GL_LINE_STIPPLE);来启动虚线模式（使用glDisable(GL_LINE_STIPPLE)可以关闭之）。
////然后，使用glLineStipple来设置虚线的样式。
////void glLineStipple(GLint factor, GLushort pattern);
////pattern是由1和0组成的长度为16的序列，从最低位开始看，如果为1，则直线上接下来应该画的factor个点将被画为实的；如果为0，则直线上接下来应该画的factor个点将被画为虚的
//
//
////“多边形”
//
////GL_POLYGON用于画多边形
////多边形无法绘制非凸多边形,
////但可以用glPolygonMode函数改变多边形绘制的模式，绘制其轮廓
////
////下面从四个方面详细介绍下多边形的绘制问题：
////
////（1）多边形的两面以及绘制方式。
////
////从三维的角度来看，一个多边形具有两个面。每一个面都可以设置不同的绘制方式：填充、只绘制边缘轮廓线、只绘制顶点，其中“填充”是默认的方式。可以为两个面分别设置不同的方式。
////glPolygonMode(GL_FRONT, GL_FILL);            // 设置正面为填充方式
////glPolygonMode(GL_BACK, GL_LINE);             // 设置反面为边缘绘制方式
////glPolygonMode(GL_FRONT_AND_BACK, GL_POINT); // 设置两面均为顶点绘制方式
////（2）反转
////一般约定为“顶点以逆时针顺序出现在屏幕上的面”为“正面”，另一个面即成为“反面”。生活中 常见的物体表面，通常都可以用这样的“正面”和“反面”，“合理的”被表现出来（请找一个比较透明的矿泉水瓶子，在正对你的一面沿逆时针画一个圆，并标明 画的方向，然后将背面转为正面，画一个类似的圆，体会一下“正面”和“反面”。你会发现正对你的方向，瓶的外侧是正面，而背对你的方向，瓶的内侧才是正 面。正对你的内侧和背对你的外侧则是反面。这样一来，同样属于“瓶的外侧”这个表面，但某些地方算是正面，某些地方却算是反面了）。
////但也有一些表面比较特殊。例如“麦比乌斯带”（请自己Google一下），可以全部使用“正面”或全部使用“背面”来表示。
////可以通过glFrontFace函数来交换“正面”和“反面”的概念。
////glFrontFace(GL_CCW);   // 设置CCW方向为“正面”，CCW即CounterClockWise，逆时针
////glFrontFace(GL_CW);    // 设置CW方向为“正面”，CW即ClockWise，顺时针
//
//
//
//void myDisplay(void)
//{
//	//=========================画渐开线============================
//
//	int i;
//	glClear(GL_COLOR_BUFFER_BIT);//表示清除颜色
//	//glRectf(-0.5f, -0.5f, 0.5f, 0.5f);//画一个矩形。四个参数分别表示位于对角线上的两个点的横、纵坐标
//	//glBegin(GL_POLYGON);//填充
//	//glBegin(GL_LINE_LOOP);//描边
//
//
//
//
//	//把渐开线和里面的圆连起来
//	for (i = 0; i < n + 1; i++)
//	{
//		glBegin(GL_LINES);//连线
//		glVertex2f(R*(i*2*Pi / n*sin(i*2*Pi / n-(Pi/2)) + cos(i*2*Pi / n - (Pi / 2))), R*(sin(i*2*Pi / n - (Pi / 2)) - i*2*Pi / n*cos(i*2*Pi / n - (Pi / 2))));
//		glVertex2f(R*cos( 2*Pi / n*i - (Pi / 2)), R*sin(2*Pi / n*i - (Pi / 2)));
//	}
//	glEnd();
//
//	//画里面的圆
//	glBegin(GL_LINE_STRIP);//折线
//	for (i = 0; i < n + 1; i++)
//	{
//		glVertex2f(R*cos(2 * Pi / n*i - (Pi / 2)), R*sin(2 * Pi / n*i - (Pi / 2)));
//
//		//glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
//	}
//	glEnd();
//
//	//画渐开线
//	glBegin(GL_LINE_STRIP);//折线
//	for (i = 0; i < n + 1; i++)
//	{
//		glVertex2f(R*(i * 2 * Pi / n*sin(i * 2 * Pi / n - (Pi / 2)) + cos(i * 2 * Pi / n - (Pi / 2))), R*(sin(i * 2 * Pi / n - (Pi / 2)) - i * 2 * Pi / n*cos(i * 2 * Pi / n - (Pi / 2))));
//
//		//glVertex2f(R*(i * 2 * Pi / n*sin(i * 2 * Pi / n) + cos(i * 2 * Pi / n)), R*(sin(i * 2 * Pi / n) - i * 2 * Pi / n*cos(i * 2 * Pi / n)));
//
//	}
//	glEnd();
//
//
//	////=====================================尝试======================================
//
//	////把渐开线和里面的圆连起来
//	//for (int j = 1; j < 20; j++)
//	//{
//	//	for (i = 0; i < n + 1; i++)
//	//	{
//	//		glBegin(GL_LINE_STRIP);//连线
//	//		glVertex2f(R*(i * 2 * Pi / n*sin(i * 2 * Pi / n - j*(Pi / 6)) + cos(i * 2 * Pi / n - j*(Pi / 6))), R*(sin(i * 2 * Pi / n - j*(Pi / 6)) - i * 2 * Pi / n*cos(i * 2 * Pi / n - j*(Pi / 6))));
//	//		glVertex2f(R*cos(2 * Pi / n*i - j*(Pi / 6)), R*sin(2 * Pi / n*i - j*(Pi / 6)));
//	//	}
//	//	glEnd();
//
//	//	//画里面的圆
//	//	glBegin(GL_LINE_STRIP);//折线
//	//	for (i = 0; i < n + 1; i++)
//	//	{
//	//		glVertex2f(R*cos(2 * Pi / n*i - j*(Pi / 6)), R*sin(2 * Pi / n*i - j*(Pi / 6)));
//
//	//		//glVertex2f(R*cos(2 * Pi / n*i), R*sin(2 * Pi / n*i));
//	//	}
//	//	glEnd();
//
//	//	//画渐开线
//	//	glBegin(GL_LINE_STRIP);//折线
//	//	for (i = 0; i < n + 1; i++)
//	//	{
//	//		glVertex2f(R*(i * 2 * Pi / n*sin(i * 2 * Pi / n - j*(Pi / 6)) + cos(i * 2 * Pi / n - j*(Pi / 6))), R*(sin(i * 2 * Pi / n - j*(Pi / 6)) - i * 2 * Pi / n*cos(i * 2 * Pi / n - j*(Pi / 6))));
//
//	//		//glVertex2f(R*(i * 2 * Pi / n*sin(i * 2 * Pi / n) + cos(i * 2 * Pi / n)), R*(sin(i * 2 * Pi / n) - i * 2 * Pi / n*cos(i * 2 * Pi / n)));
//
//	//	}
//	//	glEnd();
//	//}
//
//
//	glFlush();//保证前面的OpenGL命令立即执行（而不是让它们在缓冲区等待）
//
//
//
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