//#include <gl/glut.h>
//#include<math.h>
//
//#define WIDTH 400
//#define HEIGHT 400
//
//		const int n = 40;
//		const GLfloat R = 0.2f;
//		const GLfloat Pi = 3.1415926536f;
//		GLfloat x;
//
//static GLfloat angle = 0.0f;
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//
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
//	//glLineStipple(2, 0xAAAA);
//	//glLineWidth(5.0f);
//	//glEnable(GL_LINE_STIPPLE);
//	//glBegin(GL_LINES);
//	//for (x = 0; x<10 * Pi; x += 0.01f) {
//	//	glColor3f(1.0f, 1.0f, 1.0f);
//	//	glVertex3f(11* cos(x),  sin(x) * 11,0);
//	//}
//	//glEnd();
//	//glDisable(GL_LINE_STIPPLE);
//
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
//		GLfloat sun_mat_emission[] = { 1.0f, 0.0f, 0.0f, 1.0f };
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
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission);//GL_EMISSION属性。该属性由四个值组成，表示一种颜色。OpenGL认为该材质本身就微微的向外发射光线，以至于眼睛感觉到它有这样的颜色，但这光线又比较微弱，以至于不会影响到其它物体的颜色。
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sun_mat_shininess);//GL_SHININESS属性。该属性只有一个值，称为“镜面指数”，取值范围是0到128。该值越小，表示材质越粗糙，点光源发射的光线照射到上面，也可以产生较大的亮点。该值越大，表示材质越类似于镜面，光源照射到上面后，产生较小的亮点。
//																		//通常，GL_AMBIENT和GL_DIFFUSE都取相同的值，可以达到比较真实的效果。使用GL_AMBIENT_AND_DIFFUSE可以同时设置GL_AMBIENT和GL_DIFFUSE属性
//
//																		//glRotatef(angle, 0.0f, -1.0f, 0.0f);
//																		//glTranslatef(5.0f, 0.0f, 0.0f);
//
//		glutSolidSphere(2.0, 40, 32);
//	}
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星1
//	{
//		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat earth_mat_shininess = 30.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, earth_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, earth_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, earth_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, earth_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, earth_mat_shininess);
//		glRotatef(angle, 0.0f, 1.0f, 0.0f);
//		glTranslatef(6.0f, 0.0f, 0.0f);
//		glutSolidSphere(0.2, 40, 32);
//
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(6 * cos(x), 0, sin(x) *6);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//
//
//
//	}
//
//	glPopMatrix();
//	glPushMatrix();
//
//	// 定义材质并绘制行星2
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
//		glTranslatef(5.0f, 0.0f, 0.0f);
//		glutSolidSphere(0.3, 40, 32);
//
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(5 * cos(x), 0, sin(x) * 5);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//
//
//	glPopMatrix();
//	glPushMatrix();
//
//	// 定义材质并绘制行星3
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.5f, 0.8f, 0.0f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 1.5, 0.0f, 1.0f, 0.0f);
//		glTranslatef(3.5f, 0.0f, 0.0f);
//		glutSolidSphere(0.3, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(3.5 * cos(x), 0, sin(x) * 3.5);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//
//	glPopMatrix();
//	glPushMatrix();
//
//	// 定义材质并绘制行星4
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.0f, 0.8f, 0.8f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 2, 0.0f, 1.0f, 0.0f);
//		glTranslatef(4.0f, 0.0f, 0.0f);
//		glutSolidSphere(0.4, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(4 * cos(x), 0, sin(x) * 4);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星5
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.8f, 0.2f, 0.4f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 2.5, 0.0f, 1.0f, 0.0f);
//		glTranslatef(5.0f, 0.0f, 0.0f);
//		glutSolidSphere(0.6, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(5 * cos(x), 0, sin(x) * 5);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星6
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.2f, 0.8f, 0.4f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 4, 0.0f, 1.0f, 0.0f);
//		glTranslatef(4.5f, 0.0f, 0.0f);
//		glutSolidSphere(0.45, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(4.5 * cos(x), 0, sin(x) * 4.5);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星7
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.2f, 0.4f, 0.8f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 4.8, 0.0f, 1.0f, 0.0f);
//		glTranslatef(3.2f, 0.0f, 0.0f);
//		glutSolidSphere(0.2, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(4.8 * cos(x), 0, sin(x) * 4.8);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星8
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.5f, 0.8f, 0.1f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 4.5, 0.0f, 1.0f, 0.0f);
//		glTranslatef(4.3f, 0.0f, 0.0f);
//		glutSolidSphere(0.8, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(4.3 * cos(x), 0, sin(x) * 4.3);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//	}
//	glPopMatrix();
//	glPushMatrix();
//	// 定义材质并绘制行星9
//	{
//		GLfloat moon_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat moon_mat_emission[] = { 0.1f, 0.2f, 0.9f, 1.0f };
//		GLfloat moon_mat_shininess = 10.0f;
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, moon_mat_ambient);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, moon_mat_diffuse);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, moon_mat_specular);
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, moon_mat_emission);
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, moon_mat_shininess);
//		glRotatef(angle * 3, 0.0f, 1.0f, 0.0f);
//		glTranslatef(3.8f, 0.0f, 0.0f);
//		glutSolidSphere(0.4, 40, 32);
//		{
//			glPopMatrix();
//			glPushMatrix();
//			const int n = 40;
//			const GLfloat R = 0.2f;
//			const GLfloat Pi = 3.1415926536f;
//			int i;
//			GLfloat j = 0.1f;
//
//			glBegin(GL_LINES);//折线
//							  //glShadeModel(GL_FLAT);
//							  //glColor3f(1.0f, 0.0f, 0.0f);
//			for (i = 1; i < n; i++)
//			{
//				glColor3f(1.0f, 1.0f, 1.0f);
//				glVertex2f(R*cos(2 * Pi / 7 * i), R*sin(2 * Pi / 7 * i));
//				glVertex2f(R*cos(2 * Pi / 7 * (i + 1)), R*sin(2 * Pi / 7 * (i + 1)));
//			}
//			glEnd();
//			glPushMatrix();
//			glLineStipple(2, 0x00FF);
//			glLineWidth(3.0f);
//			glEnable(GL_LINE_STIPPLE);
//			glBegin(GL_LINES);
//			for (x = 0; x<2 * Pi; x += 0.01f) {
//				glColor3f(0.0f, 0.5f, 0.0f);
//				glVertex3f(3.8 * cos(x), 0, sin(x) * 3.8);
//			}
//			glEnd();
//			glDisable(GL_LINE_STIPPLE);
//		}
//
//	}
//	//glPopMatrix();
//	//glPushMatrix();
//	//glLineStipple(2, 0xAAAA);
//	//glLineWidth(10.0f);
//	//glEnable(GL_LINE_STIPPLE);
//	//glBegin(GL_LINES);
//	//for (x = 0; x<2 * Pi; x += 0.01f) {
//	//	glColor3f(0.1f, 0.3f, 0.1f);
//	//	glVertex3f(5 * cos(x), 0, sin(x) * 5);
//	//}
//	//glEnd();
//	//glDisable(GL_LINE_STIPPLE);
//
//
//	glutSwapBuffers();
//}
//void myIdle(void)
//{
//	angle += 0.1f;
//	if (angle >= 900.0f)
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