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
#include "T2lStyle.h"
#include "T2lSfeatLine.h"
#include "T2lSfeatText.h"
#include "T2lSymbol.h"
#include "T2lSitemArea.h"
#include "T2lSitemCircle.h"
#include "T2lSitemLine.h"
#include "T2lSitemText.h"
#include "T2lSfeatSymbol.h"

#include <string>

using namespace T2l;
using namespace std;

//=============================================================================
Style::Style( const char* id ) :
    id_(id)
{
}

//=============================================================================
Style* Style::createPointStyle( const Color& color, ESymbol symbol, double size, const char* id)
{
    Symbol* symbolObj = new Symbol();

    switch (symbol)
    {
    case SYMBOL_CIRCLE:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, false) );
        break;
    case SYMBOL_CIRCLE_FILLED:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, true) );
        break;
    case SYMBOL_SQUARE:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, false) );
        break;
    case SYMBOL_SQUARE_FILLED:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, true) );
        break;
    case SYMBOL_CROSS_PLUS:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, false) );
        break;
    case SYMBOL_CROSS_X:
        symbolObj->items().add( new SitemCircle( Point2F(0,0), 0.5*size, color, true) );

        double size = 0.008;
        SitemLine* sitem = new SitemLine(Color::MAGENTA, 0.0002);
        sitem->points().points().add(Point2F( size, size ));
        sitem->points().points().add(Point2F( -size, -size ));
        symbolObj->items().add( sitem );

        sitem = new SitemLine(Color::MAGENTA, 0.0002);
        sitem->points().points().add(Point2F( -size, size ));
        sitem->points().points().add(Point2F( size, -size ));
        symbolObj->items().add( sitem );

        break;
    }

    Style* style = new Style(id);
    style->sfeats().add( new SfeatSymbol(color, symbolObj) );

    return style;
}

//=============================================================================
Style* Style::createLineStyleStr ( const Color& color, double width, const char* line_style, const char* id )
{
    string ls_str(line_style);

    ELineStyle ls = LS_SOLID;

    if ( ls_str == "dashed") {
        ls = LS_DASHED;
    }
    if ( ls_str == "dotted") {
        ls = LS_DOTTED;
    }
    else if ( ls_str == "dashdot") {
        ls = LS_DASHDOT;
    }
    else if ( ls_str == "dashdotdot") {
        ls = LS_DASHDOTDOT;
    }

    return createLineStyle(color, width, id, ls);
}

//=============================================================================
QStringList Style::lineStyleCol()
{
    QStringList result;

    result.append("solid");
    result.append("dashed");
    result.append("dotted");
    result.append("dashdot");
    result.append("dashdotdot");

    return result;
}

//=============================================================================
Style* Style::createLineStyle( const Color& color, double width, const char* id, ELineStyle lineStyle)
{
    Style* style = new Style(id);
    Lstyle* lstyle = new Lstyle();
    SfeatLine* sfLine = nullptr;

    switch (lineStyle) {
    case LS_SOLID:
        sfLine = new SfeatLine( color, width);
        break;
    case LS_DASHED:
        lstyle->items().add(new LstyleItem(3, false));
        lstyle->items().add(new LstyleItem(1, true));

        sfLine = new SfeatLine( color, width, lstyle );
        break;
    case LS_DOTTED:
        lstyle->items().add(new LstyleItem(1, false));
        lstyle->items().add(new LstyleItem(0.5, true));

        sfLine = new SfeatLine( color, width, lstyle );
        break;
    case LS_DASHDOT:
        lstyle->items().add(new LstyleItem(4,   false));
        lstyle->items().add(new LstyleItem(0.5, true));
        lstyle->items().add(new LstyleItem(1,   false));
        lstyle->items().add(new LstyleItem(0.5, true));

        sfLine = new SfeatLine( color, width, lstyle );
        break;
    case LS_DASHDOTDOT:
        lstyle->items().add(new LstyleItem(5,   false));
        lstyle->items().add(new LstyleItem(0.5, true));
        lstyle->items().add(new LstyleItem(1,   false));
        lstyle->items().add(new LstyleItem(0.5, true));
        lstyle->items().add(new LstyleItem(1,   false));
        lstyle->items().add(new LstyleItem(0.5, true));

        sfLine = new SfeatLine( color, width, lstyle );
        break;
    }

    style->sfeats().add(sfLine);
    return style;
}

//=============================================================================
Style* Style::createTextStyle( const Color& color, double height, const char* id, bool bold)
{
    Style* style = new Style(id);
    style->sfeats().add( new SfeatText(color, height, bold));
    return style;
}

//=============================================================================


