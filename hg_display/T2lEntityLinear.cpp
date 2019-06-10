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
#include "T2lEntityLinear.h"
#include "T2lCanvas.h"
#include "T2lSfeatLine.h"
#include "T2lSfeatLineS.h"
#include "T2lRawSline.h"
#include "T2lRawLine.h"

using namespace T2l;

//=============================================================================
EntityLinear::EntityLinear( Style* style, bool styleOwner,
                                bool closed, StyleChange* styleChange ) :
    EntityStyled(style, styleOwner, styleChange),
    points_(closed)
{
}

//=============================================================================
void EntityLinear::drawBasic_(Canvas* canvas)
{
    if ( points_.count() < 2 ) return;

    //if ( check_(display) == false ) return; TODO - does not work

    for (int i = 0; i < style()->sfeats().count(); i++)
    {   Sfeat* sf = style_->sfeats().get(i);

        if ( sf->getAsLine() ) {
            SfeatLine* sfLine = sf->getAsLine();
            RawLine e ( sfLine->color(), sfLine->width(), sfLine->offset(),
                               sfLine->lstyle(), points().closed(), styleChange() );
            for ( int i = 0; i < points_.count(); i++) e.pline().points().add(points_.get(i));

            if ( canvas->draw(&e) == false ) e.decompose(canvas);
        }
        else if ( sf->getAsLineS() ) {
            RawSline e( *sf->getAsLineS(), styleChange(), points_.closed() );
            Point2FCol& points = e.pline().points();
            for ( int i = 0; i < points_.count(); i++ ) points.add(points_.get(i));

            if ( canvas->draw(&e) == false) e.decompose(canvas);
        }
    }
}

//=============================================================================
bool EntityLinear::check_(Canvas* canvas)
{
    Box2F bound = canvas->bound();
    Point2F safe = canvas->mapPaperToReal(Point2F(0.01, 0.01));

    Box2F bound2 = Box2F( IntervalF( bound.x().beg() - fabs( safe.x() ),
                                     bound.x().end() + fabs( safe.x() )),
                          IntervalF( bound.y().beg() - fabs( safe.y() ),
                                     bound.y().end() + fabs( safe.y() )) );

    return ( bound2.intersectWidth(bound_).isEmpty() == false );
}

//=============================================================================
