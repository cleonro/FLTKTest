#include "GLSimpleState.h"
#include "MainWindow.h"
#include "gltest.h"
#include <windows.h>
#include <GL/GL.h>

GLSimpleState::GLSimpleState() :
	m_initialized(false)
{
	m_buttonPressed = false;
	m_startX = -100;
	m_startY = -100;
}


GLSimpleState::~GLSimpleState()
{

}

void GLSimpleState::init(void* data)
{
	if(data != NULL)
	{
		float aspect = *(float*)data;
		m_camera.SetPerspective(OVector4(1, 2048, 75, aspect));
		if(!m_initialized)
		{
			m_camera.PlaceAt(OVector3(- 3 * 39, 1 * 50, 5 * 30 + 20));
			m_camera.LookAt(OVector3(0, 0, 0));
		}
	}


	if(!m_initialized)
	{
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
}

void GLSimpleState::clear()
{

}

void GLSimpleState::update(void* data)
{
	m_camera.SetGLModelViewMatrix();
}

void GLSimpleState::render()
{
	glClearColor(0.3, 0.5, 0.7, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightOn();
	DrawAxes(100.0f);
	//glEnable(GL_NORMALIZE);

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_NORMAL_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	//static OSpecialMesh mesh(100, 100, 50.0f, 5.0f);
	//static std::string path = AppResPath + "Bifurcation 1 (ARO).txt";
	//mesh.DrawMeshFromFile(path.c_str());
	//mesh.DrawMesh(OSpecialMesh::THORUS);
	//mesh.DrawMesh(OSpecialMesh::SPHERE);
	//mesh.DrawMesh(OSpecialMesh::CYLINDER);
	//glDisableClientState(GL_COLOR_ARRAY);

	lightOff();
}

bool GLSimpleState::initialized()
{
	return m_initialized;
}

void GLSimpleState::lightOn()
{
	// Enable lighting, one light source, and color material
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_LIGHT1 );
	
	glEnable( GL_COLOR_MATERIAL );

	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	
	// Specify a white specular highlight
	const GLfloat ambient[4] = { 0.5f, 0.5f, 0.5f, 1.f };
	const GLfloat white[4] = { 0.8f, 0.8f, 0.8f, 1.f };
	const GLfloat pos[4] = { 0.f, 0.f, 170.0f, 1.0f };
	const GLfloat pos1[4] = { 0.f, 0.f, -70.0f, 0.0f };
	const GLfloat dir[3] = { 0.0f, 0.0f, -1.0f};
	const GLfloat dir1[3] = { 0.0f, 0.0f, 1.0f};
    //const GLfloat cutoff = 85.0f;

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, true);

	//glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff);
	glLightfv( GL_LIGHT0, GL_POSITION, pos );
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
// 	glLightfv(GL_LIGHT0, GL_AMBIENT, white);
// 	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	
	glLightfv( GL_LIGHT1, GL_POSITION, pos1 );
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, dir1);
// 	glLightfv(GL_LIGHT1, GL_AMBIENT, white);
// 	glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white);

	glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, white );
	glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, 85.f );
/*
	const GLfloat yell[] = {0.5f, 0.5f, 0.1f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yell);

	const GLfloat rd[] = {0.5f, 1.0f, 1.0f};
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, rd);
*/
}

void GLSimpleState::lightOff()
{
	glDisable(GL_LIGHTING);
}

bool GLSimpleState::event(UIEvent* event)
{
	if(event == nullptr)
	{
		return true;
	}

	switch(event->type())
	{
	case UIEvent::MOUSE_DOWN:
		if(event->rbutton(0))
		{
			m_buttonPressed = true;
			m_startX = event->rx();
			m_startY = event->ry();
		}		
		break;
	case UIEvent::MOUSE_MOVE:
		if(m_buttonPressed)
		{
			float dx = 0.5 * (event->rx() - m_startX);
			float dy = 0.5 * (event->ry() - m_startY);
			m_startX = event->rx();
			m_startY = event->ry();
			m_camera.Pitch(-dy);//? possible problems with Pitch?
			m_camera.Yaw(-dx);
		}
		break;
	case UIEvent::MOUSE_UP:
		m_buttonPressed = false;
		break;
	case UIEvent::MOUSE_WHEEL:
		{
			const float dist = 8.0f;
			if(event->ry() > 0)
			{
				m_camera.Translate(dist);
			}
			else
			{
				m_camera.Translate(-dist);
			}
		}
		break;
	}

	return true;
}