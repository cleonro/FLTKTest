#pragma once

#include "StateManager.h"
#include "GLCamera.h"

#define GL_SIMPLE_STATE "GLSimpleState"

class GLSimpleState : public BaseState
{
	friend class StateManager;

public:
	virtual void init(void* data = nullptr);
	virtual void clear();
	virtual void update(void* data = nullptr);
	virtual void render();
	virtual bool initialized();
	virtual bool event(UIEvent* event);

protected:
	GLSimpleState();
	~GLSimpleState();

private:
	void lightOn();
	void lightOff();

private:
	bool m_initialized;

	OGL3DCamera m_camera;

	//input
	bool m_buttonPressed;
	int m_startX;
	int m_startY;
};

