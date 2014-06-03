#pragma once

#define _USE_MATH_DEFINES

#include "Math/Vector3.h"

#if 0
class OSpecialMesh
{
public:

    struct point3
    {
        float x;
        float y;
        float z;
        bool operator==(const point3& p)
        {
            return x == p.x && y == p.y && z == p.z;
        }
    };

    struct point4
    {
        float r;
        float g;
        float b;
        float a;

    };

    enum eMeshes
    {
        SPHERE,
        CYLINDER,
        THORUS
    };

    OSpecialMesh(int n, int m, float size1, float size2);
    ~OSpecialMesh();

    void WriteToFile();

    void GenerateData(eMeshes type);

    void DrawMeshFromFile(const char* file_name);

    void DrawMesh(eMeshes type);

protected:

    void GeneratePoint(eMeshes type, int n, int m, float& x, float& y, float& z,
        float& nx, float& ny, float& nz,
        float& red, float& green, float& blue, float& alpha);

    void AddCoordinates(int index, float x0, float y0, float z0,
        float x1, float y1, float z1,
        float x2, float y2, float z2);

    void AddNormals(int index, float nx0, float ny0, float nz0,
        float nx1, float ny1, float nz1,
        float nx2, float ny2, float nz2);

    void AddColors(int index, float red0, float green0, float blue0, float alpha0,
        float red1, float green1, float blue1, float alpha1,
        float red2, float green2, float blue2, float alpha2);

    void GenerateDataFromFile(const char* file_name);

    float R1;
    float R2;

    float R;
    float Xmax;

    int N;
    int M;

    float *c_vertices;
    float *c_colors;
    float *c_normals;
    unsigned int *c_indices;

    int NPoints;
};
#endif //0

void DrawAxis(float radius, float length);

void DrawAxes(float length);

void DrawCube();

void draw_axis(OVector3 origin, OVector3 direction, float length, bool arrow = true, float radius_f = 0.01f);

void draw_axes(float length);
