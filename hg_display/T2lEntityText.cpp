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
#include "T2lEntityText.h"
#include "T2lCanvas.h"
#include "T2lSfeatText.h"
#include "T2lVector2.h"
#include "T2lElemText.h"
#include "T2lStyleChange.h"
#include <QFont>
#include <QFontMetrics>

using namespace T2l;

//=============================================================================
EntityText::EntityText( const QString& text, const Point2F& position,
            EPositionH alignH, EPositionV alignV, AngleXcc angle,
            const Point2F& offset, StyleChange* styleChange ) :
    EntityStyled(nullptr, false, styleChange),
    text_(text),
    position_(position),
    offset_(offset),
    alignH_(alignH),
    alignV_(alignV),
    angle_(angle),
    metric_(false)
{
    bound_.inflateTo(position);
}

//=============================================================================
EntityText::EntityText( const QString& text, const Point2F& position,
            EPositionH alignH, EPositionV alignV,
            Style* style, bool styleOwner, AngleXcc angle,
            const Point2F& offset, StyleChange* styleChange, bool metric ) :
    EntityStyled(style, styleOwner, styleChange),
    text_(text),
    position_(position),
    offset_(offset),
    alignH_(alignH),
    alignV_(alignV),
    angle_(angle),
    metric_(metric)
{

}

//=============================================================================
void EntityText::draw(Canvas* canvas)
{
    double scale = 1.0/canvas->scale();
    if ( canvas->scale() > canvas->scale() ) scale = 1.0/canvas->scale();

    if (style()) {
        for (int i = 0; i < style()->sfeats().count(); i++) {
            SfeatText* sfeatText = dynamic_cast<SfeatText*>(style()->sfeats().get2(i));
            if ( sfeatText == nullptr ) continue;
            if ( sfeatText->isScaleIn(scale) == false ) continue;

            EnPointMmRel pt(position(), Vector2F(offset_.x(), offset().y()));

            draw_( canvas, pt.xy(canvas), angle(), sfeatText->color(), sfeatText->height(),
                   sfeatText->bold() );
        }
    }
    else {
        draw_(canvas, position(), angle(), Color::BLACK, 2.5, false);
    }
}

//=============================================================================
void EntityText::draw_(Canvas* canvas, const Point2F& position, const AngleXcc& angle,
                        const Color& colorArg, double heightArg, bool bold)
{
    Point2F pt = canvas->mapRealToPaper(position);

    if ( offset().x() != 0) {
        pt.add( Vector2F(angle, canvas->mapSymbolicToReal(offset().x())) );
    }

    if ( offset().y() != 0) {
        Vector2F off(angle, canvas->mapSymbolicToReal(offset().y()));
        off.setPerpendLeft();
        pt.add(off);
    }

    double heightSymbolic = 1;
    if (metric_) {
        Point2F ptt = canvas->mapRealToPaper(Point2F(heightArg, 0));
        heightSymbolic = ptt.x();//*0.8; //*4
    }
    else {
        heightSymbolic = canvas->mapSymbolicToReal(heightArg);
    }

    ElemText component( text_, pt, heightSymbolic, colorArg, alignH(), alignV(), bold, angle );
    if ( styleChange() != nullptr ) styleChange()->execute(&component, canvas);
    canvas->draw(&component);
}

//=============================================================================
