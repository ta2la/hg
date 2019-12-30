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
#include "T2lIdentifyPoint.h"
#include "T2lSfeatSymbol.h"
#include "T2lEntityLine.h"
#include "T2lEntityList.h"
#include "T2lCanvas.h"

using namespace T2l;//CHECKEND

//=============================================================================
IdentifyPoint::IdentifyPoint( const Canvas& canvas, const Point2F& point, double enlargement ) :
    Identify(canvas, enlargement),
    point_(point),
    symbolH_(0.0),
    symbolV_(0.0)
{
}

//=============================================================================
Box2F IdentifyPoint::calcBox_()
{
    double dx = (enlargement()+symbolH_/2.0)/canvas_.scaleX()/1000.0;
    double dy = (enlargement()+symbolV_/2.0)/canvas_.scaleY()/1000.0;

    Box2F result;
    result.inflateTo(Point2F(point_.x()-dx, point_.y()-dy));
    result.inflateTo(Point2F(point_.x()+dx, point_.y()+dy));

    return result;
}

//=============================================================================
bool IdentifyPoint::byPoint(const Point2F& pt)
{
    return calcBox_().isInside(pt);
}

//=============================================================================
bool IdentifyPoint::byBox(const Box2F& box)
{
    Box2F box2 = calcBox_();
    return box.isInside(box2);
}

//=============================================================================
void IdentifyPoint::display(EntityList& list)
{
    Box2F box = calcBox_();
    EntityLine* e = new EntityLine(Color::MAGENTA);
    for ( int i = 0; i < 5; i++ ) {
        e->points().points().add(box.getPoint(i));
    }
    list.add(e);
}

//=============================================================================
