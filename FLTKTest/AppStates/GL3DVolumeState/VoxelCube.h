#pragma once

#ifndef _VOXEL_CUBE_H_
#define _VOXEL_CUBE_H_

#include <windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>

struct gPoint10 {
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
	GLfloat nx;
	GLfloat ny;
	GLfloat nz;
};

class Matrix3D;
class OGL3DCamera;

class VoxelCube
{
protected:
	OGL3DCamera* camera_;
	unsigned int N_;
	GLfloat size_;
	GLfloat *quad_;

	static const int FACE_FRONT;
	static const int FACE_BACK;
	static const int FACE_RIGHT;
	static const int FACE_LEFT;
	static const int FACE_BOTTOM;
	static const int FACE_TOP;

	static const int ecodes_[12];

	GLfloat p_[12][3];				// volume points, used to compute intersection, 
									// p[i] = intersection of edge "i" with the section plane
	GLfloat polygon_[6 * 3];		// intersection polygon
	GLfloat tex_polygon_[6 * 3];	// texture polygon
	GLfloat normals_[6 * 3];

	GLuint id_;
	GLubyte *image_;
	
	unsigned short num_ints_;		// number of intersection points
	GLfloat view_[3];
	GLfloat view_pos_[3];
	GLfloat dmin_;
	GLfloat dmax_;
	GLfloat ns_;

	void CalcViewAlignedIsectPolygon(int );
	void UpdatePlanesInf();
	

public:
	VoxelCube();
	~VoxelCube();
	void Init(GLfloat );
	void Update();
	void Draw(bool withbox = false);
	void InitImage(/*bool b_col, bool r_col*//*, Matrix3D* matrix*/);

	void SetCamera(OGL3DCamera* camera);

	GLfloat transparency_;
};

#endif
