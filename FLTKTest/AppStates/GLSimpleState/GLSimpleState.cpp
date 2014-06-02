#include "GLSimpleState.h"
#include "MainWindow.h"
#include <windows.h>
#include <GL/GL.h>

GLSimpleState::GLSimpleState() :
	m_initialized(false)
{

}


GLSimpleState::~GLSimpleState()
{

}

void GLSimpleState::init(void* data)
{
	LOGGER.log("GLSimpleState init\n");
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);

	//?
	glPixelZoom(1.0,1.0);

	m_initialized = true;
}

void GLSimpleState::clear()
{

}

void GLSimpleState::update(void* data)
{

}

void GLSimpleState::render()
{

}

bool GLSimpleState::initialized()
{
	return m_initialized;
}