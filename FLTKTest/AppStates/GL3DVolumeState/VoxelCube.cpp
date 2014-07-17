#include "VoxelCube.h"
#include "VariousObjects.h"
#include "GLCamera.h"

#include "glext.h"

const int VoxelCube::FACE_FRONT=1;
const int VoxelCube::FACE_BACK=2;
const int VoxelCube::FACE_RIGHT=4;
const int VoxelCube::FACE_LEFT=8;
const int VoxelCube::FACE_BOTTOM=16;
const int VoxelCube::FACE_TOP=32;

const int VoxelCube::ecodes_[12] = {
	// edge 0                   edge 1                edge 2                  edge 3
	(FACE_FRONT+FACE_BOTTOM),(FACE_FRONT+FACE_TOP),(FACE_BACK+FACE_BOTTOM),(FACE_BACK+FACE_TOP),
	// edge 4                  edge 5                  edge 6                edge 7 
	(FACE_FRONT+FACE_LEFT ),(FACE_FRONT+FACE_RIGHT),(FACE_BACK+FACE_LEFT),(FACE_BACK+FACE_RIGHT),
	// edge 8                  edge 9                   edge 10               edge 11
	(FACE_LEFT+FACE_BOTTOM),(FACE_RIGHT+FACE_BOTTOM),(FACE_TOP+ FACE_LEFT),(FACE_TOP+FACE_RIGHT) };

VoxelCube::VoxelCube()
{
	//quad_ = new GLfloat[12];
	id_ = 0;
	N_ = 128;
	image_ = new GLubyte[N_*N_*N_*4];

	transparency_ = 0.02f;
	camera_ = NULL;
}

VoxelCube::~VoxelCube()
{
	//delete [] quad_;
	delete [] image_;
}

void VoxelCube::SetCamera(OGL3DCamera* camera)
{
	camera_ = camera;
}

void VoxelCube::Init(GLfloat sz)
{
	size_= sz;//5.0f;
	num_ints_ = 0;
	ns_ = 200;
/*
	quad_[0] = -size_; quad_[1] = -size_; quad_[2] = 0.0f;
	quad_[3] =  size_; quad_[4] = -size_; quad_[5] = 0.0f;
	quad_[6] =  size_; quad_[7] =  size_; quad_[8] = 0.0f;
	quad_[9] = -size_; quad_[10] =  size_; quad_[11] = 0.0f;
*/
	const GLfloat minC = -size_;
	const GLfloat maxC =  size_;

	p_[0][1] = maxC; p_[0][2] = minC;
	p_[1][1] = maxC; p_[1][2] = maxC;
	p_[2][1] = minC; p_[2][2] = minC;
	p_[3][1] = minC; p_[3][2] = maxC;
	
	p_[4][0] = minC; p_[4][1] = maxC;
	p_[5][0] = maxC; p_[5][1] = maxC;
	p_[6][0] = minC; p_[6][1] = minC;
	p_[7][0] = maxC; p_[7][1] = minC;
	
	p_[8][0] = minC; p_[8][2] = minC;
	p_[9][0] = maxC; p_[9][2] = minC;
	p_[10][0] = minC; p_[10][2] = maxC;
	p_[11][0] = maxC; p_[11][2] = maxC;


	//InitImage();
}

void VoxelCube::Update()
{
	
}

void VoxelCube::Draw(bool withbox)
{
	UpdatePlanesInf();

	

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	if(withbox){
		glPushMatrix();
		glScalef(size_, size_, size_);
		VDraws->DrawCube();
		glPopMatrix();
	}
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_3D);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	if(dmin_ < 0) {
		//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_3D, id_);
		for(int i = 1; i <= ns_; i++) {
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			CalcViewAlignedIsectPolygon(i);

			glVertexPointer(3, GL_FLOAT, 0, polygon_);
			glTexCoordPointer(3, GL_FLOAT, 0, tex_polygon_);
			glNormalPointer(GL_FLOAT, 0, normals_);
			glDrawArrays(GL_POLYGON, 0, num_ints_);
		}
	}
	
/*
	glPushMatrix();

	glVertexPointer(3, GL_FLOAT, 0, quad_);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glDrawArrays(GL_LINE_LOOP, 0, 4);

	glPopMatrix();
*/
	glDisable(GL_TEXTURE_3D);
	glDisable(GL_BLEND);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void VoxelCube::CalcViewAlignedIsectPolygon(int k)
{
	const GLfloat minC = -size_;
	const GLfloat maxC =  size_;

	const GLfloat dist = dmin_ + (k + 0.0f)*(dmax_ - dmin_) / (ns_ + 1.0f);

	const GLfloat a = view_[0];
	const GLfloat b = view_[1];
	const GLfloat c = view_[2];
	const GLfloat d = a * (view_pos_[0] + dist * a) + b * (view_pos_[1] + dist * b) +
						c * (view_pos_[2] + dist * c);//0.0f;

	p_[0][0] = (d - b*p_[0][1] - c*p_[0][2]) / a;
	p_[1][0] = (d - b*p_[1][1] - c*p_[1][2]) / a;
	p_[2][0] = (d - b*p_[2][1] - c*p_[2][2]) / a;
	p_[3][0] = (d - b*p_[3][1] - c*p_[3][2]) / a;
	
	p_[4][2] = (d - a*p_[4][0] - b*p_[4][1]) / c;
	p_[5][2] = (d - a*p_[5][0] - b*p_[5][1]) / c;;
	p_[6][2] = (d - a*p_[6][0] - b*p_[6][1]) / c;;
	p_[7][2] = (d - a*p_[7][0] - b*p_[7][1]) / c;;
	
	p_[8][1] = (d - a*p_[8][0] - c*p_[8][2]) / b;
	p_[9][1] = (d - a*p_[9][0] - c*p_[9][2]) / b;
	p_[10][1] = (d - a*p_[10][0] - c*p_[10][2]) / b;
	p_[11][1] = (d - a*p_[11][0] - c*p_[11][2]) / b;

	num_ints_ = 0;
	bool used[12];
	int i, j;

	for(i = 0; i < 4; i++) {
		if((p_[i][0] > minC) && (p_[i][0] < maxC)) {
			used[i] = false;
			num_ints_++;
		} else {
			used[i] = true;
		}
	}

	for(i = 4; i < 8; i++) {
		if((p_[i][2] > minC) && (p_[i][2] < maxC)) {
			used[i] = false;
			num_ints_++;
		} else {
			used[i] = true;
		}
	}

	for(i = 8; i < 12; i++) {
		if((p_[i][1] > minC) && (p_[i][1] < maxC)) {
			used[i] = false;
			num_ints_++;
		} else {
			used[i] = true;
		}
	}

	int nEdgeCode = 0xFFFFFFFF;
	int numUsedIsects = 0;
	for(j = 0; j < num_ints_; j++) {
		for(i = 0; i < 12; i++){
			if((!used[i]) && (ecodes_[i] & nEdgeCode)) {
				used[i]=true;
				
				polygon_[numUsedIsects*3] = p_[i][0];
				polygon_[numUsedIsects*3 + 1] = p_[i][1];
				polygon_[numUsedIsects*3 + 2] = p_[i][2];

				tex_polygon_[numUsedIsects*3] = (polygon_[numUsedIsects*3] - minC) / (maxC - minC);
				tex_polygon_[numUsedIsects*3 + 1] = (polygon_[numUsedIsects*3 + 1] - minC) / (maxC - minC);
				tex_polygon_[numUsedIsects*3 + 2] = (polygon_[numUsedIsects*3 + 2] - minC) / (maxC - minC);

				normals_[numUsedIsects*3] = a;
				normals_[numUsedIsects*3 + 1] = b;
				normals_[numUsedIsects*3 + 2] = c;
				
				nEdgeCode=ecodes_[i];
				numUsedIsects++;
			}
		}
	}
}

void VoxelCube::UpdatePlanesInf()
{
	OVector3 view_direction = camera_->GetAxesK();
	OVector3 view_position = camera_->GetPosition();
	view_[0] = view_direction.X();
	view_[1] = view_direction.Y();
	view_[2] = view_direction.Z();
	view_pos_[0] = view_position.X();
	view_pos_[1] = view_position.Y();
	view_pos_[2] = view_position.Z();
	
	const GLfloat a = view_[0];
	const GLfloat b = view_[1];
	const GLfloat c = view_[2];

	const GLfloat ap = view_pos_[0];
	const GLfloat bp = view_pos_[1];
	const GLfloat cp = view_pos_[2];

	const GLfloat minC = -size_;
	const GLfloat maxC =  size_;

	//0
	GLfloat scp = -(a*(ap - minC) + b*(bp - minC) + c*(cp - minC));
	dmin_ = scp;
	dmax_ = scp;
	//1
	scp = -(a*(ap - minC) + b*(bp - minC) + c*(cp - maxC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//2
	scp = -(a*(ap - minC) + b*(bp - maxC) + c*(cp - minC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//3
	scp = -(a*(ap - minC) + b*(bp - maxC) + c*(cp - maxC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//4
	scp = -(a*(ap - maxC) + b*(bp - minC) + c*(cp - minC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//5
	scp = -(a*(ap - maxC) + b*(bp - minC) + c*(cp - maxC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//6
	scp = -(a*(ap - maxC) + b*(bp - maxC) + c*(cp - minC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;
	//7
	scp = -(a*(ap - maxC) + b*(bp - maxC) + c*(cp - maxC));
	dmin_ = (dmin_ > scp) ? scp : dmin_;
	dmax_ = (dmax_ < scp) ? scp : dmax_;

	if (dmax_ > 0) {
		dmax_ = 0;
	}

}

void VoxelCube::InitImage(/*bool b_col, bool r_col*//*, Matrix3D* matrix*/)
{
#ifdef WIN32
	PFNGLTEXIMAGE3DEXTPROC glTexImage3D = (PFNGLTEXIMAGE3DEXTPROC)wglGetProcAddress("glTexImage3DEXT");
#endif

	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	unsigned int s, t, r;
	for (r = 0; r < N_; r++) {
		for (t = 0; t < N_; t++) {
			for (s = 0; s < N_; s++) {
				const GLfloat x = (1.0f * s) / (N_ + 0.0f);
				const GLfloat y = (1.0f * t) / (N_ + 0.0f);
				const GLfloat z = (1.0f * r) / (N_ + 0.0f);
				const GLfloat dist = SQRT(fabs(x - 0.5f) * fabs(y - 0.5f) + fabs(z - 0.5f) * fabs(y - 0.5f) + fabs(x - 0.5f) * fabs(z - 0.5f));
				const GLfloat alpha = /*transparency_;/*//*(1.0f - powf(dist/SQRT(3.0f * 0.5f * 0.5f), 0.05));/*/ ( dist > 0.5) ? 0 : 0.1 * (1.0 - dist * dist / 0.25f);
				
				const int xc = 0;
				const int yc = 0;
				const int zc = 0;
								
				float xv = fabs(1.0 * cos(3.0 * dist * sin(7.0 * dist * dist) ));
				float yv = fabs(1.0 * sin(4.0 * dist * cos(dist)));
				float zv = fabs(1.0 * sin(0.1 * dist));
				//xv = xv > 1 ? 1 : (xv < 0 ? 0 : xv);
				//yv = yv > 1 ? 1 : (yv < 0 ? 0 : yv);
				//zv = zv > 1 ? 1 : (zv < 0 ? 0 : zv);


				image_[r * N_ * N_ * 4 + t * N_ * 4 + s * 4 + 0] = xv * 255;//200;
				image_[r * N_ * N_ * 4 + t * N_ * 4 + s * 4 + 1] = yv * 255;//200;
				image_[r * N_ * N_ * 4 + t * N_ * 4 + s * 4 + 2] = zv * 255;//210;
				image_[r * N_ * N_ * 4 + t * N_ * 4 + s * 4 + 3] = (GLubyte)(alpha * 255);
			}
		}
	}

	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	if(id_ == 0) {
		glGenTextures(1, &id_);
	}

glDisable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_3D, id_);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, /*GL_REPEAT*/GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, /*GL_REPEAT*/GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, /*GL_REPEAT*/GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, /*GL_NEAREST*/GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, /*GL_NEAREST*/GL_LINEAR);
	
	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, N_, N_, N_, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_);
	
}