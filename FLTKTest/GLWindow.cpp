#include "GLWindow.h"
#include "MainWindow.h"
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
	std::ostringstream buff;
	buff << "GLWindow event " << event << "\n";
	LOGGER.log(buff.str().c_str());
	//

	switch(event)
	{
	case FL_PUSH:

		break;
	
	}

	return Fl_Gl_Window::handle(event);
}

void GLWindow::init()
{
	LOGGER.log("GLWindow init\n");
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//glEnable(GL_TEXTURE_2D);

	glPixelZoom(1.0,1.0);

	//valid(1);
}

void GLWindow::draw()
{
	if(!valid())
	{
		init();
	}
	glClearColor(0.3, 0.5, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::resize(int x, int y, int w, int h)
{
	//test-remove
	std::ostringstream buff;
	buff << "GLWindow resize " << x << ", " << "y, " << w << ", " << h <<  "\n";
	LOGGER.log(buff.str().c_str());
	//

	Fl_Gl_Window::resize(x, y, w, h);
}