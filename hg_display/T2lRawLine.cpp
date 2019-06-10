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
#include "T2lRawLine.h"
#include "T2lCanvasI.h"
#include "T2lLstyle.h"
#include "T2lComponentLine.h"
#include "T2lStationing2.h"

using namespace T2l;

//=============================================================================
RawLine::RawLine( const Color& color, double width, double offset, Lstyle* lstyle,
                                bool closed, const T2l::StyleChange* styleChange ) :
    Raw(color, styleChange),
    pline_(closed),
    width_(width),
    lstyle_(lstyle),
    offset_(offset)
{
}

//=============================================================================
void RawLine::decompose(CanvasI* canvas)
{
    //<STEP>
    PolyLine2 plineScaledCalc(false);

    bool hasScale = false;
    if ( canvas->scaleX() != 1.0) hasScale = true;
    else if ( canvas->scaleY() != 1.0) hasScale = true;
    Point2FCol& pointCol = pline().points();
    if ( hasScale) {
        for(int i = 0; i < pointCol.count(); i++) {
            plineScaledCalc.points().add(canvas->mapRealToPaper(pointCol.getRef(i)));
        }
    }

    PolyLine2 plineScaled = hasScale ? plineScaledCalc : pline();

    //<STEP>
    PolyLine2 plineOfsettedCalc;
    if ( offset() != 0.0 ) plineScaled.offset(plineOfsettedCalc, canvas->mapSymbolicToReal((offset())));

    PolyLine2& pline = ( offset() == 0 ) ? plineScaled : plineOfsettedCalc;

    //<STEP>
    double paramEnd = pline.paramMax();
    if ( paramEnd > pline_.paramMax() ) paramEnd = pline_.paramMax();

    if ( ( lstyle() == NULL ) || ( lstyle()->items().count() == 0 ) )
    {
        int beg = 0;
        int end = (int)paramEnd + 1;
        if ( end >= pline.points().count() ) {
            end = pline.points().count()-1;
        }

        ComponentLine component(color(), canvas->mapSymbolicToReal(width()), 255);

        for ( int i = beg; i <= end; i++) {
            component.points().points().add(pline.points().getRef(i));
        }
        if ( pline_.closed() == true ) {
            component.points().points().add(pline.points().getRef(0));
        }

        canvas->draw(&component);
    }
    else // style
    {
        double parameter = 0;

        for (int i = 0; true; i++) {
            if (i >= lstyle()->items().count()) i = 0;

            const LstyleItem* item = lstyle()->items().get2(i);

            double paramNext = Stationing2::parameterOffset(pline, parameter, canvas->mapSymbolicToReal(item->size()));

            if ( item->isSpace() == false ) {
                PolyLine2 cutPart;
                Stationing2::cutPart(pline, cutPart, parameter, paramNext);

                if (cutPart.points().count() >= 2)
                {
                    ComponentLine component(color(), canvas->mapSymbolicToReal(width()));
                    for (int i = 0; i < cutPart.points().count(); i++) {
                        component.points().points().add(cutPart.points().getRef(i));
                    }
                    canvas->draw(&component);
                }
            }

            if ( paramNext >= paramEnd ) break;
            parameter = paramNext;
        }
    }
}

//=============================================================================
