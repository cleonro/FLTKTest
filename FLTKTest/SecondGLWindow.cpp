#include "SecondGLWindow.h"
#include <MainWindow.h>

#include <windows.h>
#include <GL/GL.h>
#include <FL/Fl.H>
#include <cmath>
#include <sstream>

SecondGLWindow::SecondGLWindow(int x, int y, int w, int h, const char *label)
	: Fl_Gl_Window(x, y, w, h, label)
{
	m_glSizeX = 10;
	m_glSizeY = 10;

	m_x = 0;
	m_y = 0;
	m_r = 1;
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

	m_glSizeY = m_glSizeX / aspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-m_glSizeX, m_glSizeX, -m_glSizeY, m_glSizeY, -1024, 1024);
}

void SecondGLWindow::draw()
{
	if(!valid())
	{
		init();
	}

	glClearColor(0.3, 0.7, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_LINES);
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glVertex2f(-m_glSizeX, 0);
	glVertex2f(m_glSizeX, 0);
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glVertex2f(0, -m_glSizeY);
	glVertex2f(0, m_glSizeY);
	glEnd();
	drawTriangle();

	this->swap_buffers();
}

int SecondGLWindow::handle(int event)
{
	int r = Fl_Gl_Window::handle(event);

	switch(event)
	{
	case FL_ENTER:
		r = 1;
		break;
	case FL_PUSH:
		{
			r = 1;
			if(Fl::event_button1() == 0)
			{
				break;
			}
			int x = Fl::event_x();
			int y = Fl::event_y();
			m_x = -m_glSizeX + x * 2.0 * m_glSizeX / this->w();
			m_y = m_glSizeY - y * 2.0 * m_glSizeY / this->h();
			this->redraw();
		}
		break;
	//case FL_RELEASE:
	//	{
	//		r = 1;
	//		if(Fl::event_button1() == 0)
	//		{
	//			break;
	//		}
	//		int x = Fl::event_x();
	//		int y = Fl::event_y();
	//		m_x = -m_glSizeX + x * 2.0 * m_glSizeX / this->w();
	//		m_y = m_glSizeY - y * 2.0 * m_glSizeY / this->h();
	//		this->redraw();
	//	}
	//	break;
	case FL_DRAG:
		{
			r = 1;
			if(Fl::event_button1() == 0)
			{
				break;
			}
			int x = Fl::event_x();
			int y = Fl::event_y();
			m_x = -m_glSizeX + x * 2.0 * m_glSizeX / this->w();
			m_y = m_glSizeY - y * 2.0 * m_glSizeY / this->h();
			this->redraw();
		}
		break;
	case FL_MOUSEWHEEL:
		{
			r = 1;
			int dy = Fl::event_dy();
			if(dy > 0)
			{
				m_glSizeX = 1.1 * m_glSizeX;
			}
			else
			{
				m_glSizeX = 0.9 * m_glSizeX;
			}
			redraw();
		}
	default:

		break;	
	}

	return r;
}

void SecondGLWindow::drawTriangle()
{
	float x1 = m_x;
	float y1 = m_y + m_r;

	float x2 = m_x + m_r * cos(M_PI / 6);
	float y2 = m_y - m_r * sin(M_PI / 6);

	float x3 = m_x - m_r * cos(M_PI / 6);
	float y3 = y2;

	glBegin(GL_TRIANGLES);
	glColor4f(0.7, 0.5, 0.3, 1.0);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();

	//std::stringstream buff;
	//buff << "Triangle [" << x1 << ", " << y1 << "] [" << x2 << ", " << y2 << "] [" << x3 << ", " << y3 << "]\n";
	//LOGGER.log(buff.str().c_str());
}