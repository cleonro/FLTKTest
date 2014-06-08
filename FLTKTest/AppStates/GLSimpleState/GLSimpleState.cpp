#include "GLSimpleState.h"
#include "MainWindow.h"
#include "gltest.h"
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
// 	if(m_initialized)
// 	{
// 		return;
// 	}

	if(data != NULL)
	{
		float aspect = *(float*)data;
		m_camera.SetPerspective(OVector4(1, 2048, 75, aspect));
		m_camera.PlaceAt(OVector3(- 3 * 39, 1 * 50, 5 * 30 + 20));
		m_camera.LookAt(OVector3(0, 0, 0));
	}

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