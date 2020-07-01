//
// Copyright (C) 2020 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lEntityEnLinear.h"
#include "T2lComponentArea.h"
#include "T2lCanvas.h"
#include "T2lStyleChange.h"
#include "T2lEnPointMmRel.h"

using namespace T2l;

//=============================================================================
EntityEnLinear::EntityEnLinear(const Color& color, const Color& colorLine, int transp) :
    color_(color),
    colorLine_(colorLine),
    transp_(transp)
{
}

//=============================================================================
void EntityEnLinear::pointAdd( const Point2F& pt, const Point2F& offset)
{
    points_.add(pt);
    ofsets_.add(offset);
}

//=============================================================================
void EntityEnLinear::draw(Canvas* canvas)
{
    ComponentArea componentArea(color_);
    componentArea.alphaSet(120);

    for ( int i = 0; i < points_.count(); i++) {
        Point2F offset = ofsets_.get(i);
        EnPointMmRel pt( points_.get(i), Vector2F(offset.x(), offset.y()) );

        //componentArea.area().points().points().add(canvas->mapRealToPaper(points_.get(i)));
        componentArea.area().points().points().add(canvas->mapRealToPaper(pt.xy(canvas)));

        /*draw_( canvas, pt.xy(canvas), angle(), sfeatText->color(), sfeatText->height(),
               sfeatText->bold() );*/
    }

    canvas->draw(&componentArea);
}

//=============================================================================
