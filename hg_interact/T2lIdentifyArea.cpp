//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lIdentifyArea.h"
#include "T2lCanvas.h"
#include "T2lEntityLine.h"
#include "T2lEntityList.h"

using namespace T2l;//CHECKEND

//=============================================================================
IdentifyArea::IdentifyArea(const Canvas& canvas) :
    Identify(canvas),
    enlargement_(2)
{
}

double IdentifyArea::offset_()
{
    return enlargement_/canvas_.scaleX()/1000.0;
}

//=============================================================================
bool IdentifyArea::byPoint(const Point2F& pt)
{
    Area2 a;
    for ( int i = 0; i < area_.points().points().count(); i++ ) {
        a.points().points().add( area_.points().offsetVertex(i, offset_()) );
    }
    return a.isInside(pt);
}

//=============================================================================
bool IdentifyArea::byBox(const Box2F& box)
{
    Point2FCol& points = area_.points().points();

    for ( int i = 0; i < points.count(); i++) {
        if ( box.isInside(points.get(i)) == false ) return false;
    }

    return false;
}

//=============================================================================
void IdentifyArea::display(EntityList& list)
{
    EntityLine* entity = new EntityLine(Color::MAGENTA);
    for (int i = 0; i < area().points().points().count(); i++) {
        entity->points().points().add( area_.points().offsetVertex(i, offset_()) );
    }
    list.add(entity);
}

//=============================================================================
