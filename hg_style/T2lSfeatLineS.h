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
#include "T2lSfeat.h"
#include "T2lSymbol.h"

namespace T2l
{
//=============================================================================
class SfeatLineS : public Sfeat {
//=============================================================================
public:
//<CONSTRUCTION>
    SfeatLineS( const Color& color, T2l::Symbol* symbol, double spacing,
                double offset = 0.0, bool along = true );
    virtual ~SfeatLineS(void) {;}
//<METHODS>
    T2l::Symbol* symbol()   { return symbol_;  }
    double       spacing()  { return spacing_; }
    double       offset()   { return offset_;  }
    bool         along()    { return along_;   }
//=============================================================================
//<OVERRIDES>
    virtual SfeatLineS*  getAsLineS() { return NULL; }
protected:
//<DATA>
    T2l::Symbol* symbol_;
    double       spacing_;
    double       offset_;
    bool         along_;
};

} // namespace T2l
