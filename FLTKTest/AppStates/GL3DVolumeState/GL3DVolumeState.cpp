#include "GL3DVolumeState.h"


GL3DVolumeState::GL3DVolumeState(void)
{

}

GL3DVolumeState::~GL3DVolumeState(void)
{

}

void GL3DVolumeState::init(void* data)
{
	GLSimpleState::init(data);
	m_cube.SetCamera(camera());
	m_cube.Init(20.0f);
}

void GL3DVolumeState::clear()
{
	GLSimpleState::clear();
}

void GL3DVolumeState::update(void* data)
{
	GLSimpleState::update(data);

	static bool init_image = true;
	if(init_image)
	{
		m_cube.InitImage();
		init_image = false;
	}
}

void GL3DVolumeState::render()
{
	GLSimpleState::render();

	m_cube.Draw();
}
