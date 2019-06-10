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
#include "T2lBox2.h"
#include "T2lArea2.h"

namespace T2l
{

class CanvasI;

//=============================================================================
class Component {
//=============================================================================
public:
//<ENUMS>
    enum ECategory
    {
        COMPONENT_LINE,
        COMPONENT_CIRCLE,
        COMPONENT_AREA,
        COMPONENT_TEXT,
        COMPONENT_IMAGE,
        COMPONENT_RAW_LINE,
        COMPONENT_RAW_LINES,
        COMPONENT_RAW_SYMBOL,
        COMPONENT_RAW_AREA
    };

//<CONSTRUCTION>
    Component( const Color& color );
    virtual ~Component(void) {;}
//<METHODS>
    virtual ECategory category() = 0;

    const Color& color() const { return color_; }
    void colorSet(const Color& color) { color_ = color; }

    std::vector<T2l::Area2>& clips() { return clips_; }
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
    Color                   color_;
    std::vector<T2l::Area2> clips_;
//<FRIENDS>
    friend class CanvasPainter;
};

} // namespace T2l
