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

#include "T2lColor.h"
#include "T2lItem.h"
#include "T2lItemCol.h"
#include "T2lIntervalF.h"

namespace T2l
{

class SfeatLine;
class SfeatLineS;
class SfeatArea;
class SfeatSymbol;
class SfeatText;

//=============================================================================
class Sfeat : public Item {
//=============================================================================
public:
    Sfeat( const Color& color );
    virtual ~Sfeat(void) {;}
//<NEIGHBOURS>
    virtual SfeatLine*   getAsLine()   { return NULL; }
    virtual SfeatLineS*  getAsLineS()  { return NULL; }
    virtual SfeatArea*   getAsArea()   { return NULL; }
    virtual SfeatSymbol* getAsSymbol() { return NULL; }
    virtual SfeatText*   getAsText()   { return NULL; }
//<METHODS>
    Color color(void) const { return color_; }

    IntervalF& scale() {return scale_; }
    bool isScaleIn(double scale);
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
    Color     color_;
    IntervalF scale_;
};

typedef ItemCol<Sfeat> SfeatCol;

} // namespace T2l
