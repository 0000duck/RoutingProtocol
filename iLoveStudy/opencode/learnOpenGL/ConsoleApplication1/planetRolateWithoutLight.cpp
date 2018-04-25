//#include<gl/glut.h>
//#include<time.h>
//#include<stdio.h>
//
//
////进行模型和视图变换，主要涉及到三个函数：
////glTranslate*，把当前矩阵和一个表示移动物体的矩阵相乘。三个参数分别表示了在三个坐标上的位移值。
////glRotate*，把当前矩阵和一个表示旋转物体的矩阵相乘。物体将绕着(0, 0, 0)到(x, y, z)的直线以逆时针旋转，参数angle表示旋转的角度。
////glScale*，把当前矩阵和一个表示缩放物体的矩阵相乘。x, y, z分别表示在该方向上的缩放比例。
//
//static float day = 200;
//
//double CalFrequency()//统计该函数自身的调用频率
//{
//	static int count;
//	static double save;
//	static clock_t last, current;
//	double timegap;
//
//	++count;
//	if (count <= 50)
//	{
//		return save;
//	}
//	count = 0;
//	last = current;
//	current = clock();
//	timegap = (current - last) / (double)CLK_TCK;
//	save = 50.0 / timegap;
//	return save;
//}
//
//void myDisplay(void)
//{
//	double FPS = CalFrequency();
//	printf("FPS=%f\n", FPS);
//
//	glDepthFunc(GL_LEQUAL);
//
//	//指定“目标像素与当前像素在z方向上值大小比较”的函数，符合该函数关系的目标像素才进行绘制，否则对目标像素不予绘制。
//	//参数说明：
//	//	func指定深度比较函数，GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTE_QUAL, GL_GEQUAL, GL_ALWAYS, 缺省值GL_LESS，
//	//	GL_NEVER, 不通过（输入的深度值不取代参考值）
//	//	GL_LESS, 如果输入的深度值小于参考值，则通过
//	//	GL_EQUAL, 如果输入的深度值等于参考值，则通过
//	//	GL_LEQUAL, 如果输入的深度值小于或等于参考值，则通过  ←←←
//	//	GL_GREATER, 如果输入的深度值大于参考值，则通过
//	//	GL_NOTE_QUAL, 如果输入的深度值不等于参考值，则通过
//	//	GL_GEQUAL, 如果输入的深度值大于或等于参考值，则通过
//	//	GL_ALWAYS, 总是通过（输入的深度值取代参考值）
//
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//使用深度测试
//
//	glMatrixMode(GL_PROJECTION);//设置为投影变换
//
//
//	glLoadIdentity();//在进行变换前把当前矩阵设置为单位矩阵。
//
//
//	//gluPerspective(75, 1, 1, 400000000);
//		gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
//
//	//为了得到透视效果，使用gluPerspective来设置可视空间。
//	//假定可视角为60度，高宽比为1.0。最近可视距离为1.0，最远可视距离为200000000*2=400000000。
//	//即：gluPerspective (60, 1, 1, 400000000);
//
//	glMatrixMode(GL_MODELVIEW);//由于模型和视图的变换都通过矩阵运算来实现，在进行变换前，应先设置当前操作的矩阵为“模型视图矩阵”
//	glLoadIdentity();//通常，我们需要在进行变换前把当前矩阵设置为单位矩阵。
//
//	gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
//
//	//前三个参数表示了观察点的位置，中间三个参数表示了观察目标的位置，最后三个参数代表从(0,0,0)到 (x,y,z)的直线，它表示了观察者认为的“上”方向。
//
//
//	// 绘制红色的“太阳”
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glutSolidSphere(2.0, 40, 32);
//	//glutSolidSphere(69600000, 20, 20);
//
//	//绘制球体的现成函数：glutSolidSphere
//	//这个函数在“原点”绘制出一个球体。
//	//由于坐标是可以通过glTranslate*和glRotate*两个函数进行随意变换的，所以就可以在任意位置绘制球体了。
//	//函数有三个参数：第一个参数表示球体的半径，后两个参数代表了“面”的数目，简单点说就是球体的精确程度，数值越大越精确，当然代价就是速度越缓慢。
//
//	// 绘制蓝色的“地球”
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
//	//地球则要复杂一点，需要变换坐标。
//	//由于今年已经经过的天数已知为day，则地球转过的角度为day/一年的天数*360度。
//	//前面已经假定每年都是360天，因此地球转过的角度恰好为day。
//
//	glTranslatef(4.0f, 0.0f, 0.0f);
//	glutSolidSphere(1.0, 40, 32);
//	//glTranslatef(150000000, 0.0f, 0.0f);//glTranslatef(地球轨道半径, 0, 0);
//	//glutSolidSphere(15945000, 20, 20);//glutSolidSphere(地球半径, 20, 20);
//	// 注意地球公转是“自西向东”的，因此是饶着Z轴负方向进行逆时针旋转
//
//	// 绘制黄色的“月亮”
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);//glRotatef(月亮旋转的角度, 0, 0, -1);
//
//	glTranslatef(2.0f, 0.0f, 0.0f);
//	glutSolidSphere(0.5, 40, 32);
//	//glTranslatef(38000000, 0.0f, 0.0f);//glRotatef(月亮轨道半径, 0, 0);
//	//glutSolidSphere(4345000,20, 20);//glutSolidSphere(月亮半径, 20, 20);
//
//	glFlush();
//	glutSwapBuffers();
//}
//
//void myIdle(void)
//{
//	day+=0.5;
//	if (day >= 360)
//		day = 0;
//	myDisplay();
//}
//
//
//int main(int argc, char *argv[])
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//双缓冲
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("Planet Revolution");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}