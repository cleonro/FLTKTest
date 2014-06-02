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
	//test-remove
// 	std::ostringstream buff;
// 	buff << "GLWindow event " << event << "\n";
// 	LOGGER.log(buff.str().c_str());
// 	//
// 
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
// 	//valid(1);
}

void GLWindow::draw()
{
// 	if(!valid())
// 	{
// 		init();
// 	}
// 	glClearColor(0.3, 0.5, 0.7, 1.0);
// 	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	STATEMNGR.updateActiveState();
	STATEMNGR.renderActiveState();
}

void GLWindow::resize(int x, int y, int w, int h)
{
	//test-remove
// 	std::ostringstream buff;
// 	buff << "GLWindow resize " << x << ", " << "y, " << w << ", " << h <<  "\n";
// 	LOGGER.log(buff.str().c_str());
	//

	Fl_Gl_Window::resize(x, y, w, h);
}