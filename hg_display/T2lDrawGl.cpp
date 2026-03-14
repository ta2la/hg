/**
 * @file Template.cpp
 * @brief Implementation of class Template
 */

#include "T2lDrawGl.h"

#include <GL/gl.h>
#include <GL/glu.h>

using namespace T2l;

//=============================================================================
void DrawGl::drawLine( float x0, float y0, float z0, float x1, float y1, float z1 )
{
    glBegin(GL_LINES);
    glVertex3d(x0, y0, z0);
    glVertex3d(x1, y1, z1);
    glEnd();
}

//=============================================================================
void DrawGl::drawFace( Cube1& cube, int faceIndex, const Color& color, double shift )
{
    std::array<int, 4> faceIndexes = cube.faceIndexes(faceIndex);

    glColor4f(color.rf(), color.gf(), color.bf(), 0.7);

    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++) {
        Point3F pti = cube.pointGet(faceIndexes[i], shift);
        glVertex3d(pti.x(), pti.y(), pti.z());
    }
    glEnd();
}

//=============================================================================
void DrawGl::drawFaceUv( Cube1& cube, int faceIndex, const Color& color )
{
    glColor4f(color.rf(), color.gf(), color.bf(), 0.7);

    glBegin(GL_QUADS);

    Grid3 grid = cube.faceGrid(faceIndex);
    Point3F p0 = grid.getPoint(Point2F(0.1,0.1));
    Point3F p1 = grid.getPoint(Point2F(0.1,0.9));
    Point3F p2 = grid.getPoint(Point2F(0.9,0.9));
    Point3F p3 = grid.getPoint(Point2F(0.9,0.1));

    glVertex3d(p0.x(), p0.y(), p0.z());
    glVertex3d(p1.x(), p1.y(), p1.z());
    glVertex3d(p2.x(), p2.y(), p2.z());
    glVertex3d(p3.x(), p3.y(), p3.z());

    glEnd();
}

//=============================================================================
void DrawGl::drawFaceM( Cube1& cube, int faceIndex, const Color& color )
{
    double mul[5][5] = {
        { 0.9, 0.8, 0.9, 1.0, 1.0},
        { 1.0, 1.1, 1.0, 1.2, 1.1 },
        { 0.9, 1.0, 1.1, 1.2, 1.2 },
        { 1.0, 1.1, 1.2, 1.1, 1.4 },
        { 0.9, 1.1, 1.4, 1.5, 1.3 }
    };

    Grid3 grid = cube.faceGrid(faceIndex);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            float r = color.rf()*mul[i][j];
            float g = color.gf()*mul[i][j];
            float b = color.bf()*mul[i][j];

            double u = 0.2*i;
            double v = 0.2*j;

            if (r > 1.0) r = 1.0;
            if (g > 1.0) g = 1.0;
            if (b > 1.0) b = 1.0;

            glColor4f(r, g, b, 1.0);

            glBegin(GL_QUADS);

            Point3F p0 = grid.getPoint(Point2F(u,    v));
            Point3F p1 = grid.getPoint(Point2F(u,    v+0.2));
            Point3F p2 = grid.getPoint(Point2F(u+0.2,v+0.2));
            Point3F p3 = grid.getPoint(Point2F(u+0.2,v));

            glVertex3d(p0.x(), p0.y(), p0.z());
            glVertex3d(p1.x(), p1.y(), p1.z());
            glVertex3d(p2.x(), p2.y(), p2.z());
            glVertex3d(p3.x(), p3.y(), p3.z());

            glEnd();
        }
    }
}

//=============================================================================
void DrawGl::drawCube(float s)
{
    float p =  1*s;
    float m = -1*s;

    drawLine(p, p, m, m, p, m);
    drawLine(m, p, m, m, m, m);
    drawLine(m, m, m, p, m, m);
    drawLine(p, m, m, p, p, m);

    drawLine(p, p, p, m, p, p);
    drawLine(m, p, p, m, m, p);
    drawLine(m, m, p, p, m, p);
    drawLine(p, m, p, p, p, p);

    drawLine(p, p, m, p, p, p);
    drawLine(m, p, m, m, p, p);
    drawLine(m, m, m, m, m, p);
    drawLine(p, m, m, p, m, p);
}
//=============================================================================
