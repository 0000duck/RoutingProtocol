//// Texture.cpp : Defines the entry point for the console application.
////
//
//
//
//#include "stdafx.h"
//
//#define WindowWidth   400
//#define WindowHeight 400
//#define WindowTitle  "OpenGL��������"
//
//#include <gl/glut.h>
//#include <stdio.h>
//#include <stdlib.h>
//
///* ����grab
//* ץȡ�����е�����
//* ���贰�ڿ���ΪWindowWidth���߶�ΪWindowHeight
//*/
//#define BMP_Header_Length 54
//void grab(void)
//{
//	FILE*     pDummyFile;
//	FILE*     pWritingFile;
//	GLubyte* pPixelData;
//	GLubyte   BMP_Header[BMP_Header_Length];
//	GLint     i, j;
//	GLint     PixelDataLength;
//
//	// �����������ݵ�ʵ�ʳ���
//	i = WindowWidth * 3;    // �õ�ÿһ�е��������ݳ���
//	while (i % 4 != 0)       // �������ݣ�ֱ��i�ǵı���
//		++i;                // �������и�����㷨��
//							// �������׷��ֱ�ۣ����ٶ�û��̫��Ҫ��
//	PixelDataLength = i * WindowHeight;
//
//	// �����ڴ�ʹ��ļ�
//	pPixelData = (GLubyte*)malloc(PixelDataLength);
//	if (pPixelData == 0)
//		exit(0);
//
//	pDummyFile = fopen("dummy.bmp", "rb");
//	if (pDummyFile == 0)
//		exit(0);
//
//	pWritingFile = fopen("grab.bmp", "wb");
//	if (pWritingFile == 0)
//		exit(0);
//
//	// ��ȡ����
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
//	glReadPixels(0, 0, WindowWidth, WindowHeight,
//		GL_BGR_EXT, GL_UNSIGNED_BYTE, pPixelData);
//
//	// ��dummy.bmp���ļ�ͷ����Ϊ���ļ����ļ�ͷ
//	fread(BMP_Header, sizeof(BMP_Header), 1, pDummyFile);
//	fwrite(BMP_Header, sizeof(BMP_Header), 1, pWritingFile);
//	fseek(pWritingFile, 0x0012, SEEK_SET);
//	i = WindowWidth;
//	j = WindowHeight;
//	fwrite(&i, sizeof(i), 1, pWritingFile);
//	fwrite(&j, sizeof(j), 1, pWritingFile);
//
//	// д����������
//	fseek(pWritingFile, 0, SEEK_END);
//	fwrite(pPixelData, PixelDataLength, 1, pWritingFile);
//
//	// �ͷ��ڴ�͹ر��ļ�
//	fclose(pDummyFile);
//	fclose(pWritingFile);
//	free(pPixelData);
//}
//
///* ����power_of_two
//* ���һ�������Ƿ�Ϊ2�������η�������ǣ�����1�����򷵻�0
//* ʵ����ֻҪ�鿴�������λ���ж��ٸ������������1��������1�����򷵻�0
//* �ڡ��鿴�������λ���ж��ٸ���ʱʹ����һ��С����
//* ʹ��n &= (n-1)����ʹ��n�еļ���һ��������ԭ����ҿ����Լ�˼����
//*/
//int power_of_two(int n)
//{
//	if (n <= 0)
//		return 0;
//	return (n & (n - 1)) == 0;
//}
//
///* ����load_texture
//* ��ȡһ��BMP�ļ���Ϊ����
//* ���ʧ�ܣ�����0������ɹ��������������
//*/
//GLuint load_texture(const char* file_name)
//{
//	GLint width, height, total_bytes;
//	GLubyte* pixels = 0;
//	GLuint last_texture_ID, texture_ID = 0;
//
//	// ���ļ������ʧ�ܣ�����
//	FILE* pFile = fopen(file_name, "rb");
//	if (pFile == 0)
//		return 0;
//
//	// ��ȡ�ļ���ͼ��Ŀ��Ⱥ͸߶�
//	fseek(pFile, 0x0012, SEEK_SET);
//	fread(&width, 4, 1, pFile);
//	fread(&height, 4, 1, pFile);
//	fseek(pFile, BMP_Header_Length, SEEK_SET);
//
//	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
//	{
//		GLint line_bytes = width * 3;
//		while (line_bytes % 4 != 0)
//			++line_bytes;
//		total_bytes = line_bytes * height;
//	}
//
//	// �����������ֽ��������ڴ�
//	pixels = (GLubyte*)malloc(total_bytes);
//	if (pixels == 0)
//	{
//		fclose(pFile);
//		return 0;
//	}
//
//	// ��ȡ��������
//	if (fread(pixels, total_bytes, 1, pFile) <= 0)
//	{
//		free(pixels);
//		fclose(pFile);
//		return 0;
//	}
//
//	// �ھɰ汾��OpenGL��
//	// ���ͼ��Ŀ��Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
//	// ���ﲢû�м��OpenGL�汾�����ڶ԰汾�����ԵĿ��ǣ����ɰ汾����
//	// ���⣬�����Ǿɰ汾�����°汾��
//	// ��ͼ��Ŀ��Ⱥ͸߶ȳ�����ǰOpenGLʵ����֧�ֵ����ֵʱ��ҲҪ��������
//	{
//		GLint max;
//		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
//		if (!power_of_two(width)
//			|| !power_of_two(height)
//			|| width > max
//			|| height > max)
//		{
//			const GLint new_width = 256;
//			const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
//			GLint new_line_bytes, new_total_bytes;
//			GLubyte* new_pixels = 0;
//
//			// ����ÿ����Ҫ���ֽ��������ֽ���
//			new_line_bytes = new_width * 3;
//			while (new_line_bytes % 4 != 0)
//				++new_line_bytes;
//			new_total_bytes = new_line_bytes * new_height;
//
//			// �����ڴ�
//			new_pixels = (GLubyte*)malloc(new_total_bytes);
//			if (new_pixels == 0)
//			{
//				free(pixels);
//				fclose(pFile);
//				return 0;
//			}
//
//			// ������������
//			gluScaleImage(GL_RGB,
//				width, height, GL_UNSIGNED_BYTE, pixels,
//				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);
//
//			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
//			free(pixels);
//			pixels = new_pixels;
//			width = new_width;
//			height = new_height;
//		}
//	}
//
//	// ����һ���µ��������
//	glGenTextures(1, &texture_ID);
//	if (texture_ID == 0)
//	{
//		free(pixels);
//		fclose(pFile);
//		return 0;
//	}
//
//	// ���µ�����������������������������
//	// �ڰ�ǰ���Ȼ��ԭ���󶨵�������ţ��Ա��������лָ�
//	glGetIntegerv(GL_TEXTURE_BINDING_2D, (int *)&last_texture_ID);
//	glBindTexture(GL_TEXTURE_2D, texture_ID);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
//		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
//	glBindTexture(GL_TEXTURE_2D, last_texture_ID);
//
//	// ֮ǰΪpixels������ڴ����ʹ��glTexImage2D�Ժ��ͷ�
//	// ��Ϊ��ʱ���������Ѿ���OpenGL���б�����һ�ݣ����ܱ����浽ר�ŵ�ͼ��Ӳ���У�
//	free(pixels);
//	return texture_ID;
//}
//
///* ������������ı��
//*/
//GLuint texGround;
//GLuint texWall;
//
//void display(void)
//{
//	// �����Ļ
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// �����ӽ�
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluPerspective(75, 1, 1, 21);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(1, 5, 5, 0, 0, 0, 0, 0, 1);
//
//	// ʹ�á��ء�������������
//	glBindTexture(GL_TEXTURE_2D, texGround);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-8.0f, -8.0f, 0.0f);
//	glTexCoord2f(0.0f, 5.0f); glVertex3f(-8.0f, 8.0f, 0.0f);
//	glTexCoord2f(5.0f, 5.0f); glVertex3f(8.0f, 8.0f, 0.0f);
//	glTexCoord2f(5.0f, 0.0f); glVertex3f(8.0f, -8.0f, 0.0f);
//	glEnd();
//	// ʹ�á�ǽ����������դ��
//	glBindTexture(GL_TEXTURE_2D, texWall);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
//	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
//	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
//	glEnd();
//
//	// ��ת���ٻ���һ��
//	glRotatef(-90, 0, 0, 1);
//	glBegin(GL_QUADS);
//	glTexCoord2f(0.0f, 0.0f); glVertex3f(-6.0f, -3.0f, 0.0f);
//	glTexCoord2f(0.0f, 1.0f); glVertex3f(-6.0f, -3.0f, 1.5f);
//	glTexCoord2f(5.0f, 1.0f); glVertex3f(6.0f, -3.0f, 1.5f);
//	glTexCoord2f(5.0f, 0.0f); glVertex3f(6.0f, -3.0f, 0.0f);
//	glEnd();
//
//	// �������������������������ݵ��ļ�
//	glutSwapBuffers();
//	grab();
//}
//
//int main(int argc, char* argv[])
//{
//	// GLUT��ʼ��
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
//	glutInitWindowPosition(100, 100);
//	glutInitWindowSize(WindowWidth, WindowHeight);
//	glutCreateWindow(WindowTitle);
//	glutDisplayFunc(&display);
//
//	// ��������һЩ��ʼ��
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_TEXTURE_2D);
//	texGround = load_texture("ground.bmp");
//	texWall = load_texture("wall.bmp");
//
//	// ��ʼ��ʾ
//	glutMainLoop();
//
//	return 0;
//}