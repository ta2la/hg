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
#include "T2lIdentifyLine.h"
#include "T2lArea2.h"
#include "T2lSfeatLine.h"
#include "T2lSfeatLineS.h"
#include "T2lEntityLine.h"
#include "T2lEntityList.h"
#include "T2lCanvas.h"

using namespace T2l;//CHECKEND

//=============================================================================
IdentifyLine::IdentifyLine(const Canvas& canvas) :
    Identify(canvas)
{
    if (enlargement_ < 0) enlargement_ = 0;
}

//=============================================================================
bool IdentifyLine::byPoint(const Point2F& pt)
{
    Area2 area;
    exactArea_(area);

    return area.isInside(pt);
}

//=============================================================================
bool IdentifyLine::byBox(const Box2F& box)
{
    for ( int i = 0; i < polyline_.points().count(); i++ ) {
        if ( box.isInside(polyline_.points().getRef(i)) == false ) return false;
    }

    return true;
}

//=============================================================================
void IdentifyLine::display(EntityList& list)
{
    //TODO
}

//=============================================================================
void IdentifyLine::exactArea_(Area2& area)
{
    if (polyline_.points().count() < 2) return;

    double offset = enlargement()/canvas_.scaleX()/1000.0;

    for (int i = 0; i < points().count(); i++) {
        area.points().points().add(polyline_.offsetVertex(i, offset));
    }
    for (int i = points().count()-1; i >=0; i++) {
        area.points().points().add(polyline_.offsetVertex(i, -offset));
    }
}

//=============================================================================
