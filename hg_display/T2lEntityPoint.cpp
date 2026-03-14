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
#include "T2lElexSymbol.h"
#include "T2lStyleChange.h"
#include "T2lEnPointXy.h"

using namespace T2l;

//=============================================================================
EntityPoint::EntityPoint( const Point2F& origin, Style& style, bool styleOwner,
                    EAngleZero angleZero, AngleXcc angle, StyleChange* styleChange,
                    double metricSize ) :
    EntityStyled( &style, styleOwner, styleChange ),
    origin_(new EnPointXy(origin)),
    angleZero_(angleZero),
    angle_(angle),
    metric_(metricSize > 0 ? true : false),
    metricSize_(metricSize)
{
    bound_.inflateTo(origin);
}

//=============================================================================
EntityPoint::EntityPoint( EnPoint* origin, Style& style, bool styleOwner,
                    EAngleZero angleZero, AngleXcc angle, StyleChange* styleChange ) :
    EntityStyled( &style, styleOwner, styleChange ),
    origin_(origin->clone()),
    angleZero_(angleZero),
    angle_(angle),
    metric_(false),
    metricSize_(1.0)
{
    //bound_.inflateTo(origin);
}

//=============================================================================
void EntityPoint::draw(Canvas* canvas)
{
    Style* styleNc = const_cast<Style*>(style());

    double scale = 1.0/canvas->scale();
    if ( canvas->scale() > canvas->scale() ) scale = 1.0/canvas->scale();

    for ( int i = 0; i < styleNc->sfeats().count(); i++ ) {
        SfeatSymbol* sfSymbol = dynamic_cast<SfeatSymbol*>(styleNc->sfeats().get(i));
        if (sfSymbol == nullptr) continue;
        if ( sfSymbol->isScaleIn(scale) == false ) continue;

        double height = 1;
        if ( metric_ ) {
            Point2F pt = canvas->mapRealToPaper(Point2F(metricSize_, 0));
            height = pt.x()*1000;
        }
        else {
            height = -metricSize_;
        }

        ElexSymbol e( origin(canvas), *sfSymbol->symbol(), Color(Color::BLACK),
                             angle(), angleZero(), styleChange(), height );

        if ( canvas->draw(&e) == false ) e.decompose(canvas);
    }
}

//=============================================================================
