/**
 * @class Template
 * @brief Template class header for Universe.
 */
#pragma once

#include "T2lCube1.h"
#include "T2lColor.h"

namespace T2l {

class  DrawGl
{
public:
//! @section Enums
//! @section Construction
    DrawGl(int arg) = delete;
//! @section Methods
    static void drawLine( float x0, float y0, float z0, float x1, float y1, float z1 );
    static void drawFace( Cube1& cube, int faceIndex, const Color& color, double shift = 0.0 );
    static void drawFaceUv( Cube1& cube, int faceIndex, const Color& color);
    static void drawFaceM( Cube1& cube, int faceIndex, const Color& color);
    static void drawCube(float s);
//! @section Overrides
//=============================================================================
protected:
//! @section Data
    int arg_;
//! @section Friends
//! @section Hidding
};

} //namespace T2l
