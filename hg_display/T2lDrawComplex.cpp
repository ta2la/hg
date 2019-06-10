//
// Copyright (C) 2017 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lDrawComplex.h"
#include "T2lStyle.h"
#include "T2lSfeatArea.h"
#include "T2lEntityArea.h"

using namespace T2l;

//=============================================================================
void DrawComplex::drawArrow(EntityList& list, const Point2F& position, Side side)
{
    double d = 50;

    if ( side == ALL ) return;

    Point2F p0(position);
    Point2F p1(position);
    Point2F p2(position);

    switch (side)
    {
    case ALL:    return;
    case LEFT:   p1.add(Vector2F(-d,  0)); p0.add(Vector2F( 0, -d)); p2.add(Vector2F( 0, d)); break;
    case RIGHT:  p1.add(Vector2F( d,  0)); p0.add(Vector2F( 0, -d)); p2.add(Vector2F( 0, d)); break;
    case TOP:    p1.add(Vector2F( 0,  d)); p0.add(Vector2F(-d,  0)); p2.add(Vector2F( d, 0)); break;
    case BOTTOM: p1.add(Vector2F( 0, -d)); p0.add(Vector2F(-d,  0)); p2.add(Vector2F( d, 0)); break;
    }

    Style* style = new Style("");
    style->sfeats().add( new SfeatArea(Color(255, 100, 100), 220));

    EntityArea* entityArea = new EntityArea( *style, true, NULL );
    entityArea->points().points().add( p0 );
    entityArea->points().points().add( p1 );
    entityArea->points().points().add( p2 );

    list.add(entityArea);
}

//=============================================================================
