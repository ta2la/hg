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

class Lstyle;
class EntityLine;

//=============================================================================
class RawLine : public Raw {
//=============================================================================
public:
//<CONSTRUCTION>
    RawLine( const Color& color = Color::BLACK, double width = 0.25,
                    double offset = 0.0, Lstyle* lstyle = NULL,
                    bool closed = false, const StyleChange* styleChange = NULL );
    virtual ~RawLine(void) {}
//<METHODS>
    PolyLine2& pline()  { return pline_; }
    double     width()  { return width_;  }
    Lstyle*    lstyle() { return lstyle_; }
    double     offset() { return offset_; }
//=============================================================================
//<OVERRIDES>
    virtual void decompose(CanvasI* canvas);
    virtual ECategory category() { return COMPONENT_RAW_LINE; }
protected:
//<DATA>
    PolyLine2    pline_;
    double       width_;
    Lstyle*      lstyle_;
    double       offset_;
};

} // namespace T2l
