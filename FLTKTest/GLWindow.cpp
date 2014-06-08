#include "GLWindow.h"
#include "MainWindow.h"
#include "StateManager.h"
#include <sstream>

GLWindow::GLWindow(int x, int y, int w, int h, const char *label)
	: Fl_Gl_Window(x, y, w, h, label)
{

}

GLWindow::~GLWindow()
{

}

int GLWindow::handle(int event)
{
// 	switch(event)
// 	{
// 	case FL_PUSH:
// 
// 		break;
// 	
// 	}

	return Fl_Gl_Window::handle(event);
}

void GLWindow::init()
{ 
	valid(1);
	
}

void GLWindow::draw()
{
	if(!valid())
	{
		init();
	}

	STATEMNGR.updateActiveState();
	STATEMNGR.renderActiveState();
}

void GLWindow::resize(int x, int y, int w, int h)
{
	Fl_Gl_Window::resize(x, y, w, h);
}