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
    if (entered_) consume();
    entered_ = true;
    position_ = pt;

    EntityPack* pack = view.entityPack();
    if ( pack == NULL ) { assert(0); return; }
    if ( pack->scene() == NULL ) return;

    //<STEP> Dynamic drawing
    EntityLine* line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x()-20, pt.y()) );
    line->points().points().add( Point2F(pt.x()+20, pt.y()) );
    entities_.add(line);

    line = new EntityLine( Color(255, 0, 255) );
    line->points().points().add( Point2F(pt.x(), pt.y()-20) );
    line->points().points().add( Point2F(pt.x(), pt.y()+20) );
    entities_.add(line);

    for (int i = 0; i < entities_.count(); i++) {
        pack->add(entities_.get(i));
    }
}

//=============================================================================
void TentativeImplementation::enterTentative( const Point2F& pt, Display& view )
{
    //cout << "TENTATIVE AT XY: " << pt.x() << " " << pt.y() << endl;

    enterTentative_( pt, view );
}

//=============================================================================
