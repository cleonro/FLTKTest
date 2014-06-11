#pragma once

#include <FL/Fl_Gl_Window.H>

class SecondGLWindow : public Fl_Gl_Window
{
public:
	SecondGLWindow(int x, int y, int w, int h, const char *label = 0);
	~SecondGLWindow();

protected:
	void init();
	void draw();
	int handle(int event);

private:
	void drawTriangle();

private:
	float m_glSizeX;

	//triangle center and radius
	float m_x;
	float m_y;
	float m_r;
};

