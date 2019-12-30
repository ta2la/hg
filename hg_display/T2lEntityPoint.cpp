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
#include "T2lEntityPoint.h"
#include "T2lCanvas.h"
#include "T2lSfeatSymbol.h"
#include "T2lRawSymbol.h"
#include "T2lStyleChange.h"

using namespace T2l;

//=============================================================================
EntityPoint::EntityPoint( const Point2F& origin, Style& style, bool styleOwner,
                    EAngleZero angleZero, AngleXcc angle, StyleChange* styleChange ) :
    EntityStyled( &style, styleOwner, styleChange ),
    origin_(origin),
    angleZero_(angleZero),
    angle_(angle)
{
    bound_.inflateTo(origin);
}

//=============================================================================
void EntityPoint::draw(Canvas* canvas)
{
    Style* styleNc = const_cast<Style*>(style());

    double scale = 1.0/canvas->scaleX();
    if ( canvas->scaleX() > canvas->scaleY() ) scale = 1.0/canvas->scaleY();

    for ( int i = 0; i < styleNc->sfeats().count(); i++ ) {
        SfeatSymbol* sfSymbol = dynamic_cast<SfeatSymbol*>(styleNc->sfeats().get(i));
        if (sfSymbol == NULL) continue;
        if ( sfSymbol->isScaleIn(scale) == false ) continue;

        RawSymbol e( origin(), *sfSymbol->symbol(), Color(Color::BLACK),
                                  angle(), angleZero(), styleChange() );
        /*if ( styleChange_ ) {
            styleChange_->execute(&e, canvas);
        }*/

        if ( canvas->draw(&e) == false ) e.decompose(canvas);
    }
}

//=============================================================================
