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
#include "T2lIdentifyBox.h"
#include "T2lEntityLine.h"
#include "T2lEntityList.h"
#include "T2lCanvas.h"

using namespace T2l;//CHECKEND

//=============================================================================
IdentifyBox::IdentifyBox(const Canvas& canvas, const Box2F& box) :
    Identify(canvas),
    box_(box)
{
}

//=============================================================================
Box2F IdentifyBox::boxCalc_()
{
    double dx = enlargement_/canvas_.scaleX()/1000.0;
    double dy = enlargement_/canvas_.scaleY()/1000.0;

    return Box2F( IntervalF(box_.x().beg()-dx, box_.x().end()+dx),
                  IntervalF(box_.y().beg()-dy, box_.y().end()+dy) );
}

//=============================================================================
bool IdentifyBox::byPoint(const Point2F& pt)
{
    return boxCalc_().isInside(pt);
}

//=============================================================================
void IdentifyBox::display(EntityList& list)
{
    Box2F box = boxCalc_();

    EntityLine* e = new EntityLine(Color::BLUE);
    for ( int i = 0; i < 5; i++ ) {
        e->points().points().add(box.getPoint(i));
    }
    list.add(e);
}

//=============================================================================
