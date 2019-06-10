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
#include "T2lSymbolDefs.h"
#include "T2lPoint2.h"
#include "T2lAngleXcc.h"

namespace T2l
{

class StyleChange;
class Symbol;

//=============================================================================
class RawSymbol : public Raw {
//=============================================================================
public:
//<CONSTRUCTION>
    RawSymbol( const Point2F position, Symbol& symbol,
                      const Color& color, AngleXcc angle,
                      EAngleZero angleZero = ANGLE_ZERO_COORDS,
                      const StyleChange* styleChange = NULL );
    virtual ~RawSymbol() {}
//<METHODS>
    Point2F&      position()     { return position_; }
    Symbol&       symbol()       { return *symbol_; }
    AngleXcc&     angle()     { return angle_; }
    EAngleZero angleZero() { return angleZero_; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_RAW_SYMBOL; }
    virtual void decompose(CanvasI* canvas);
protected:
//<DATA>
    Point2F       position_;
    Symbol*       symbol_;
    AngleXcc      angle_;
    EAngleZero    angleZero_;
//<INTERNALS>
    Point2F point_(const Point2F& point, CanvasI* canvas);
};

} // namespace T2l
