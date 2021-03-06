//
// Copyright (C) 2015, 2017 Petr Talla. [petr.talla@gmail.com]
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
#include "T2lArea2.h"

namespace T2l
{
//=============================================================================
class ComponentArea : public T2l::Component {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ComponentArea( const Color& color, unsigned char alpha = 255 );
    virtual ~ComponentArea(void) {;}
//<NEIGHBOURS>
    T2l::Area2& area() { return area_; }
//<METHODS>
    unsigned char alpha() const { return alpha_; }
    void alphaSet(unsigned char alpha) { alpha_ = alpha; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_AREA; }
protected:
//<DATA>
    Area2          area_;
    unsigned char  alpha_;
};

} // namespace T2l
