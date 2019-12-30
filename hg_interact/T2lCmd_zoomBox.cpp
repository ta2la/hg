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
#include "T2lCmd_zoomBox.h"
#include "T2lEntityPack.h"
#include "T2lDisplay.h"
#include "T2lWidget.h"
#include "T2lEntityLine.h"
#include "T2lEntityText.h"
#include "T2lEntityPoint.h"
#include "T2lSize2.h"
#include <iostream>

using namespace T2l;
using namespace std;

//=============================================================================
Cmd_zoomBox::Cmd_zoomBox() :
    Cmd("zoom by box"),
    pointKnown_(false)
{
}

//=============================================================================
Box2F Cmd_zoomBox::newDisplay_( const Point2F& pt, Display& view )
{
    if ( fabs(point_.x()-pt.x()) < 10e-9 ) point_.set(0, pt.x()-10e-9);
    if ( fabs(point_.y()-pt.y()) < 10e-9 ) point_.set(1, pt.y()-10e-9);

    double dx = pt.x()-point_.x();
    double dy = pt.y()-point_.y();

    Size2F viewSize = view.size();
    double ratioNeeded = fabs(viewSize.w()/viewSize.h());
    double ratio = fabs(dx/dy);

    double DX = dx;
    double DY = dy;

    if ( ratioNeeded > ratio ) {
        DX = ( ( dx > 0.0 ) ? 1.0 : -1.0 )*fabs(dy*ratioNeeded);
    }
    else {
        DY = ( ( dy > 0.0 ) ? 1.0 : -1.0 ) * fabs(dy/ratioNeeded);
    }

    return Box2F(point_, Point2F(point_.x()+DX, point_.y()+DY));
}

//=============================================================================
void Cmd_zoomBox::enterPoint( const Point2F& pt, Display& view )
{
    EntityPack* pack = view.entityPack();
    assert ( pack != NULL );

    pack->cleanDynamic();

    if ( pointKnown_ )
    {
        Box2F newDisplay = newDisplay_(pt, view);

        Point2F originNew (
            ( view.scale(Scale2::X) > 0 ) ? newDisplay.x().beg() : newDisplay.x().end(),
            ( view.scale(Scale2::Y) > 0 ) ? newDisplay.y().beg() : newDisplay.y().end() );

        view.originSet(originNew);
        view.scaleSet( view.getRefCanvas().scaleX()*view.size().w()/newDisplay.x().getLength(), Scale2::X );
        view.scaleSet( view.getRefCanvas().scaleY()*view.size().h()/newDisplay.y().getLength(), Scale2::Y );

        view.refresh();

        pointKnown_ = false;
        if ( once_ ) delete this;
    }
    else {
        point_ = pt;
        pointKnown_ = true;
    }
}

//=============================================================================
void Cmd_zoomBox::enterMove( const Point2F& pt, Display& view )
{
    if ( pointKnown_ == false ) return;

    EntityPack* pack = view.entityPack();

    pack->cleanDynamic();

    EntityLine* line = new EntityLine();
    for ( int i = 0; i < 5; i++ ) {
        line->points().points().add(newDisplay_(pt, view).getPoint(i));
    }
    pack->addDynamic(line);

    Style* pointStyle = Style::createPointStyle( Color::BLACK, Style::SYMBOL_CIRCLE_FILLED, 2, "" );
    EntityPoint* point = new EntityPoint( Point2F(point_.x(), point_.y()), *pointStyle, true,
                                            ANGLE_ZERO_VIEW, 0, NULL );
    pack->addDynamic(point);

    pack->dynamicRefresh();
}

//=============================================================================
