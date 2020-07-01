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
#pragma once

#include "T2lSfeat.h"
#include "T2lItem.h"

namespace T2l
{

class StyleCol;

//=============================================================================
class Style : public Item {
//=============================================================================
public:
//<ENUMS>
    enum ESymbol {
        SYMBOL_CIRCLE,     SYMBOL_CIRCLE_FILLED,
        SYMBOL_SQUARE,     SYMBOL_SQUARE_FILLED,
        SYMBOL_CROSS_PLUS, SYMBOL_CROSS_X };
//<CONSTRUCTION>
    Style( const char* id );
    virtual ~Style(void) {;}

    static Style* createPointStyle( const Color& color, ESymbol symbol, double size, const char* id = "");
    static Style* createLineStyle ( const Color& color, double width = 0.25, const char* id = "");
    static Style* createTextStyle ( const Color& color, double height,       const char* id = "", bool bold = false);
//<NEIGHBOURS>
    SfeatCol& sfeats() { return sfeats_; }
    const SfeatCol& sfeats() const {return sfeats_; }
//<METHODS>
    const char* id() const { return id_.c_str(); }
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
    std::string id_;
    SfeatCol    sfeats_;
};

class StyleItem : public Item
{
public:
    StyleItem(Style* style) : style_(style) {}
    Style* style() { return style_; }
private:
    Style* style_;
};

} // namespace T2l
