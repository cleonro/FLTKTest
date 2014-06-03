#include "gltest.h"
#include "Quaternion.h"
#include "Matrix4x4.h"
#include "VariousObjects.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>

#include <windows.h>
#include <GL/GL.h>

#if 0
extern std::string AppResPath;

OSpecialMesh::OSpecialMesh(int n, int m, float size1, float size2)
{
    R1 = size1;//50.0;
    R2 = size2;//5.0;

    Xmax = size1;//50.0f;
    R = size2;//5.0f;

    N = n;
    M = m;

    c_vertices = NULL;
    c_colors = NULL;
    c_normals = NULL;
    c_indices = NULL;

    NPoints = 0;
}

OSpecialMesh::~OSpecialMesh()
{
    delete [] c_vertices;
    delete [] c_colors;
    delete [] c_normals;
    delete [] c_indices;
}

void OSpecialMesh::GeneratePoint(eMeshes type, int n, int m, float& x, float& y, float& z,
									float& nx, float& ny, float& nz,
									float& red, float& green, float& blue, float& alpha)
{
   float dt = 0.0f;
   float dh = 0.0f;
   float zh = 0.0f;
   float du = 0.0f;

    switch(type) {
        case CYLINDER:
        //cylinder
            dt = 2 * M_PI / (N-1);
            dh = Xmax / (M - 1);

            //x = m * dh;
            x = -m * dh;
            y = R * cos(n * dt);
            z = R * sin(n * dt);

            nx = 0;
            ny = cos(n * dt);
            nz = sin(n * dt);

            red = 0.4 + 0.6 * x / Xmax;
            green = 0;
            blue = 0;
            alpha = 1.0;
            break;

        case THORUS:
        //tor
            dt = M_PI / (N-1);
            du = 2 * M_PI / (M - 1);

            //zh = 3;

            //x = (R1 + R2 * cos(m * du)) * cos(n * dt);
            //y = (R1 + R2 * cos(m * du)) * sin(n * dt);
            //z =  R2 * sin(m * du) + zh * (n * dt);

            z = (R1 + R2 * cos(m * du)) * cos(n * dt);
            x = (R1 + R2 * cos(m * du)) * sin(M_PI + n * dt);
            y =  R2 * sin(m * du) + zh * (n * dt);

            nx = cos(m * du) * cos(n * dt);
            ny = cos(m * du) * sin(n * dt);
            nz = sin(m * du);

            blue = 0.5 + 0.5 * cos(n * dt);
            green = 0.5 + 0.5 * sin(n * dt);
            red = (n + 0.0) / (N - 1.0);
            alpha = 1.0;
            break;

        case SPHERE:
        //sphere
            dt = M_PI / (N-1);
            du = 2 * M_PI / (M - 1);

            x = R1 * cos(m * du) * sin(n * dt);
            y = R1 * sin(m * du) * sin(n * dt);
            z = R1 * cos(n * dt);

            nx = cos(m * du) * sin(n * dt);
            ny = sin(m * du) * sin(n * dt);
            nz = cos(n * dt);

            red = 0.5 + 0.5 * cos(n * dt);
            green = 0.5 + 0.5 * sin(n * dt);
            blue = (n + 0.0) / (N - 1.0);
            alpha = 1.0;
            break;
    }
}

void OSpecialMesh::AddCoordinates(int index, float x0, float y0, float z0,
								float x1, float y1, float z1,
								float x2, float y2, float z2)
{
	c_vertices[9 * index] = x0;
	c_vertices[9 * index + 1] = y0;
	c_vertices[9 * index + 2] = z0;

	c_vertices[9 * index + 3] = x1;
	c_vertices[9 * index + 4] = y1;
	c_vertices[9 * index + 5] = z1;

	c_vertices[9 * index + 6] = x2;
	c_vertices[9 * index + 7] = y2;
	c_vertices[9 * index + 8] = z2;
}

void OSpecialMesh::AddNormals(int index, float nx0, float ny0, float nz0,
								float nx1, float ny1, float nz1,
								float nx2, float ny2, float nz2)
{
	c_normals[9 * index] = nx0;
	c_normals[9 * index + 1] = ny0;
	c_normals[9 * index + 2] = nz0;

	c_normals[9 * index + 3] = nx1;
	c_normals[9 * index + 4] = ny1;
	c_normals[9 * index + 5] = nz1;

	c_normals[9 * index + 6] = nx2;
	c_normals[9 * index + 7] = ny2;
	c_normals[9 * index + 8] = nz2;
}

void OSpecialMesh::AddColors(int index, float red0, float green0, float blue0, float alpha0,
								float red1, float green1, float blue1, float alpha1,
								float red2, float green2, float blue2, float alpha2)
{
	c_colors[12 * index] = red0;
	c_colors[12 * index + 1] = green0;
	c_colors[12 * index + 2] = blue0;
	c_colors[12 * index + 3] = alpha0;

	c_colors[12 * index + 4] = red1;
	c_colors[12 * index + 5] = green1;
	c_colors[12 * index + 6] = blue1;
	c_colors[12 * index + 7] = alpha1;

	c_colors[12 * index + 8] = red2;
	c_colors[12 * index + 9] = green2;
	c_colors[12 * index + 10] = blue2;
	c_colors[12 * index + 11] = alpha2;
}

void OSpecialMesh::WriteToFile()
{
    std::string path = AppResPath + "Cylinder_.txt";
    FILE *f = fopen(path.c_str(), "w");

	fprintf(f, "%s\n", "[CenterlineProx]");
	fprintf(f, "%s\n", "[Vessel]");

	int nr_triangles = 2 * (N - 1) * (M - 1);
	for(int i = 0; i < 3 * nr_triangles; i++)
	{
		int index = c_indices[i];
		
		float x = c_vertices[3 * index];
		float y = c_vertices[3 * index + 1];
		float z = c_vertices[3 * index + 2];
		
		float nx = c_normals[3 * index];
		float ny = c_normals[3 * index + 1];
		float nz = c_normals[3 * index + 2];
		
		float red = c_colors[4 * index];
		float green = c_colors[4 * index + 1];
		float blue = c_colors[4 * index + 2];
        //float alpha = c_colors[4 * index + 3];
		
		int ired = red * 255;
		int igreen = green * 255;
		int iblue = blue * 255;
		int color = (iblue >> 16) + (igreen >> 8) + ired;

		fprintf(f, "%f %f %f %f %f %f %d\n", x, y, z, nx, ny, nz, color);
	}

	fclose(f);
}

void OSpecialMesh::GenerateData(eMeshes type)
{
	int nr_triangles = 2 * (N - 1) * (M - 1);
	c_vertices = new float[3 * nr_triangles * 3];
	c_colors = new float[3 * nr_triangles * 4];
	c_normals = new float[3 * nr_triangles * 3];
	c_indices = new unsigned int[3 * nr_triangles];

	//vertices generation
	int index = 0;//triangle index
	for(int m = 0; m < M-1; m++)
	{
		for(int n = 0; n < N - 1; n++)
		{
			//0 point
			float x0, y0, z0, nx0, ny0, nz0, red0, green0, blue0, alpha0;
            GeneratePoint(type, n, m, x0, y0, z0, nx0, ny0, nz0, red0, green0, blue0, alpha0);

			//1 point
			float x1, y1, z1, nx1, ny1, nz1, red1, green1, blue1, alpha1;
            GeneratePoint(type, n + 1, m, x1, y1, z1, nx1, ny1, nz1, red1, green1, blue1, alpha1);

			//2 point
			float x2, y2, z2, nx2, ny2, nz2, red2, green2, blue2, alpha2;
            GeneratePoint(type, n, m + 1, x2, y2, z2, nx2, ny2, nz2, red2, green2, blue2, alpha2);

			//3 point
			float x3, y3, z3, nx3, ny3, nz3, red3, green3, blue3, alpha3;
            GeneratePoint(type, n + 1, m + 1, x3, y3, z3, nx3, ny3, nz3, red3, green3, blue3, alpha3);

			//first triangle - 012 
			AddCoordinates(index, x0, y0, z0, x1, y1, z1, x2, y2, z2);
			AddNormals(index, nx0, ny0, nz0, nx1, ny1, nz1, nx2, ny2, nz2);
			AddColors(index, red0, green0, blue0, alpha0, red1, green1, blue1, alpha1,
						red2, green2, blue2, alpha2);

			//second triangle - 132
			index += 1;//triangle index 
			AddCoordinates(index, x1, y1, z1, x3, y3, z3, x2, y2, z2);
			AddNormals(index, nx1, ny1, nz1, nx3, ny3, nz3, nx2, ny2, nz2);
			AddColors(index, red1, green1, blue1, alpha1, red3, green3, blue3, alpha3,
						red2, green2, blue2, alpha2);
			index += 1;
		}
	}

	//indices generation
	for(int i = 0; i < 3 * nr_triangles; i++)
	{
		c_indices[i] = i;
	}
    NPoints = 3 * nr_triangles;

	//WriteToFile();
}

float xmin = 0, xmax = 0;
float ymin = 0, ymax = 0;
float zmin = 0, zmax = 0;

void OSpecialMesh::GenerateDataFromFile(const char* file_name)
{
        std::fstream f(file_name, std::ios::in);
        if(!f.is_open())
        {
            return;
        }

        std::vector<point3> coordinates;
        std::vector<point3> normals;
        std::vector<point4> colors;
        std::vector<unsigned int> indices;

        coordinates.reserve(65000);
        normals.reserve(65000);
        colors.reserve(65000);
        indices.reserve(65000);

        std::string line;
        std::istringstream linestream;
        point3 coord;
        point3 nor;
        point4 col;
        unsigned int icol;
        bool vessel_found = false;
        while(!f.eof()) {
            std::getline(f, line);
            if(line != "[Vessel]" && !vessel_found) {
                continue;
            } else if(!vessel_found) {
                vessel_found = true;
                continue;
            }
            linestream.clear();
            linestream.str(line.c_str());
            linestream >> coord.x >> coord.y >> coord.z >> nor.x >> nor.y >> nor.z >> icol;
            size_t i = 0;
            for(i = 0; i < coordinates.size(); i++) {
                if(coord == coordinates[i]) {
                    break;
                }
            }

            if(i == 0) {
                xmin = xmax = coord.x;
                ymin = ymax = coord.y;
                zmin = zmax = coord.z;
            }

            if(i == coordinates.size()) {

                xmin = xmin > coord.x ? coord.x : xmin;
                xmax = xmax < coord.x ? coord.x : xmax;

                ymin = ymin > coord.y ? coord.y : ymin;
                ymax = ymax < coord.y ? coord.y : ymax;

                zmin = zmin > coord.z ? coord.z : zmin;
                zmax = zmax < coord.z ? coord.z : zmax;

                coordinates.push_back(coord);
                normals.push_back(nor);
                col.a = 1.0;//(icol >> 24) & 0xff / 255.0;
                unsigned int blue = ((icol >> 16) & 0xff);
                col.b = 1.0 * blue / 255.0;
                unsigned int green = ((icol >> 8 ) & 0xff);
                col.g = 1.0 * green / 255.0;
                unsigned int red = ((icol ) & 0xff);
                col.r = 1.0 * red / 255.0;
                colors.push_back(col);
            }
            indices.push_back(i/*coordinates.size() - 1*/);
        }
        f.close();

        int size = coordinates.size();
        c_vertices = new float[3 * size];
        c_normals = new float[3 * size];
        c_colors = new float[4 * size];
        c_indices = new unsigned int[indices.size()];

        for(int i = 0; i < size; i++) {

            point3 coord = coordinates[i];
            point3 nor = normals[i];
            point4 col = colors[i];

            c_vertices[3 * i] = coord.x;
            c_vertices[3 * i + 1] = coord.y;
            c_vertices[3 * i + 2] = coord.z;

            c_normals[3 * i] = nor.x;
            c_normals[3 * i + 1] = nor.y;
            c_normals[3 * i + 2] = nor.z;

            c_colors[4 * i] = col.r;
            c_colors[4 * i + 1] = col.g;
            c_colors[4 * i + 2] = col.b;
            c_colors[4 * i + 3] = col.a;
        }

        for(size_t i = 0; i < indices.size(); i++) {
            c_indices[i] = indices[i];
        }
        NPoints = indices.size();
    std::cout<<"GenerateDataFromFile out "<<NPoints<<" points"<<std::endl;
}

void OSpecialMesh::DrawMeshFromFile(const char* file_name)
{
//	static bool b = false;
//	if(!b) {
//		b = true;
//		GenerateDataFromFile(file_name);
//	}

    if(c_vertices == NULL) {
        GenerateDataFromFile(file_name);
    }

//	OGL3DCamera& camera = APPMNGR.GetState()->GetCamera();
//	OVector3 lookat((xmax + xmin) / 2.0, (ymax + ymin) / 2.0, (zmax + zmin) / 2.0);
	
//	camera.LookAt(lookat, camera.GetRoll());

	glVertexPointer(3, GL_FLOAT, 0, c_vertices);
	glColorPointer(4, GL_FLOAT, 0, c_colors);
	glNormalPointer(GL_FLOAT, 0, c_normals);
	glDrawElements(GL_TRIANGLES, NPoints, GL_UNSIGNED_INT, c_indices);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    VDraws->DrawBox(OVector3(xmin, ymin, zmin), OVector3(xmax, ymax, zmax));
}

void OSpecialMesh::DrawMesh(eMeshes type)
{
    if(c_vertices == NULL) {
        GenerateData(type);
    }
    glVertexPointer(3, GL_FLOAT, 0, c_vertices);
    glColorPointer(4, GL_FLOAT, 0, c_colors);
    glNormalPointer(GL_FLOAT, 0, c_normals);
    glDrawElements(GL_TRIANGLES, NPoints, GL_UNSIGNED_INT, c_indices);
}
//end class OSpecialMesh

#endif //0

void DrawAxis(float radius, float length)
{
    const int N = 16;
    const float ang = 2.0 * M_PI / N;
    const float h = length / 20.0;
    glBegin(GL_QUAD_STRIP);
    for(int i = 0; i <= N; i++)
    {
        float x = radius * cosf(ang * i);
        float y = radius * sinf(ang * i);
        float sq = sqrt(x * x + y * y);
        glNormal3f( x / sq, y / sq, 0);
        glVertex3f(x, y, length / 2.0 - h);
        glVertex3f(x, y, -length / 2);

    }
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f( 0, 0, 1);
    glVertex3f(0, 0, length / 2 );
    for(int i = 0; i <= N; i++)
    {
        float x = 2.0 * radius * cosf(ang * i);
        float y = 2.0 * radius * sinf(ang * i);
        float sq = sqrt(x * x + y * y);
        glNormal3f( x / sq, y / sq, 0);
        glVertex3f(x, y, length / 2 - h);

    }
    glEnd();
}

void DrawAxes(float length)
{
   //x
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glColor4f(1.0, 0.0, 0.0, 0.8);
    DrawAxis(0.01 * length, length);
    //y
    glRotatef(-90, 1, 0, 0);
    glColor4f(0.0, 1.0, 0.0, 0.8);
    DrawAxis(0.01 * length, length);
    glPopMatrix();

    //z
    glColor4f(0.0, 0.0, 1.0, 0.8);
    DrawAxis(0.01 * length, length);
    glColor4f(1.0, 1.0, 1.0, 1.0);
}

//cube
const GLfloat l = 30.0f; 
const GLfloat d = -l / sqrtf(3.f * l * l);
GLfloat cube[8 * 10] = {
	-l,  l,  l, 0.0, 1.0, 1.0, 1.0,  -d, d, d * 0,//0
	l,  l,  l, 1.0, 1.0, 1.0, 1.0, d, d, d * 0,//1
	l,  l, -l, 1.0, 1.0, 0.0, 1.0, d, d, -d * 0,//2
	-l,  l, -l, 0.0, 1.0, 0.0, 1.0, -d, d,  -d * 0,//3

	-l, -l,  l, 0.0, 0.0, 1.0, 1.0,  -d,  -d, d * 0,//4
	l, -l,  l, 1.0, 0.0, 1.0, 1.0, d,  -d, d * 0,//5
	l, -l, -l, 1.0, 0.0, 0.0, 1.0, d,  -d,  -d * 0,//6
	-l, -l, -l, 0.0, 0.0, 0.0, 1.0, -d, -d, - d * 0 //7
};
GLuint indices[6 * 4] = {
	0, 1, 2, 3,
	0, 3, 7, 4,
	0, 4, 5, 1,
	1, 5, 6, 2,
	2, 6, 7, 3,
	4, 5, 6, 7
};

void DrawCube()
{
	glVertexPointer(3, GL_FLOAT, 10 * 4, cube);
	glColorPointer(4, GL_FLOAT, 10 * 4, (void*)(cube + 3));
	glNormalPointer(GL_FLOAT, 10 * 4, (void*)(cube + 7));
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, indices);
}
//

void draw_axis(OVector3 origin, OVector3 direction, float length, bool arrow, float radius_f)
{
    direction.normalize();

    const float radius = radius_f * length;
    const int N = 16;
    const float ang = 2.0f * (float)M_PI / N;
    const float h = arrow ? length / 20.0f : 0;

    OVector3 middle_point = origin + (length / 2.0f) * direction;
    OVector3 z_axis(0.0f, 0.0f, 1.0f);

    OQuaternion q_orientation;
    q_orientation.shortest_rotation(z_axis, direction);
    OMatrix4 matrix_orientation = q_orientation.ToMatrix();

    glPushMatrix();
    glTranslatef(middle_point.X(), middle_point.Y(), middle_point.Z());
    glMultMatrixf(matrix_orientation.GetSafeM());

    glBegin(GL_TRIANGLE_STRIP);
    for(int i = 0; i <= N; i++)
    {
        float x = radius * cosf(ang * i);
        float y = radius * sinf(ang * i);
        float sq = sqrt(x * x + y * y);
        glNormal3f( x / sq, y / sq, 0.0f);
        glVertex3f(x, y, length / 2.0f - h);
        glVertex3f(x, y, -length / 2.0f);

    }
    glEnd();
    if(!arrow)
    {
        glPopMatrix();
        return;
    }
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f( 0, 0, 1);
    glVertex3f(0, 0, length / 2);
    for(int i = 0; i <= N; i++)
    {
        float x = 2.0f * radius * cosf(ang * i);
        float y = 2.0f * radius * sinf(ang * i);
        float sq = sqrt(x * x + y * y);
        glNormal3f( x / sq, y / sq, 0);
        glVertex3f(x, y, length / 2 - h);

    }
    glEnd();

    glPopMatrix();
}

void draw_axes(float length)
{
    //x
    glColor4f(1.0f, 0.0f, 0.0f, 0.8f);
    draw_axis(OVector3(-length * 0.5f, 0.0f, 0.0f), OVector3(1.0f, 0.0f, 0.0f), length);
    //y
    glColor4f(0.0f, 1.0f, 0.0f, 0.8f);
    draw_axis(OVector3(0.0f, -length * 0.5f, 0.0f), OVector3(0.0f, 1.0f, 0.0f), length);
    //z
    glColor4f(0.0f, 0.0f, 1.0f, 0.8f);
    draw_axis(OVector3(0.0f, 0.0f, -length * 0.5f), OVector3(0.0f, 0.0f, 1.0f), length);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}
