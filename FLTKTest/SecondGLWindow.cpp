#include "SecondGLWindow.h"

#include <windows.h>
#include <GL/GL.h>
#include <FL/Fl.H>

SecondGLWindow::SecondGLWindow(int x, int y, int w, int h, const char *label)
	: Fl_Gl_Window(x, y, w, h, label)
{
	m_glSizeX = 10;

	m_x = 0;
	m_y = 0;
	m_r = 10;
}


SecondGLWindow::~SecondGLWindow(void)
{

}

void SecondGLWindow::init()
{
	valid(1);
	float cx = this->w();
	float cy = this->h();
	float aspect = cx / cy;
	glViewport(0, 0, cx, cy);

	float glSizeY = m_glSizeX / aspect;
	glOrtho(-m_glSizeX, m_glSizeX, -glSizeY, glSizeY, -2048, 2048);
}

void SecondGLWindow::draw()
{
	if(!valid())
	{
		init();
	}

	glClearColor(0.3, 0.7, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawTriangle();
}

int SecondGLWindow::handle(int event)
{
	int r = Fl_Gl_Window::handle(event);

	return r;
}

void SecondGLWindow::drawTriangle()
{

}