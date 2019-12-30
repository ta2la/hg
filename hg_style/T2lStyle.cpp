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

using namespace T2l;

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
        break;
    }

    Style* style = new Style(id);
    style->sfeats().add( new SfeatSymbol(color, symbolObj) );

    return style;
}

//=============================================================================
Style* Style::createLineStyle( const Color& color, double width, const char* id)
{
    Style* style = new Style(id);
    style->sfeats().add( new SfeatLine( color, width) );
    return style;
}

//=============================================================================
Style* Style::createTextStyle( const Color& color, double height, const char* id)
{
    Style* style = new Style(id);
    style->sfeats().add( new SfeatText(color, height));
    return style;
}

//=============================================================================
