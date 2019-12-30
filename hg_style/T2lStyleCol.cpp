//
// Copyright (C) 2019 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lStyleCol.h"
#include "T2lLstyle.h"
#include "T2lSymbol.h"
#include "T2lSitemCircle.h"
#include "T2lSitemLine.h"
#include "T2lSitemArea.h"
#include "T2lSitemText.h"
#include "T2lSfeatSymbol.h"
#include <string>

using namespace T2l;
using namespace std;

//====================================================================
StyleCol::StyleCol()
{
}

//====================================================================
void StyleCol::load()
{
    add( new StyleItem( Style::createPointStyle ( Color::BLUE, Style::SYMBOL_CIRCLE,        3,   "void"        )) );
}

//====================================================================
Style* StyleCol::getStyle(const char* id)
{
    string ids(id);

    for (int i = 0; i < count(); i++) {
        Style* stylei = get(i)->style();
        if ( ids == stylei->id() ) return stylei;
    }

    return getStyle("void");
}

//====================================================================
SfeatSymbol* StyleCol::lastSymbol()
{
    if ( count() == 0 ) add(new StyleItem(new Style("implicit")) );
    SfeatSymbol* result = nullptr;
    SfeatCol& sfeats = last()->style()->sfeats();
    for ( int i = 0; i < sfeats.count(); i++ ) {
        result = dynamic_cast<SfeatSymbol*>(sfeats.get(i));
        if ( result != nullptr) break;
    }
    result = new SfeatSymbol(Color::BLACK, new Symbol());
    sfeats.add(result);

    return result;
}

//====================================================================
