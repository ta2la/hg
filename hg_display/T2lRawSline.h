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

#include "T2lRaw.h"
#include "T2lPolyLine2.h"

namespace T2l
{

class SfeatLineS;
class StyleChange;
class Symbol;

//=============================================================================
class RawSline : public Raw {
//=============================================================================
public:
//<CONSTRUCTION>
    RawSline( SfeatLineS& sfeat, const StyleChange* styleChange, bool closed );
    virtual ~RawSline(void) {}
//<METHODS>
    PolyLine2& pline()   { return pline_;  }
    Symbol*    symbol()  { return symbol_;  }
    double     spacing() { return spacing_; }
    double     offset()  { return offset_;  }
    bool       along()   { return along_;   }
    bool       closed()  { return closed_;  }

    virtual void decompose(CanvasI* canvas);
    virtual ECategory category() { return COMPONENT_RAW_LINES; }
//=============================================================================
protected:
//<DATA>
    PolyLine2 pline_;
    Symbol*   symbol_;
    double    spacing_;
    double    offset_;
    bool      along_;
    bool      closed_;
};

} // namespace T2l
