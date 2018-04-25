//#include <gl/glut.h>
//#include <math.h>     
//
//#define WIDTH 400
//#define HEIGHT 400
//
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
//static GLfloat angle = 0.0f;
//
//void myDisplay(void)
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// ����͸��Ч����ͼ
//	glMatrixMode(GL_PROJECTION);//����ΪͶӰ�任
//	glLoadIdentity();//�ڽ��б任ǰ�ѵ�ǰ��������Ϊ��λ����
//	gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.0, 5.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//ǰ����������ʾ�˹۲���λ�ã��м�����������ʾ�˹۲�Ŀ���λ�ã�����������������(0,0,0)�� (x,y,z)��ֱ�ߣ�����ʾ�˹۲�����Ϊ�ġ��ϡ�����
//
//	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
//	{
//		GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat sun_light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//		GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//
//		//GL_POSITION���ԡ���ʾ��Դ���ڵ�λ�á����ĸ�ֵ��X, Y, Z, W����ʾ��
//		//������ĸ�ֵWΪ�㣬���ʾ�ù�Դλ������Զ����ǰ����ֵ��ʾ�������ڵķ������ֹ�Դ��Ϊ�����Թ�Դ��ͨ����̫�����Խ��Ƶı���Ϊ�Ƿ����Թ�Դ��
//		//������ĸ�ֵW��Ϊ�㣬��X/W, Y/W, Z/W��ʾ�˹�Դ��λ�á�
//		glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
//		glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);//GL_AMBIENT��ʾ�ù�Դ�������Ĺ⣬�����ǳ���εķ���������������������ջ����е�ǿ�ȣ���ɫ��
//		glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);//GL_DIFFUSE��ʾ�ù�Դ�������Ĺ⣬���䵽�ֲڱ���ʱ���������䣬���õ��Ĺ��ǿ�ȣ���ɫ��
//		glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//GL_SPECULAR��ʾ�ù�Դ�������Ĺ⣬���䵽�⻬����ʱ�������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
//															  //glLight*����������������
//															  //��һ������ָ����������һ����Դ������
//															  //�ڶ�������ָ�������øù�Դ����һ������
//															  //��������������ָ���Ѹ�����ֵ���óɶ���
//
//		glEnable(GL_LIGHT0);
//		glEnable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//	}
//
//	// test��Դ
//	{
//		GLfloat test_light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };
//		GLfloat test_light_ambient[] = { 0.5f, 0.0f, 0.5f, 1.0f };
//		GLfloat test_light_diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		GLfloat test_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
//
//
//		//GL_POSITION���ԡ���ʾ��Դ���ڵ�λ�á����ĸ�ֵ��X, Y, Z, W����ʾ��
//		//������ĸ�ֵWΪ�㣬���ʾ�ù�Դλ������Զ����ǰ����ֵ��ʾ�������ڵķ������ֹ�Դ��Ϊ�����Թ�Դ��ͨ����̫�����Խ��Ƶı���Ϊ�Ƿ����Թ�Դ��
//		//������ĸ�ֵW��Ϊ�㣬��X/W, Y/W, Z/W��ʾ�˹�Դ��λ�á�
//		glLightfv(GL_LIGHT1, GL_POSITION, test_light_position);
//		glLightfv(GL_LIGHT1, GL_AMBIENT, test_light_ambient);//GL_AMBIENT��ʾ�ù�Դ�������Ĺ⣬�����ǳ���εķ���������������������ջ����е�ǿ�ȣ���ɫ��
//		glLightfv(GL_LIGHT1, GL_DIFFUSE, test_light_diffuse);//GL_DIFFUSE��ʾ�ù�Դ�������Ĺ⣬���䵽�ֲڱ���ʱ���������䣬���õ��Ĺ��ǿ�ȣ���ɫ��
//		glLightfv(GL_LIGHT1, GL_SPECULAR, test_light_specular);//GL_SPECULAR��ʾ�ù�Դ�������Ĺ⣬���䵽�⻬����ʱ�������淴�䣬���õ��Ĺ��ǿ�ȣ���ɫ��
//															   //glLight*����������������
//															   //��һ������ָ����������һ����Դ������
//															   //�ڶ�������ָ�������øù�Դ����һ������
//															   //��������������ָ���Ѹ�����ֵ���óɶ���
//
//		glEnable(GL_LIGHT1);
//		glEnable(GL_LIGHTING);
//		glEnable(GL_DEPTH_TEST);
//	}
//
//
//	// ����̫���Ĳ��ʲ�����̫��
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
//		//glMaterial*����������������
//		//��һ��������ʾָ����һ������ԡ�������GL_FRONT��GL_BACK����GL_FRONT_AND_BACK���ֱ��ʾ���á����桱�����桱�Ĳ��ʣ���������ͬʱ���á�
//		//�ڶ���������������glLight*�����ĵڶ������������������ơ�
//		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sun_mat_ambient);//GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ������ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��
//		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sun_mat_diffuse);//GL_DIFFUSE��ʾ�������䵽�ò����ϣ�������������γɵĹ���ǿ�ȣ���ɫ��
//		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sun_mat_specular);//GL_SPECULAR��ʾ�������䵽�ò����ϣ��������淴����γɵĹ���ǿ�ȣ���ɫ��
//		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sun_mat_emission);//GL_EMISSION���ԡ����������ĸ�ֵ��ɣ���ʾһ����ɫ��OpenGL��Ϊ�ò��ʱ����΢΢�����ⷢ����ߣ��������۾��о���������������ɫ����������ֱȽ�΢���������ڲ���Ӱ�쵽�����������ɫ��
//		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, sun_mat_shininess);//GL_SHININESS���ԡ�������ֻ��һ��ֵ����Ϊ������ָ������ȡֵ��Χ��0��128����ֵԽС����ʾ����Խ�ֲڣ����Դ����Ĺ������䵽���棬Ҳ���Բ����ϴ�����㡣��ֵԽ�󣬱�ʾ����Խ�����ھ��棬��Դ���䵽����󣬲�����С�����㡣
//																		//ͨ����GL_AMBIENT��GL_DIFFUSE��ȡ��ͬ��ֵ�����Դﵽ�Ƚ���ʵ��Ч����ʹ��GL_AMBIENT_AND_DIFFUSE����ͬʱ����GL_AMBIENT��GL_DIFFUSE����
//
//																		//glRotatef(angle, 0.0f, -1.0f, 0.0f);
//																		//glTranslatef(5.0f, 0.0f, 0.0f);
//
//		glutSolidSphere(2.0, 40, 32);
//	}
//
//	// �������Ĳ��ʲ����Ƶ���
//	{
//		GLfloat earth_mat_ambient[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_diffuse[] = { 0.0f, 0.0f, 0.5f, 1.0f };
//		GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
//		//GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
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
//		//glRotatef(45, 1, 1, 1);
//		glFrontFace(GL_CCW);
//
//		for (int i = 0; i < 4; ++i)      // ���ĸ��棬ѭ������  
//		{
//			glPolygonMode(GL_FRONT, GL_FILL);//��������Ϊ���ģʽ
//											 //glBegin(GL_LINE_LOOP);
//			glBegin(GL_POLYGON);//����ʱ�����
//			for (int j = 0; j < 3; ++j)     // ÿ�������ĸ����㣬ѭ���Ĵ�  
//			{
//				//glColor3f(0.2f*j, 0.5f, 0.5f);
//				glColor3f(i & 0x02, i & 0x06, i & 0x01);
//				glVertex3fv(vertex_list[index_list[i][j]]);
//			}
//			glEnd();
//		}
//
//	}
//
//	// ���������Ĳ��ʲ���������
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
//	glutCreateWindow("OpenGL������ʾ");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}