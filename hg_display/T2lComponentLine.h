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

#include "T2lComponent.h"
#include "T2lSymbolDefs.h"
#include "T2lPolyLine2.h"

namespace T2l
{
//=============================================================================
class ComponentLine : public T2l::Component {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ComponentLine( const Color& color, double width = 1.0, unsigned char alpha = 255 );
    virtual ~ComponentLine(void) {;}
//<NEIGHBOURS>
    T2l::PolyLine2& points() { return points_; }
//<METHODS>
    double        width()                  { return width_; }
    void          setWidth( double width ) { width_ = width; }
    unsigned char alpha() const            { return alpha_; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_LINE; }
protected:
//<DATA>
    PolyLine2      points_;
    double         width_;
    unsigned char  alpha_;
};

} // namespace T2l
