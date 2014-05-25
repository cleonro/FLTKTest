#pragma once

#include <FL/Fl_Gl_Window.H>
#include <windows.h>
#include <GL/GL.h>

class GLWindow : public Fl_Gl_Window
{
public:
	GLWindow(int x, int y, int w, int h, const char *label = 0);
	~GLWindow();

protected:
	void init();
	void draw();
	int handle(int event);
	void resize(int x, int y, int w, int h);

private:
	
};

