//#include<gl/glut.h>
//#include<time.h>
//#include<stdio.h>
//
//
////����ģ�ͺ���ͼ�任����Ҫ�漰������������
////glTranslate*���ѵ�ǰ�����һ����ʾ�ƶ�����ľ�����ˡ����������ֱ��ʾ�������������ϵ�λ��ֵ��
////glRotate*���ѵ�ǰ�����һ����ʾ��ת����ľ�����ˡ����彫����(0, 0, 0)��(x, y, z)��ֱ������ʱ����ת������angle��ʾ��ת�ĽǶȡ�
////glScale*���ѵ�ǰ�����һ����ʾ��������ľ�����ˡ�x, y, z�ֱ��ʾ�ڸ÷����ϵ����ű�����
//
//static float day = 200;
//
//double CalFrequency()//ͳ�Ƹú�������ĵ���Ƶ��
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
//	//ָ����Ŀ�������뵱ǰ������z������ֵ��С�Ƚϡ��ĺ��������ϸú�����ϵ��Ŀ�����زŽ��л��ƣ������Ŀ�����ز�����ơ�
//	//����˵����
//	//	funcָ����ȱȽϺ�����GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL, GL_GREATER, GL_NOTE_QUAL, GL_GEQUAL, GL_ALWAYS, ȱʡֵGL_LESS��
//	//	GL_NEVER, ��ͨ������������ֵ��ȡ���ο�ֵ��
//	//	GL_LESS, �����������ֵС�ڲο�ֵ����ͨ��
//	//	GL_EQUAL, �����������ֵ���ڲο�ֵ����ͨ��
//	//	GL_LEQUAL, �����������ֵС�ڻ���ڲο�ֵ����ͨ��  ������
//	//	GL_GREATER, �����������ֵ���ڲο�ֵ����ͨ��
//	//	GL_NOTE_QUAL, �����������ֵ�����ڲο�ֵ����ͨ��
//	//	GL_GEQUAL, �����������ֵ���ڻ���ڲο�ֵ����ͨ��
//	//	GL_ALWAYS, ����ͨ������������ֵȡ���ο�ֵ��
//
//	glEnable(GL_DEPTH_TEST);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//ʹ����Ȳ���
//
//	glMatrixMode(GL_PROJECTION);//����ΪͶӰ�任
//
//
//	glLoadIdentity();//�ڽ��б任ǰ�ѵ�ǰ��������Ϊ��λ����
//
//
//	//gluPerspective(75, 1, 1, 400000000);
//		gluPerspective(90.0f, 1.0f, 1.0f, 20.0f);
//
//	//Ϊ�˵õ�͸��Ч����ʹ��gluPerspective�����ÿ��ӿռ䡣
//	//�ٶ����ӽ�Ϊ60�ȣ��߿��Ϊ1.0��������Ӿ���Ϊ1.0����Զ���Ӿ���Ϊ200000000*2=400000000��
//	//����gluPerspective (60, 1, 1, 400000000);
//
//	glMatrixMode(GL_MODELVIEW);//����ģ�ͺ���ͼ�ı任��ͨ������������ʵ�֣��ڽ��б任ǰ��Ӧ�����õ�ǰ�����ľ���Ϊ��ģ����ͼ����
//	glLoadIdentity();//ͨ����������Ҫ�ڽ��б任ǰ�ѵ�ǰ��������Ϊ��λ����
//
//	gluLookAt(0.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	//gluLookAt(0, -200000000, 200000000, 0, 0, 0, 0, 0, 1);
//
//	//ǰ����������ʾ�˹۲���λ�ã��м�����������ʾ�˹۲�Ŀ���λ�ã�����������������(0,0,0)�� (x,y,z)��ֱ�ߣ�����ʾ�˹۲�����Ϊ�ġ��ϡ�����
//
//
//	// ���ƺ�ɫ�ġ�̫����
//	glColor3f(1.0f, 0.0f, 0.0f);
//	glutSolidSphere(2.0, 40, 32);
//	//glutSolidSphere(69600000, 20, 20);
//
//	//����������ֳɺ�����glutSolidSphere
//	//��������ڡ�ԭ�㡱���Ƴ�һ�����塣
//	//���������ǿ���ͨ��glTranslate*��glRotate*����������������任�ģ����ԾͿ���������λ�û��������ˡ�
//	//������������������һ��������ʾ����İ뾶�����������������ˡ��桱����Ŀ���򵥵�˵��������ľ�ȷ�̶ȣ���ֵԽ��Խ��ȷ����Ȼ���۾����ٶ�Խ������
//
//	// ������ɫ�ġ�����
//	glColor3f(0.0f, 0.0f, 1.0f);
//	glRotatef(day / 360.0*360.0, 0.0f, 0.0f, -1.0f);
//	//������Ҫ����һ�㣬��Ҫ�任���ꡣ
//	//���ڽ����Ѿ�������������֪Ϊday�������ת���ĽǶ�Ϊday/һ�������*360�ȡ�
//	//ǰ���Ѿ��ٶ�ÿ�궼��360�죬��˵���ת���ĽǶ�ǡ��Ϊday��
//
//	glTranslatef(4.0f, 0.0f, 0.0f);
//	glutSolidSphere(1.0, 40, 32);
//	//glTranslatef(150000000, 0.0f, 0.0f);//glTranslatef(�������뾶, 0, 0);
//	//glutSolidSphere(15945000, 20, 20);//glutSolidSphere(����뾶, 20, 20);
//	// ע�����ת�ǡ������򶫡��ģ����������Z�Ḻ���������ʱ����ת
//
//	// ���ƻ�ɫ�ġ�������
//	glColor3f(1.0f, 1.0f, 0.0f);
//	glRotatef(day / 30.0*360.0 - day / 360.0*360.0, 0.0f, 0.0f, -1.0f);//glRotatef(������ת�ĽǶ�, 0, 0, -1);
//
//	glTranslatef(2.0f, 0.0f, 0.0f);
//	glutSolidSphere(0.5, 40, 32);
//	//glTranslatef(38000000, 0.0f, 0.0f);//glRotatef(��������뾶, 0, 0);
//	//glutSolidSphere(4345000,20, 20);//glutSolidSphere(�����뾶, 20, 20);
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
//	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);//˫����
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(400, 400);
//	glutCreateWindow("Planet Revolution");
//	glutDisplayFunc(&myDisplay);
//	glutIdleFunc(&myIdle);
//	glutMainLoop();
//	return 0;
//}