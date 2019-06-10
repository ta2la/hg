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
#include "T2lRawSline.h"
#include "T2lRawSymbol.h"
#include "T2lSfeatLineS.h"
#include "T2lCanvasI.h"
#include "T2lStationing2.h"

using namespace T2l;
//=============================================================================
RawSline::RawSline( SfeatLineS& sfeat, const T2l::StyleChange* styleChange, bool closed ) :
    Raw(sfeat.color(), styleChange),
    symbol_(sfeat.symbol()),
    spacing_(sfeat.spacing()),
    offset_(sfeat.offset()),
    along_(sfeat.along()),
    closed_(closed)
{
}

//=============================================================================
void RawSline::decompose(CanvasI* canvas)
{
    //<STEP>
    bool hasScale = false;
    if ( canvas->scaleX() != 1.0 )      hasScale = true;
    else if ( canvas->scaleY() != 1.0 ) hasScale = true;

    PolyLine2 scaledPlineCalc;
    if ( hasScale ) {
        for ( int i = 0; i < pline().points().count(); i++) {
            const Point2F& pointi = pline().points().get(i);
            scaledPlineCalc.points().add(canvas->mapRealToPaper(pointi));
        }
    }

    PolyLine2 scaled = hasScale ? scaledPlineCalc : pline();

    //<STEP>
    PolyLine2 ofsettedPlineCalc;
    if ( offset() != 0.0 ) {
        scaled.offset(ofsettedPlineCalc, canvas->mapSymbolicToReal(offset()));
    }

    PolyLine2& pline = (offset() == 0) ? scaled : scaledPlineCalc;

    //<STEP>
    double parameter  = 0;

    while(true) {
        if ( parameter >= pline.paramMax()) break;

        AngleXcc angle(0);
        if (along_ == true)
        {   int i = int(parameter);
            Vector2F dir(pline.points().getRef(i), pline.points().getRef(i+1));
            angle = dir.getAngle();
        }

        RawSymbol rawSymbol( pline.getPoint(parameter), *symbol(),
                                    color(), angle, ANGLE_ZERO_COORDS, styleChange() );

        if ( canvas->draw(&rawSymbol) == false) rawSymbol.decompose(canvas);

        parameter = Stationing2::parameterOffset(pline, parameter, canvas->mapSymbolicToReal(spacing()));
    }
}

//=============================================================================
