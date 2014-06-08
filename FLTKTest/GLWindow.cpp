#include "GLWindow.h"
#include "MainWindow.h"
#include "StateManager.h"
#include <sstream>
#include <FL/Fl.H>

GLWindow::GLWindow(int x, int y, int w, int h, const char *label)
	: Fl_Gl_Window(x, y, w, h, label)
{

}

GLWindow::~GLWindow()
{

}

int GLWindow::handle(int event)
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
			UIEvent event(UIEvent::MOUSE_DOWN);
			event.rbutton(0) = Fl::event_button1();
			event.rbutton(1) = Fl::event_button2();
			event.rbutton(2) = Fl::event_button3();
			event.rx() = Fl::event_x();
			event.ry() = Fl::event_y();
			STATEMNGR.sendEvent(&event);
		}
		break;
	case FL_RELEASE:
		{
			r = 1;
			UIEvent event(UIEvent::MOUSE_UP);
			event.rbutton(0) = Fl::event_button1();
			event.rbutton(1) = Fl::event_button2();
			event.rbutton(2) = Fl::event_button3();
			event.rx() = Fl::event_x();
			event.ry() = Fl::event_y();
			STATEMNGR.sendEvent(&event);
		}
		break;
	case FL_DRAG:
		{
			r = 1;
			UIEvent event(UIEvent::MOUSE_MOVE);
			event.rbutton(0) = Fl::event_button1();
			event.rbutton(1) = Fl::event_button2();
			event.rbutton(2) = Fl::event_button3();
			event.rx() = Fl::event_x();
			event.ry() = Fl::event_y();
			STATEMNGR.sendEvent(&event);

			redraw();
		}
		break;
	case FL_MOUSEWHEEL:
		{
			r = 1;
			UIEvent event(UIEvent::MOUSE_WHEEL);
			event.rbutton(0) = Fl::event_button1();
			event.rbutton(1) = Fl::event_button2();
			event.rbutton(2) = Fl::event_button3();
			event.rx() = Fl::event_dx();
			event.ry() = Fl::event_dy();
			STATEMNGR.sendEvent(&event);

			redraw();
		}
	default:
		
		break;	
	}

	return r;
}

void GLWindow::init()
{ 
	valid(1);
	float cx = this->w();
	float cy = this->h();
	float aspect = cx / cy;
	glViewport(0, 0, cx, cy);
	BaseState* state = STATEMNGR.activeState();
	if(state != NULL)
	{
		state->init(&aspect);
	}
}

void GLWindow::draw()
{
	if(!valid())
	{
		init();
	}

	STATEMNGR.updateActiveState();
	STATEMNGR.renderActiveState();

	this->swap_buffers();
}

void GLWindow::resize(int x, int y, int w, int h)
{
	Fl_Gl_Window::resize(x, y, w, h);
}