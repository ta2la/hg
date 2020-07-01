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
#include <iostream>
#include "T2lUpdateLock.h"
#include "T2lScene.h"
#include "T2lSfeatSymbol.h"

using namespace T2l;
using namespace std;//CHECKEND

//=============================================================================
TentativeImplementation::TentativeImplementation() :
    entered_(false)
{
}

//=============================================================================
Point2F TentativeImplementation::consume()
{
    assert(entered_);
    entered_ = false;

    for (int i = 0; i < entities_.count(); i++) {
        delete entities_.get(i);
    }
    entities_.clean();

    return position_;
}

//=============================================================================
void TentativeImplementation::enterTentative_( const Point2F& pt, Display& view )
{
    UpdateLock l;

    if (entered_) consume();
    entered_ = true;
    position_ = pt;

    EntityPack* pack = view.entityPack();
    if ( pack == NULL ) { assert(0); return; }
    if ( pack->scene() == NULL ) return;

    int SIZE = 4;

    //<STEP> Dynamic drawing
    /*static Style style* = nullptr;
    if (style == nullptr) {
        style = new Style();

        Symbol* symbol = new Symbol();

        SfeatSymbol sfeat = new SfeatSymbol();*/

    EntityLine* line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x()-SIZE, pt.y()) );
    line->points().points().add( Point2F(pt.x()+SIZE, pt.y()) );
    entities_.add(line);

    line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x(), pt.y()-SIZE) );
    line->points().points().add( Point2F(pt.x(), pt.y()+SIZE) );
    entities_.add(line);

    for (int i = 0; i < entities_.count(); i++) {
        pack->add(entities_.get(i));
    }

    view.entityPack()->scene()->dirtySet();
}

//=============================================================================
void TentativeImplementation::enterTentative( const Point2F& pt, Display& view )
{
    enterTentative_( pt, view );
}

//=============================================================================
