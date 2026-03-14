//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "T2lEntityCube.h"
#include "T2lElemBox.h"
#include "T2lCanvas.h"
#include "T2lElemLine.h"

using namespace T2l;

//=============================================================================
EntityCube::EntityCube( const Cube1& cube, const Color& color ) :
    cube_(cube),
    color_(color)
{
}

//=============================================================================
void EntityCube::draw(Canvas* canvas)
{
    Point3F p30 = cube_.pointGet(0);
    Point2F pt0(p30.x(), p30.y());

    Point3F p31 = cube_.pointGet(1);
    Point2F pt1(p31.x(), p31.y());

    Point3F p32 = cube_.pointGet(2);
    Point2F pt2(p32.x(), p32.y());

    Point3F p33 = cube_.pointGet(3);
    Point2F pt3(p33.x(), p33.y());

    double width = 0.0001;
    if (cube_.point().z()>0.5 && cube_.point().z()<1.5)
        width = 0.001;

    ElemLine diag0( color_, width );
    diag0.points().points().add(canvas->mapRealToPaper(pt0));
    diag0.points().points().add(canvas->mapRealToPaper(pt1));
    canvas->draw(&diag0);

    ElemLine diag1( color_, width );
    diag1.points().points().add(canvas->mapRealToPaper(pt1));
    diag1.points().points().add(canvas->mapRealToPaper(pt2));
    canvas->draw(&diag1);

    ElemLine diag2( color_, width );
    diag2.points().points().add(canvas->mapRealToPaper(pt2));
    diag2.points().points().add(canvas->mapRealToPaper(pt3));
    canvas->draw(&diag2);

    ElemLine diag3( color_, width );
    diag3.points().points().add(canvas->mapRealToPaper(pt3));
    diag3.points().points().add(canvas->mapRealToPaper(pt0));
    canvas->draw(&diag3);
}

//=============================================================================
