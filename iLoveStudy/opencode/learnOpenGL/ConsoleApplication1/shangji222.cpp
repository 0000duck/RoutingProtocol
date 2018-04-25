//#include <gl/glut.h>
//#include <math.h>     
//
//#define WIDTH 400
//#define HEIGHT 400
//#define ColoredVertex(c, v) do{ glColor3fv(c); glVertex3fv(v); }while(0)   
//
//#define pi 3.1415927f;  
//
//static GLfloat angle = 0.0f;
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// 创建透视效果视图
//	glMatrixMode(GL_PROJECTION);//设置为投影变换
//	glLoadIdentity();//在进行变换前把当前矩阵设置为单位矩阵
//	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//前三个参数表示了观察点的位置，中间三个参数表示了观察目标的位置，最后三个参数代表从(0,0,0)到 (x,y,z)的直线，它表示了观察者认为的“上”方向。
//
//	// 定义太阳光源，它是一种白色的光源
//	{
//		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//
//		//GL_POSITION属性。表示光源所在的位置。由四个值（X, Y, Z, W）表示。
//		//如果第四个值W为零，则表示该光源位于无限远处，前三个值表示了它所在的方向。这种光源称为方向性光源，通常，太阳可以近似的被认为是方向性光源。
//		//如果第四个值W不为零，则X/W, Y/W, Z/W表示了光源的位置。
//		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);//GL_AMBIENT表示该光源所发出的光，经过非常多次的反射后，最终遗留在整个光照环境中的强度（颜色）
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);//GL_DIFFUSE表示该光源所发出的光，照射到粗糙表面时经过漫反射，所得到的光的强度（颜色）
//		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//GL_SPECULAR表示该光源所发出的光，照射到光滑表面时经过镜面反射，所得到的光的强度（颜色）
//															  //glLight*函数具有三个参数
//															  //第一个参数指明是设置哪一个光源的属性
//															  //第二个参数指明是设置该光源的哪一个属性
//															  //第三个参数则是指明把该属性值设置成多少
//
//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//	}
//
//	// test光源
//	{
//		GLfloat test_light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//		GLfloat test_light_ambient[] = { 0.5f, 0.0f, 0.5f, 1.0f };
//		GLfloat test_light_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat test_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//
//		//GL_POSITION属性。表示光源所在的位置。由四个值（X, Y, Z, W）表示。
//		//如果第四个值W为零，则表示该光源位于无限远处，前三个值表示了它所在的方向。这种光源称为方向性光源，通常，太阳可以近似的被认为是方向性光源。
//		//如果第四个值W不为零，则X/W, Y/W, Z/W表示了光源的位置。
//		glLightfv(GL_LIGHT1, GL_POSITION, test_light_position);
//		glLightfv(GL_LIGHT1, GL_AMBIENT, test_light_ambient);//GL_AMBIENT表示该光源所发出的光，经过非常多次的反射后，最终遗留在整个光照环境中的强度（颜色）
//		glLightfv(GL_LIGHT1, GL_DIFFUSE, test_light_diffuse);//GL_DIFFUSE表示该光源所发出的光，照射到粗糙表面时经过漫反射，所得到的光的强度（颜色）
//		glLightfv(GL_LIGHT1, GL_SPECULAR, test_light_specular);//GL_SPECULAR表示该光源所发出的光，照射到光滑表面时经过镜面反射，所得到的光的强度（颜色）
//															   //glLight*函数具有三个参数
//															   //第一个参数指明是设置哪一个光源的属性
//															   //第二个参数指明是设置该光源的哪一个属性
//															   //第三个参数则是指明把该属性值设置成多少
//
//		glEnable(GL_LIGHT1);
//		glEnable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//	}
//
//
//	// 定义太阳的材质并绘制太阳
//	{
//		GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
//
//		//GLfloat sun_mat_emission[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_mat_emission1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_mat_emission2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
//		GLfloat sun_mat_emission3[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//		GLfloat sun_mat_emission4[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_mat_emission5[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//		GLfloat sun_mat_emission6[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//
//		GLfloat sun_mat_shininess = 50.0f;
//		//GLfloat sun_mat_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		//GLfloat sun_mat_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		//GLfloat sun_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		//GLfloat sun_mat_emission[] = { 0.5f, 0.0f, 0.0f, 1.0f };
//		//GLfloat sun_mat_shininess = 0.0f;
//
//		//glMaterial*函数有三个参数。
//		//第一个参数表示指定哪一面的属性。可以是GL_FRONT、GL_BACK或者GL_FRONT_AND_BACK。分别表示设置“正面”“背面”的材质，或者两面同时设置。
//		//第二、第三个参数与glLight*函数的第二、三个参数作用类似。
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sun_mat_ambient);//GL_AMBIENT表示各种光线照射到该材质上，经过很多次反射后最终遗留在环境中的光线强度（颜色）
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_mat_diffuse);//GL_DIFFUSE表示光线照射到该材质上，经过漫反射后形成的光线强度（颜色）
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_mat_specular);//GL_SPECULAR表示光线照射到该材质上，经过镜面反射后形成的光线强度（颜色）
//		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission);//GL_EMISSION属性。该属性由四个值组成，表示一种颜色。OpenGL认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sun_mat_shininess);//GL_SHININESS属性。该属性只有一个值，称为“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
//																		//通常，GL_AMBIENT和GL_DIFFUSE都取相同的值，可以达到比较真实的效果。使用GL_AMBIENT_AND_DIFFUSE可以同时设置GL_AMBIENT和GL_DIFFUSE属性
//
//																		//glRotatef(angle, 0.0f, -1.0f, 0.0f);
//																		//glTranslatef(5.0f, 0.0f, 0.0f);
//		glRotatef(angle*5, 0.0f, 1.0f, 0.0f);
//		//立方体
//		{
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission6);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(1.0f, 1.0f, 1.0f);
//			glVertex3f(1.0f, 1.0f, -1.0f);
//			glVertex3f(-1.0f, 1.0f, -1.0f);
//			glVertex3f(-1.0f, 1.0f, 1.0f);
//			glEnd();
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission1);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(1.0f, -1.0f, 1.0f);
//			glVertex3f(1.0f, -1.0f, -1.0f);
//			glVertex3f(-1.0f, -1.0f, -1.0f);
//			glVertex3f(-1.0f, -1.0f, 1.0f);
//			glEnd();
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission2);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(1.0f, 1.0f, 1.0f);
//			glVertex3f(1.0f, 1.0f, -1.0f);
//			glVertex3f(1.0f, -1.0f, -1.0f);
//			glVertex3f(1.0f, -1.0f, 1.0f);
//			glEnd();
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission3);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(-1.0f, 1.0f, 1.0f);
//			glVertex3f(-1.0f, 1.0f, -1.0f);
//			glVertex3f(-1.0f, -1.0f, -1.0f);
//			glVertex3f(-1.0f, -1.0f, 1.0f);
//			glEnd();
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission4);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(-1.0f, 1.0f, -1.0f);
//			glVertex3f(1.0f, 1.0f, -1.0f);
//			glVertex3f(1.0f, -1.0f, -1.0f);
//			glVertex3f(-1.0f, -1.0f, -1.0f);
//			glEnd();
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission5);
//			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			glBegin(GL_POLYGON);
//			glVertex3f(-1.0f, 1.0f, 1.0f);
//			glVertex3f(1.0f, 1.0f, 1.0f);
//			glVertex3f(1.0f, -1.0f, 1.0f);
//			glVertex3f(-1.0f, -1.0f, 1.0f);
//			glEnd();
//		}
//
//
//	}
//
//	// 定义地球的材质并绘制地球
//	{
//		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//
//		GLfloat earth_mat_emission1[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat earth_mat_emission2[] = { 0.0f, 0.0f, 1.0f, 1.0f };
//		GLfloat earth_mat_emission3[] = { 0.0f, 1.0f, 0.0f, 1.0f };
//		GLfloat earth_mat_emission4[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//
//		GLfloat earth_mat_shininess = 30.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, earth_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, earth_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, earth_mat_specular);
//		//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, earth_mat_shininess);
//		glRotatef(angle, 0.0f, 1.0f, 0.0f);
//		glTranslatef(6.0f, 0.0f, 0.0f);
//		//glutSolidSphere(1.0, 40, 32);
//
//
//
//		static int list = 0;
//		if (list == 0)
//		{
//			// 如果显示列表不存在，则创建
//
//			GLfloat   //GLfloat为OpenGL用到的数据类型，与C的float基本一致
//
//				PointA[] = { -0.5, -5 * sqrt(5) / 48, sqrt(3) / 6 },   //此处为4个顶点的坐标，因为时3D坐标系下的，所以每个坐标有3个分量，分别对应X，Y，Z轴。至于各轴方向定义……默认下屏幕水平为X，竖直为Y，里外为Z。
//				PointB[] = { 0.5, -5 * sqrt(5) / 48, sqrt(3) / 6 },
//				PointC[] = { 0, -5 * sqrt(5) / 48, -sqrt(3) / 3 },
//				PointD[] = { 0, 11 * sqrt(6) / 48, 0 };
//			/*GLfloat
//			PointA[] = { 0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
//			PointB[] = {-0.5f, -sqrt(6.0f)/12, -sqrt(3.0f)/6},
//			PointC[] = { 0.0f, -sqrt(6.0f)/12, sqrt(3.0f)/3},
//			PointD[] = { 0.0f, sqrt(6.0f)/4, 0};
//			*/
//			GLfloat
//
//				ColorR[] = { 1, 0, 0 },   //定义颜色数组，每个数组为一个颜色，也含有3个分量，对应红，绿，蓝，分量范围[0，1]，每种颜色都可看做是这3个颜色混合得到。可一自己改变下其中的数值看看具体效果。
//				ColorG[] = { 0, 1, 0 },
//				ColorB[] = { 0, 0, 1 },
//				ColorY[] = { 1, 1, 0 };
//
//			list = glGenLists(1);
//			glNewList(list, GL_COMPILE);  //创建一个顶点表，这个表里包含有绘图的顶点信息
//			glBegin(GL_TRIANGLES);   //开始绘图，（GL_TRIANGLES）表示绘制三角形
//
//			// 平面ABC 
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission1);
//			ColoredVertex(ColorR, PointA);  //以颜色R绘制点A，以下类推，ColoredVertex（）函数在程序开头定义了。
//			ColoredVertex(ColorG, PointB);
//			ColoredVertex(ColorB, PointC);
//			// 平面ACD
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission2);
//			ColoredVertex(ColorR, PointA);
//			ColoredVertex(ColorB, PointC);
//			ColoredVertex(ColorY, PointD);
//			// 平面CBD 
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission3);
//			ColoredVertex(ColorB, PointC);
//			ColoredVertex(ColorG, PointB);
//			ColoredVertex(ColorY, PointD);
//			// 平面BAD 
//			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission4);
//			ColoredVertex(ColorG, PointB);
//			ColoredVertex(ColorR, PointA);
//			ColoredVertex(ColorY, PointD);
//			glEnd();
//			glEndList();  //结束绘图 结束绘图顶点表。
//			glEnable(GL_DEPTH_TEST);  //打开深度测试。打开深度测试的作用是：如果在场景中有多个物体，而它们相对观察者的距离不同（简单理解为远近），那么这个时候，前面的物体则可以挡住后面的物体（没错吧），使场景具有深度感。如果不打开深度测试，那么绘图会按绘制的顺序，后绘制的物体覆盖住现绘制的物体。这里要注意的是，深度仅影响物体重合时谁显示谁不显示，并不影响其3D效果，远处的物体仍然会变“小”，物体在空间中的位置仍为三维的。
//
//		}
//
//		glCallList(list);  //调用顶点表，绘制四面体模型
//
//
//	}
//
//	// 定义月亮的材质并绘制月亮
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 1.0f, 1.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 3, 0.0f, 1.0f, 0.0f);
//		glTranslatef(2.0f, 0.0f, 0.0f);
//		glutSolidTeapot(0.2);
//
//
//		//glutSolidSphere(0.5, 40, 32);
//	}
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