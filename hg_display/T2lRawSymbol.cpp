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
#include "T2lRawSymbol.h"
#include "T2lSymbol.h"
#include "T2lVector2.h"
#include "T2lCanvasI.h"
#include "T2lSitemLine.h"
#include "T2lSitemCircle.h"
#include "T2lSitemArea.h"
#include "T2lSitemText.h"
#include "T2lComponentLine.h"
#include "T2lComponentCircle.h"
#include "T2lComponentArea.h"
#include "T2lComponentText.h"

using namespace T2l;

//=============================================================================
RawSymbol::RawSymbol( const T2l::Point2F position, T2l::Symbol& symbol,
                  const Color& color, AngleXcc angle,
                  EAngleZero angleZero, const T2l::StyleChange* styleChange ) :
    Raw( color, styleChange ),
    symbol_(&symbol),
    position_(position),
    angle_(angle),
    angleZero_(angleZero)
{
}

//=============================================================================
void RawSymbol::decompose(T2l::CanvasI* canvas)
{
    for ( int i = 0; i < symbol_->items().count(); i++ ) {
        Sitem* symboli = symbol_->items().get(i);

        switch ( symboli->type() )
        {
        case  Sitem::SITEM_LINE: {
            SitemLine* linei = dynamic_cast<SitemLine*>(symboli);
            ComponentLine line( symboli->color(), canvas->mapSymbolicToReal((linei->width())));
            Point2Col<double>& points = linei->points().points();
            for ( int i = 0; i < points.count(); i++ ) {
                line.points().points().add(point_(points.get(i), canvas));
            }
            canvas->draw(&line);
            }
            break;
        case Sitem::SITEM_AREA: {
            SitemArea* areai = dynamic_cast<SitemArea*>(symboli);
            ComponentArea area(symboli->color());
            Point2FCol& points = areai->points().points().points();
            for (int i = 0; i < points.count(); i++) {
                points.add( point_(points.get(i), canvas) );
            }
            canvas->draw(&area);
            }
            break;
        case Sitem::SITEM_CIRCLE: {
            SitemCircle* circlei = dynamic_cast<SitemCircle*>(symboli);
            ComponentCircle circle( symboli->color(), point_(circlei->center(), canvas),
                                  canvas->mapSymbolicToReal(circlei->radius()),
                                  circlei->fill(), canvas->mapSymbolicToReal((circlei->width())) );
            canvas->draw(&circle);
            }
        break;
        case Sitem::SITEM_TEXT: {
            SitemText* texti = dynamic_cast<SitemText*>(symboli);
            ComponentText text( texti->text(), point_(texti->position(), canvas),
                            canvas->mapSymbolicToReal(texti->height()), symboli->color(),
                            texti->alignH(), texti->alignV(), false, AngleXcc(0));
            canvas->draw(&text);
            break;
}   }   }   }

//=============================================================================
Point2F RawSymbol::point_(const Point2F& point, CanvasI* canvas)
{
    Vector2F v(point.x(), point.y());
    if ( fabs(angle_.get()) > 10e-6) v.rotateCc(angle_);
    Point2F delta = canvas->mapSymbolicToReal(Point2F(v.x(), v.y()));
    return Point2F( position().x()*canvas->scaleX()+delta.x(),
                    position().y()*canvas->scaleY()+delta.y() );
}

