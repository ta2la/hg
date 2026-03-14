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
#include "T2lElemText.h"
#include "T2lColor.h"

using namespace T2l;

//=============================================================================
ElemText::ElemText( const QString& text, const Point2F& position,
                          double height, const Color& color,
                          EPositionH positionH, EPositionV positionV,
                          bool bold, AngleXcc angle ) :
    Element(color),
    text_(text),
    position_(position),
    height_(height),
    positionH_(positionH),
    positionV_(positionV),
    angle_(angle),
    bold_(bold)
{
}

ElemText::ElemText( const QString& text, CanvasI& canvas, const Point2F& position, double height,
          const Color& color,
          EPositionH positionH,
          EPositionV positionV,
          bool bold, AngleXcc angle) :
    Element(color),
    text_(text),
    position_(canvas.mapRealToPaper(position)),
    height_(canvas.mapRealToPaper(Point2F(height, 0)).x()),
    positionH_(positionH),
    positionV_(positionV),
    angle_(angle),
    bold_(bold)
{
}

//=============================================================================

/*{
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
}*/
