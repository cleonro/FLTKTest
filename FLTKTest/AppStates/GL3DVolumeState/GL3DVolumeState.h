#pragma once

#include "GLSimpleState.h"
#include "VoxelCube.h"

#define GL_3D_VOLUME_STATE "GL3DVolumeState"

class GL3DVolumeState : public GLSimpleState
{
	friend class StateManager;
public:
	virtual void init(void* data = nullptr);
	virtual void clear();
	virtual void update(void* data = nullptr);
	virtual void render();

protected:
	GL3DVolumeState();
	~GL3DVolumeState();

private:
	VoxelCube m_cube;
};

