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
#include "T2lTentativeImplementation.h"
#include "T2lEntityPack.h"
#include "T2lDisplay.h"
#include "T2lEntityLine.h"
#include "T2lEntityPoint.h"
#include <iostream>
#include "T2lUpdateLock.h"
#include "T2lScene.h"
#include "T2lSfeatSymbol.h"
#include "T2lSitemLine.h"

using namespace T2l;
using namespace std;//CHECKEND

//=============================================================================
TentativeImplementation::TentativeImplementation() :
    entered_(false)
{
}

//=============================================================================
Point3F TentativeImplementation::consume()
{
    assert(entered_);
    entered_ = false;

    for (int i = 0; i < entities_.count(); i++) {
        delete entities_.get(i);
    }
    entities_.clean();

    //scene_->dirtySet();
    consumeEx();

    return position_;
}

//=============================================================================
void TentativeImplementation::cleanTentative_(Display& view)
{
    UpdateLock l;

    for (int i = 0; i < entities_.count(); i++) {
        delete entities_.get(i);
    }
    entities_.clean();

    consumeEx();

    entered_ = false;
}

//=============================================================================
void TentativeImplementation::enterTentative_( const Point3F& pt, Display& view )
{
    UpdateLock l;

    //if (entered_) consume();
    entered_ = true;
    position_ = pt;

    EntityPack* pack = view.entityPack();
    if ( pack == nullptr ) { assert(0); return; }
    if ( pack->scene() == nullptr ) return;

    for (int i = 0; i < entities_.count(); i++) {
        delete entities_.get(i);
    }
    entities_.clean();

    //int SIZE = 4;

    //<STEP> Dynamic drawing
    /*static Style style* = nullptr;
    if (style == nullptr) {
        style = new Style();

        Symbol* symbol = new Symbol();

        SfeatSymbol sfeat = new SfeatSymbol();*/

    Style* style = nullptr;
    if (style == nullptr) {
        Symbol* symbolObj = new Symbol();
        double width = 0.0005;
        double size  = 0.01;
        SitemLine* sitem = new SitemLine(Color::MAGENTA, width);
        sitem->points().points().add(Point2F( size, size ));
        sitem->points().points().add(Point2F( -size, -size ));
        symbolObj->items().add( sitem );

        sitem = new SitemLine(Color::MAGENTA, width);
        sitem->points().points().add(Point2F( -size, size ));
        sitem->points().points().add(Point2F( size, -size ));
        symbolObj->items().add( sitem );

        style = new Style("id");
        style->sfeats().add( new SfeatSymbol(Color::MAGENTA, symbolObj) );
    }

    EntityPoint* point = new EntityPoint( Point2F(pt.x(), pt.y()), *style, false,
                                          ANGLE_ZERO_VIEW, 0, nullptr );
    entities_.add(point);

    /*EntityLine* line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x()-SIZE, pt.y()) );
    line->points().points().add( Point2F(pt.x()+SIZE, pt.y()) );
    entities_.add(line);

    line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x(), pt.y()-SIZE) );
    line->points().points().add( Point2F(pt.x(), pt.y()+SIZE) );
    entities_.add(line);*/

    //for (int i = 0; i < entities_.count(); i++) {


        pack->add(point);
    //}

    view.entityPack()->scene()->dirtySet();
    scene_ = view.entityPack()->scene();
}

//=============================================================================
void TentativeImplementation::enterTentative( const Point2F& pt, Display& view )
{
    enterTentative_( Point3F(pt.x(), pt.y(), 0), view );
}

//=============================================================================
